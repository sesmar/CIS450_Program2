#include "CPUScheduler.h"

int CPUScheduler::getCurrentClock() { return _clock; }

void CPUScheduler::incrementClock() { _clock++; }

void CPUScheduler::addToReadyQueue(Job job) { _readyQueue.push(job); }
