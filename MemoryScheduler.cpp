#include "MemoryScheduler.h"


//function definitions
void MemoryScheduler::FirstFit(vector<char> &memory, char ProcessID, int memNeeded)
{
	int startPos=0;
	int holeCount=0;
	bool flag=false;

	for(int i=0; i<256; i++)
	{
		if(flag==false && memory[i]=='_')    //store position  
		{
			startPos=i;
			flag=true;
		}

		if(flag==true)
		{
				
				if(memory[i]=='_')
				{
					holeCount++;

						//check to see if enough holes have been found
						if(holeCount==memNeeded)
						{
							for(int j=startPos; j<startPos+memNeeded; j++)
							{
								memory[j]=ProcessID;

							}

							return;
						}

				}
				else
				{
					flag=false;
					holeCount=0;

				}
		}
	}

}


void MemoryScheduler::WorstFit(vector<char> &memory, char ProcessID, int memNeeded)
{
	int holeCount=0;
	bool flag=false;

	int currentPos=0;
	int currentHoleCount=0;
	int nextPos=0;

	for(int i=0; i<256; i++)
	{
		if(flag==false && memory[i]=='_')    //store position  
		{
			nextPos=i;
			flag=true;
		}

		if(flag==true)
		{
			
				if(memory[i]=='_' && i!=255)
				{
					holeCount++;
				}
				else
				{   
					if(memory[i]=='_')
					{holeCount++;}
					
					//compare new hole with previously stored hole
					if(holeCount>currentHoleCount)
					{
						currentPos=nextPos;				//store position of new largest hole
						currentHoleCount=holeCount;     //store size of new largest hole for comparison
					}

					flag=false;
					holeCount=0;

				}
		}
	}

	//store data into the largest hole
	for(int j=currentPos; j<currentPos+memNeeded; j++)
	{
		memory[j]=ProcessID;
	}

	return;
}

void MemoryScheduler::BestFit(vector<char> &memory, char ProcessID, int memNeeded)
{
	int holeCount=0;
	bool flag=false;

	int currentPos=0;
	int currentHoleCount=999;
	int nextPos=0;

	for(int i=0; i<256; i++)
	{
		if(flag==false && memory[i]=='_')    //store position  
		{
			nextPos=i;
			flag=true;
		}

		if(flag==true)
		{
			
				if(memory[i]=='_' && i!=255)
				{
					holeCount++;
				}
				else
				{   
					if(memory[i]=='_')
					{holeCount++;}
					//compare new hole with previously stored hole
					if(holeCount<currentHoleCount && holeCount>=memNeeded)
					{
						currentPos=nextPos;				//store position of new largest hole
						currentHoleCount=holeCount;     //store size of new largest hole for comparison
					}

					flag=false;
					holeCount=0;

				}
		}
	}

	//store data into the largest hole
	for(int j=currentPos; j<currentPos+memNeeded; j++)
	{
		memory[j]=ProcessID;
	}

}

void MemoryScheduler::ReleaseMemory(vector<char> &memory, char ProcessID)
{
	for(int i=0; i<256; i++)
	{
		if(memory[i]==ProcessID)
		{
			memory[i]='_';     //return memory to the system
		}
	}

}
