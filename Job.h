#include <string>

using namespace std;

#ifndef JOB_H
#define JOB_H

class Job
{
	private:
		int _arrivalTime;
		int _completionTime;
		string *_currentState;
		int _dataSize;
		int _pId;
		int _waiting;
		int _ready;
		int _running;
		int _serviceTime;

	public:
		Job(
				int arrivalTime, 
				int dataSize, 
				int pId, 
				int serviceTime
			);

		int getArrivalTime();
		int getCompletionTime();
		const char *getCurrentState();
		int getDataSize();
		int getProcessId();
		int getWaitingTime();
		int getReadyTime();
		int getRunningTime();
		int getServiceTime();

		void incrementReadyTime();
		void incrementRunningTime();
		void incrementWaitingTime();

		void setCurrentState(const char *state);
};

#endif /* JOB_H */
