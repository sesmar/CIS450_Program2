#include <queue>
#include <vector>
#include "Job.h"

using namespace std;

#ifndef ADMISSIONSCHEDULER_H
#define ADMISSIONSCHEDULER_H

class AdmissionScheduler
{
	private:
		queue<int> _jobQueue;

	public:
		void addJob(int jobIndex);
		vector<int> checkJobsForAdmission(vector<Job*> jobList, int clockTime);
		int queueSize();
};

#endif /* ADMISSIONSCHEDULER_H */
