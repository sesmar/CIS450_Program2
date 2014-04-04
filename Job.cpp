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
	char result;

	switch(_pId)
	{
		case 0:
			result = 'a';
			break;
		case 1:
			result = 'b';
			break;
		case 2:
			result = 'c';
			break;
		case 3:
			result = 'd';
			break;
		case 4:
			result = 'e';
			break;
		case 5:
			result = 'f';
			break;
		case 6:
			result = 'g';
			break;
		case 7:
			result = 'h';
			break;
		case 8:
			result = 'i';
			break;
		case 9:
			result = 'j';
			break;
	}
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
