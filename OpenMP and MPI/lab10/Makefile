all:
	mpicc lab.c -o lab
	mpicc lab2.c -o lab2
run:
	mpirun -np 9 ./lab
run2:
	mpirun -np 9 ./lab2
stat:
	time -p mpirun -np 9 ./lab
	time -p mpirun -np 9 ./lab2
