#include <queue>
#include <vector>
#include "Job.h"

using namespace std;

#ifndef ADMISSIONSCHEDULER_H
#define ADMISSIONSCHEDULER_H

class AdmissionScheduler
{
	private:
		queue<Job> _jobQueue;

	public:
		void addJob(Job job);
		vector<Job> checkJobsForAdmission(int clockTime);
};

#endif /* ADMISSIONSCHEDULER_H */
