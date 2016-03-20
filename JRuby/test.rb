#!/usr/bin/ruby -w

command = ''
data = ''
key = 'q'
path = '/dev/ttyUSB0'

file = File.new(path,'w+')

	while command.chomp != key
		puts '=== write your command and press enter (<'+key+'> to exit):'

		command = gets
		
		if command.chomp == ''
			puts '=== try again...'

		elsif command.chomp != key

			file.puts command.chomp + ' | wc -c'
			file.gets
			flag = file.gets.to_i

			if flag == 0
				t1_put = Time.now
					file.puts command.chomp
				t2_put = Time.now
				file.gets
				puts '=== total time (millisec) :'
				time = (t2_put - t1_put)*1000
				puts time.to_s
			else
				t1_put = Time.now
					file.puts command.chomp + ' > /tmp/data'
				t2_put = Time.now
				file.gets
				file.puts 'wc -c /tmp/data'
				file.gets
				file.gets 
				chars = file.gets.to_i

				file.puts 'wc -l /tmp/data'
				file.gets
				lines = file.gets.to_i

				num = chars  + lines

				file.puts 'cat /tmp/data'
				file.gets

				t1_get = Time.now
					data = file.read(num)
				t2_get = Time.now

				puts '=== number of chars:'
				puts num
	
				puts '=== result:'
				puts data

				puts '=== total time (millisec) :'
				time = (t2_put - t1_put)*1000 + (t2_get - t1_get)*1000
				puts time.to_s
			end

			file.puts 'clear'
			file.gets
		
		end
	end

	file.puts 'rm /tmp/data'
	file.puts 'clear'
	file.gets
	file.gets

file.close