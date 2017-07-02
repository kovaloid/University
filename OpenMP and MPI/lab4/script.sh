#!/bin/sh

echo "Optimization Experiment"

echo "\nO0"
g++ -O0 Device.cpp DeviceController.cpp Buffer.cpp Request.cpp SourceOfRequests.cpp	SourceOfRequestsController.cpp main.cpp -lncurses -o prog
du -h prog
time -p ./prog > /dev/null

echo "\nOs"
g++ -Os Device.cpp DeviceController.cpp Buffer.cpp Request.cpp SourceOfRequests.cpp	SourceOfRequestsController.cpp main.cpp -lncurses -o prog
du -h prog
time -p ./prog > /dev/null

echo "\nO1"
g++ -O1 Device.cpp DeviceController.cpp Buffer.cpp Request.cpp SourceOfRequests.cpp	SourceOfRequestsController.cpp main.cpp -lncurses -o prog
du -h prog
time -p ./prog > /dev/null

echo "\nO2"
g++ -O2 Device.cpp DeviceController.cpp Buffer.cpp Request.cpp SourceOfRequests.cpp	SourceOfRequestsController.cpp main.cpp -lncurses -o prog
du -h prog
time -p ./prog > /dev/null

echo "\nO3"
g++ -O3 Device.cpp DeviceController.cpp Buffer.cpp Request.cpp SourceOfRequests.cpp	SourceOfRequestsController.cpp main.cpp -lncurses -o prog
du -h prog
time -p ./prog > /dev/null

echo "\nO2 -march=native"
g++ -O2 -march=native Device.cpp DeviceController.cpp Buffer.cpp Request.cpp SourceOfRequests.cpp	SourceOfRequestsController.cpp main.cpp -lncurses -o prog
du -h prog
time -p ./prog > /dev/null

echo "\nO3 -march=native"
g++ -O3 -march=native Device.cpp DeviceController.cpp Buffer.cpp Request.cpp SourceOfRequests.cpp	SourceOfRequestsController.cpp main.cpp -lncurses -o prog
du -h prog
time -p ./prog > /dev/null

echo "\nO2 -march=native -funroll-loops"
g++ -O2 -march=native -funroll-loops Device.cpp DeviceController.cpp Buffer.cpp Request.cpp SourceOfRequests.cpp	SourceOfRequestsController.cpp main.cpp -lncurses -o prog
du -h prog
time -p ./prog > /dev/null

echo "\nO3 -march=native -funroll-loops"
g++ -O3 -march=native -funroll-loops Device.cpp DeviceController.cpp Buffer.cpp Request.cpp SourceOfRequests.cpp	SourceOfRequestsController.cpp main.cpp -lncurses -o prog
du -h prog
time -p ./prog > /dev/null

echo "END"



