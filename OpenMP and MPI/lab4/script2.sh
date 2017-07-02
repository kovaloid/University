#!/bin/sh

echo "Optimization Experiment"

echo "\n-O3 -flto -fipa-sra -fipa-pta -fipa-reference"
g++ -O3 -flto -fipa-sra -fipa-pta -fipa-reference Device.cpp DeviceController.cpp Buffer.cpp Request.cpp SourceOfRequests.cpp	SourceOfRequestsController.cpp main.cpp -lncurses -o prog
du -h prog
time -p ./prog > /dev/null

echo "\n-O3 -fprofile-use"
g++ -O3 -fprofile-use Device.cpp DeviceController.cpp Buffer.cpp Request.cpp SourceOfRequests.cpp	SourceOfRequestsController.cpp main.cpp -lncurses -o prog
du -h prog
time -p ./prog > /dev/null

echo "\n-O3 -flto -fipa-sra -fipa-pta -fipa-reference -fprofile-use"
g++ -O3 -flto -fipa-sra -fipa-pta -fipa-reference -fprofile-use Device.cpp DeviceController.cpp Buffer.cpp Request.cpp SourceOfRequests.cpp	SourceOfRequestsController.cpp main.cpp -lncurses -o prog
du -h prog
time -p ./prog > /dev/null

echo "END"



