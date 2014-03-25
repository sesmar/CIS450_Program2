#include <iostream>
#include <fstream>
#include "Job.h"
#include "AdmissionScheduler.h"

using namespace std;

///
//Main program source file.
///
int main(int argc, char **argv)
{
	int memoryAlgorithm = 0;
	char* inputFile;
	AdmissionScheduler adminScheduler();

	if (argc < 3)
	{
		cout << "Usage: simulation <Memory Algorithm> <Data File>" << endl;
		cout << " e.g.: ./simulation 1 datafile.txt" << endl;
		exit(0);
	}

	memoryAlgorithm = atoi(argv[1]);
	inputFile = argv[2];

	ifstream infile(inputFile);

	int a, b, c, d;

	while (infile >> a >> b >> c >> d)
	{
		Job job(a, b, c, d);
		adminScheduler.addJob(job);
	}

	cout << "Running main simulation loop" << endl;
}
