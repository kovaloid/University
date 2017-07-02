all:
	g++ -g -fopenmp -o conflict conflict.c
	g++ -g -fopenmp -o lab lab.c
all2:
	/opt/intel/bin/icc -qopenmp -qopenmp-link dynamic -g -shared-libgcc -O0 -o conflict conflict.c
checker:
	/opt/intel/inspector/bin64/inspxe-gui
clean:
	rm -rf myresult
	rm -rf myresult-bad
	rm -f conflict
export:
	export PATH="/opt/intel/compilers_and_libraries/linux/lib/intel64:$PATH"
	export LD_LIBRARY_PATH="/opt/intel/compilers_and_libraries/linux/lib/intel64:$LD_LIBRARY_PATH"

