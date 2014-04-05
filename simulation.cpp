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
	case 0:
		memScheduler = new FirstFitMemoryScheduler();
		break;
	case 1:
		memScheduler = new BestFitMemoryScheduler();
		break;
	case 2:
		memScheduler = new WorstFitMemoryScheduler();
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
	queue<int> readyTemp;

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

		readyTemp = adminScheduler.checkJobsForAdmission(
			JobList::getJobs(),
			clockTime
			);

		while (readyTemp.size() > 0)
		{
			readyForWaiting.push(readyTemp.front());
			readyTemp.pop();
		}

		if (readyForWaiting.size() > 0)
		{
			Job* job = JobList::getJobs()[readyForWaiting.front()];

			//if job can be loaded into memory, add to CPUScheduler ready queue.
			if (memScheduler->scheduleJob(job->getMappedProcessId(), job->getDataSize()))
			{
				cpu->addToReadyQueue(readyForWaiting.front());
				readyForWaiting.pop();
				stats.MemMap(memScheduler->getMemory());
				stats.PercentHoles(memScheduler->getMemory());
			}
			{
				job->setCurrentState("Waiting");
			}
			
			adminScheduler.incrementWaiting(readyForWaiting);
		}

		cpu->scheduleJob();

		int lastCompleted = cpu->lastCompleted();

		if (lastCompleted >= 0)
		{
			memScheduler->releaseMemory(JobList::getJobs()[lastCompleted]->getMappedProcessId());

			stats.OutputMem(memScheduler->getMemory());
			cout << endl << endl;
		}

		if (clockTime % 10 == 0)
		{
			cout << "The Process States at Time " << clockTime << endl << endl;

			stats.ProcessStates(JobList::getJobs(), clockTime);
			cout << endl;
		}

		cpu->incrementClock();
	}

	cout << "The Process States at Time " << cpu->getCurrentClock() << endl << endl;
	stats.ProcessStates(JobList::getJobs(), cpu->getCurrentClock());

	cout << "Total simulation time units: " << cpu->getCurrentClock() << endl;
	cout << "Total number of jobs: " << JobList::getJobs().size() << endl;
	cout << "Average hole percent: " << endl;
	cout << "Average waiting time: " << stats.getAvgWaitTime(JobList::getJobs()) << endl << endl;

	cout << "Press enter to continue..." << endl;
	cin.get();
}
