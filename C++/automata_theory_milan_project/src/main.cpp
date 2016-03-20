#include "parser.h"
#include <iostream>
#include <cstdlib>


using namespace std;

void printHelp()
{
	cout << "Usage: cmilan input_file" << endl;
}

int main(int argc, char** argv)
{
	if(argc < 2) {
		printHelp();
		return 1;
	}
	Parser p(argv[1]);
	p.parse();

	//getchar();
	return 0;
}