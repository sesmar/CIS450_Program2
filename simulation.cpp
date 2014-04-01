#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "Job.h"
#include "Stats.h"
#include "AdmissionScheduler.h"
#include "CPUScheduler.h"
#include "MemoryScheduler.h"
#include "JobList.h"

using namespace std;

///
//Main program source file.
///
int main(int argc, char **argv)
{
	int memoryAlgorithm = 0;
	char* inputFile;
	AdmissionScheduler adminScheduler;
	CPUScheduler *cpu = new CPUScheduler();
	MemoryScheduler memScheduler;
	Stats stats;

	if (argc < 3)
	{
		cout << "Usage: simulation <Memory Algorithm> <Data File>" << endl;
		cout << " e.g.: ./simulation 1 datafile.txt" << endl;
		exit(0);
	}

	memoryAlgorithm = atoi(argv[1]);
	inputFile = argv[2];

	ifstream infile(inputFile);

	int pId;
	int arrivalTime;
	int serviceTime;
	int dataSize;

	cout << "Loading jobs from: " << inputFile << endl;

	int jobIndex = 0;

	while (infile >> pId >> arrivalTime >> serviceTime >> dataSize)
	{

		Job job(pId, arrivalTime, serviceTime, dataSize);
		JobList::addJob(job);
		adminScheduler.addJob(jobIndex);
		jobIndex++;
	}

	cout << adminScheduler.queueSize() << " jobs loaded." << endl;
	
	cout << "Running main program loopi." << endl;

	while (adminScheduler.queueSize() > 0)
	{
		vector<Job> readyForWaiting = adminScheduler.checkJobsForAdmission(
				JobList::getJobs(),
				cpu->getCurrentClock()
				);

		cout << "Clock Time: " << cpu->getCurrentClock() << " ";


		for(int i = 0; i < readyForWaiting.size(); i++)
		{
			Job job = readyForWaiting[i];

			cout << "Process: " << job.getProcessId() << " arrived";
			memScheduler.FirstFit(job.getMappedProcessId(), job.getDataSize());
		}

		cpu->incrementClock();

		cout << endl;

		stats.MemMap(memScheduler.getMemory());
	}

	stats.ProcessStates(JobList::getJobs());
}
