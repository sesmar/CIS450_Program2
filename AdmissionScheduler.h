#include <queue>
#include <vector>
#include "Job.h"
#include "JobList.h"

using namespace std;

#ifndef ADMISSIONSCHEDULER_H
#define ADMISSIONSCHEDULER_H

class AdmissionScheduler
{
	private:
		queue<int> _jobQueue;

	public:
		void addJob(int jobIndex);
		queue<int> checkJobsForAdmission(vector<Job*> jobList, int clockTime);
		int queueSize();
		void incrementWaiting(queue<int> awaitingMemory, int clockTime);

};

#endif /* ADMISSIONSCHEDULER_H */
