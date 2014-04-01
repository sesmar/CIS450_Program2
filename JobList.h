#include <vector>
#include "Job.h"

class JobList
{
	private: 
		static vector<Job>* _jobs;

	public:
		static vector<Job> getJobs();
		static void addJob(Job job); 
};
