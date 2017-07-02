 gcc -c -fPIC -m64 -fopenmp -g course.cpp -o my.o -lstdc++ -lm
 gcc -m64 -shared -fopenmp -g  my.o  -o ./course.so -lstdc++ -lm
 cp course.so ../../src/main/resources/linux-x86-64/libcourse.so
