#include "Job.h"

Job::Job(int pId, int arrivalTime, int serviceTime, int dataSize)
{
	_arrivalTime = arrivalTime;
	_dataSize = dataSize;
	_pId = pId;
	_serviceTime = serviceTime;

	_completionTime = 0;
	_waiting = 0;
	_ready = 0;
	_running = 0;

	_currentState = new string("");
}

int Job::getArrivalTime() { return _arrivalTime; }

int Job::getCompletionTime() { return _completionTime; }

const char* Job::getCurrentState() { return _currentState->c_str(); }

int Job::getDataSize() { return _dataSize; }

int Job::getProcessId() { return _pId; }

char Job::getMappedProcessId()
{
	int convertedId = _pId + 97;
	char result = convertedId;

	return result;
}

int Job::getWaitingTime() { return _waiting; }

int Job::getReadyTime() { return _ready; }

int Job::getRunningTime() { return _running; }

int Job::getServiceTime() { return _serviceTime; }

void Job::incrementReadyTime() { _ready++; }

void Job::incrementRunningTime() { _running++; }

void Job::incrementWaitingTime() { _waiting++; }

void Job::setCompletionTime(int cpu_time)
{
	_completionTime = cpu_time;
}

void Job::setCurrentState(const char *state)
{
	_currentState = new string(state);
}
