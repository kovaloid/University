 gcc -c -fPIC -m64 -fopenmp -g course_norm.cpp -o my.o -lstdc++
 gcc -m64 -shared -fopenmp -g  my.o  -o ./course.so -lstdc++
 cp course.so ../../src/main/resources/linux-x86-64/libcourse.so
