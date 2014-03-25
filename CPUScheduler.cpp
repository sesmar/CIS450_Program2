#include "CPUScheduler.h"

int CPUScheduler::getCurrentClock() { return _clock; }

int CPUScheduler::incrementClock() { _clock++; }

void CPUScheduler::addToReadyQueue(Job job) { _readyQueue.push(job); }
