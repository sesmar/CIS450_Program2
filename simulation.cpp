#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <queue>
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
	MemoryScheduler *memScheduler = NULL;
	Stats stats;

	if (argc < 3)
	{
		cout << "Usage: simulation <Memory Algorithm> <Data File>" << endl;
		cout << " e.g.: ./simulation 1 datafile.txt" << endl;
		exit(0);
	}

	memoryAlgorithm = atoi(argv[1]);

	//select the proper memory scheduler based on input.
	switch (memoryAlgorithm)
	{
	case 1:
		memScheduler = new FirstFitMemoryScheduler();
		break;
	case 2:
		memScheduler = new WorstFitMemoryScheduler();
		break;
	case 3:
		memScheduler = new BestFitMemoryScheduler();
		break;
		//default case is FirstFit
	default:
		memScheduler = new FirstFitMemoryScheduler();
	}

	inputFile = argv[2];

	ifstream infile(inputFile);

	int pId;
	int arrivalTime;
	int serviceTime;
	int dataSize;
	int jobIndex = 0;
	queue<int> readyForWaiting;

	while (infile >> pId >> arrivalTime >> serviceTime >> dataSize)
	{

		Job job(pId, arrivalTime, serviceTime, dataSize);
		JobList::addJob(job);
		adminScheduler.addJob(jobIndex);
		jobIndex++;
	}

	while (adminScheduler.queueSize() > 0 || cpu->queueSize() > 0)
	{
		int clockTime = cpu->getCurrentClock();

		if (readyForWaiting.size() == 0)
		{
			readyForWaiting = adminScheduler.checkJobsForAdmission(
				JobList::getJobs(),
				clockTime
				);
		}

		if (readyForWaiting.size() > 0)
		{
			Job* job = JobList::getJobs()[readyForWaiting.front()];

			//if job can be loaded into memory, add to CPUScheduler ready queue.
			if (memScheduler->scheduleJob(job->getMappedProcessId(), job->getDataSize()))
			{
				cpu->addToReadyQueue(readyForWaiting.front());
				readyForWaiting.pop();
			}
		}

		cpu->scheduleJob();
		adminScheduler.incrementWaiting(readyForWaiting);

		int lastCompleted = cpu->lastCompleted();

		if (lastCompleted >= 0)
		{
			memScheduler->releaseMemory(JobList::getJobs()[lastCompleted]->getMappedProcessId());
		}

		cpu->incrementClock();

		stats.MemMap(memScheduler->getMemory());
		stats.PercentHoles(memScheduler->getMemory());
	}

	stats.ProcessStates(JobList::getJobs());

	cout << "Press enter to continue..." << endl;
	cin.get();
}
