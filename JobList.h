#include <vector>
#include "Job.h"


#ifndef JOBLIST_H
#define JOBLIST_H

class JobList
{
	private: 
		static vector<Job>* _jobs;

	public:
		static vector<Job*> getJobs();
		static void addJob(Job job); 
};

#endif