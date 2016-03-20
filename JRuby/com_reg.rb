
load "serialport.rb"

begin

	gps_comport = "/dev/ttyUSB0"
	serial_port = SerialPort.new gps_comport, 115200, 8, 1, GnuSerialPort::PARITY_NONE
	puts "Serial port configuration [done]"
	puts '========================================='

	key = 'q'
	command = ''
	data = ''
	path = '/home/koval/output.txt'
	read_size = 100000
	amount = 15
	longitude = []
	latitude = []
	array = ["Longitude", "Latitude", "Altitude"]
	fix_value = "3D FIX"

	file = File.new(path,'w')

	serial_port.read_timeout = 500

	print 'Please wait'
	booting = ''

	check_flag = 1
	3.times do
		char = serial_port.read(1)
		booting = booting + char
		check_flag = 0 if char[0] != 0
		print '.'
	end
	puts

	if check_flag == 0
		puts 'Some programm is already running...'
		exit
	end


	while command.chomp != key

		puts '=== input (<'+key+'> to exit):'
		command = gets

		if command.chomp == ''
			puts '=== try again...'

		elsif command.chomp != key
	
			serial_port.write command
			time_start = Time.now
			serial_port.read(command.size+1)

			
			if command[0..1] == './'
				puts '=== result data:'

				serial_port.write "\n\n"
				serial_port.read(10)
	
				first_time = true
				count = 0

				while count < amount
					rec = serial_port.read(read_size)
					data = rec

					if !data.scan("Segmentation fault").empty?
						puts 'Segmentation fault!'
						exit
					end

					if (first_time == true) && !data.scan(fix_value).empty?
					#TTF
						time_end = Time.now
						ttf = (time_end - time_start)*1000
						puts "TTF (msec): \t"+ttf.to_s
						file.puts "TTF (msec): \t"+ttf.to_s
						file.puts
						puts
						first_time = false
					end

					if !data.scan(fix_value).empty?
						count = count + 1
						puts count.to_s + ")"
						file.puts count.to_s + ")"

						tmp = []
						tmp.concat(array)
						tmp.size.times do
							j = []
							tmp.each_index {|i| j[i] = data.index(tmp[i]) }

							min_j = j.select{|i| i>=0}.min
							min_j_index = j.index(min_j)

							data = data.slice(data.index(tmp[min_j_index])..data.size)
							data = data.slice(data.index(/\-?[0-9]/)..data.size)

							puts tmp[min_j_index]+": \t"+data.to_f.to_s
							file.puts tmp[min_j_index]+": \t"+data.to_f.to_s

							if tmp[min_j_index] == array[0] #longitude
								longitude[count-1] = data.to_f
							elsif tmp[min_j_index] == array[1] #latitude
								latitude[count-1] = data.to_f
							end

							j.delete_at(min_j_index)
							tmp.delete_at(min_j_index)
						end
					end
				end

			#from grad to km
				longitude.each_index {|i| longitude[i] = longitude[i]*Math.cos(latitude[i]*Math::PI/180)*40000/360 }
				latitude.each_index {|i| latitude[i] = latitude[i]*40000/360 }
			#CEP
				longitude_sum = 0
				latitude_sum = 0
				longitude.each_index {|i| longitude_sum = longitude_sum + longitude[i] }
				latitude.each_index {|i| latitude_sum = latitude_sum + latitude[i] }
				longitude_0 = longitude_sum / longitude.size
				latitude_0 = latitude_sum / latitude.size
				vec = []
				longitude.each_index {|i| vec[i]=Math.sqrt((longitude[i]-longitude_0)**2+(latitude[i]-latitude_0)**2) }
				vec = vec.sort
				cep = vec[vec.size/2]
				puts
				file.puts
				puts "CEP (km): \t"+cep.to_s
				file.puts "CEP (km): \t\t"+cep.to_s

			else
				rec = serial_port.read(read_size)
				end_index = rec.index(/\/.*# /)
				data = rec[0, end_index]
				start_index = end_index
				end_index = rec.rindex('#') - start_index + 1
				folder = rec[start_index, end_index]
				if data != ''
					puts '=== output:'
					puts data
				end
				puts '=== folder:'
				puts folder
			end

		end
	end

	file.close
	serial_port.close
	
end