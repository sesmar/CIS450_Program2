#include "MemoryScheduler.h"

MemoryScheduler::MemoryScheduler()
{
	for(int x = 0; x < 256; x++)
	{
		_memory.push_back('_');
	}
}

void MemoryScheduler::releaseMemory(char processId)
{
	for(int i=0; i<_memory.size(); i++)
	{
		if(_memory[i]==processId)
		{
			_memory[i]='_';     //return memory to the system
		}
	}

}

vector<char> MemoryScheduler::getMemory()
{
	return _memory;
}

bool FirstFitMemoryScheduler ::scheduleJob(char processId, int memNeeded)
{
	int startPos = 0;
	int holeCount = 0;
	bool flag = false;

	for (int i = 0; i<_memory.size(); i++)
	{
		if (flag == false && _memory[i] == '_')    //store position  
		{
			startPos = i;
			flag = true;
		}

		if (flag == true)
		{
			if (_memory[i] == '_')
			{
				holeCount++;

				//check to see if enough holes have been found
				if (holeCount == memNeeded)
				{
					for (int j = startPos; j<startPos + memNeeded; j++)
					{
						_memory[j] = processId;
					}

					return true;
				}

			}
			else
			{
				flag = false;
				holeCount = 0;

			}
		}
	}

	return false;
}

bool WorstFitMemoryScheduler::scheduleJob(char processId, int memNeeded)
{
	int holeCount = 0;
	bool flag = false;

	int currentPos = 0;
	int currentHoleCount = 0;
	int nextPos = 0;

	for (int i = 0; i<_memory.size(); i++)
	{
		if (flag == false && _memory[i] == '_')    //store position  
		{
			nextPos = i;
			flag = true;
		}

		if (flag == true)
		{

			if (_memory[i] == '_' && i != (_memory.size() - 1))
			{
				holeCount++;
			}
			else
			{
				if (_memory[i] == '_')
				{
					holeCount++;
				}

				//compare new hole with previously stored hole
				if (holeCount>currentHoleCount)
				{
					currentPos = nextPos;				//store position of new largest hole
					currentHoleCount = holeCount;     //store size of new largest hole for comparison
				}

				flag = false;
				holeCount = 0;

			}
		}
	}

	if(currentHoleCount>=memNeeded)
	{
		//store data into the largest hole
		for (int j = currentPos; j<currentPos + memNeeded; j++)
		{
			_memory[j] = processId;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool BestFitMemoryScheduler::scheduleJob(char processId, int memNeeded)
{
	int holeCount = 0;
	bool flag = false;

	int currentPos = 0;
	int currentHoleCount = 999;
	int nextPos = 0;

	for (int i = 0; i<_memory.size(); i++)
	{
		if (flag == false && _memory[i] == '_')    //store position  
		{
			nextPos = i;
			flag = true;
		}

		if (flag == true)
		{

			if (_memory[i] == '_' && i != (_memory.size() - 1))
			{
				holeCount++;
			}
			else
			{
				if (_memory[i] == '_')
				{
					holeCount++;
				}
				//compare new hole with previously stored hole
				if (holeCount<currentHoleCount && holeCount >= memNeeded)
				{
					currentPos = nextPos;				//store position of new largest hole
					currentHoleCount = holeCount;     //store size of new largest hole for comparison
				}

				flag = false;
				holeCount = 0;

			}
		}
	}

		if(currentHoleCount>=memNeeded)
		{
			//store data into the largest hole
			for (int j = currentPos; j<currentPos + memNeeded; j++)
			{
				_memory[j] = processId;
			}
			return true;
		}
		else
		{
			return false;
		}
}