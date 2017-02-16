#include "ProcessTable.h"
#include <iostream>
ProcessTable::ProcessTable()
{
	head = NULL;
	sizeOftList = 0;
	cores[0].ifBusy = false;
	cores[0].busyUntil = 0;
	cores[1].ifBusy = false;
	cores[1].busyUntil = 0;
}

void ProcessTable::appendTable(int pID, double start)
{
	ProcessTableNode *newTnode;
	ProcessTableNode *nodePtr;

	newTnode = new ProcessTableNode;

	newTnode->processID = pID;
	newTnode->startT = start;
	newTnode->next = NULL;
	newTnode->CoreTime = 0;


	if (head == NULL)
	{
		head = newTnode;
		sizeOftList++;
	}

	else
	{
		nodePtr = head;
		while (nodePtr->next)
		{
			nodePtr = nodePtr->next;
		}

		nodePtr->next = newTnode;
		sizeOftList++;
	}
}

void ProcessTable::appendTableProcessList(int pID, string op, double para)
{
	ProcessTableNode *nodePtr;

	nodePtr = head;


	//search for process id in order to add proccess operations and parameters to the data table list.
	for (int i = 0; i < sizeOftList; i++)
	{
		if (nodePtr->processID == pID)
		{
			nodePtr->processList.appendNode(op, para);
		}

		else
			nodePtr = nodePtr->next;
	}
}

void ProcessTable::deleteProcess(int pID)
{
	ProcessTableNode *nodePtr;
	ProcessTableNode *prevPtr;
	bool found;

	if (head == NULL)
	{
		cout << "The list is empty. Cannot delete the process." << endl;
	}

	else
	{
		if (head->processID == pID)
		{
			nodePtr = head;
			head = head->next;
			delete nodePtr;
			sizeOftList--;
		}

		else
		{
			found = false;
			nodePtr = head->next;
			prevPtr = head;

			while (nodePtr != NULL && !found)
			{
				if (nodePtr->processID == pID)
				{
					found = true;
				}

				else
				{
					prevPtr = nodePtr;
					nodePtr = nodePtr->next;
				}
			}

			if (found == true)
			{
				prevPtr->next = nodePtr->next;
				sizeOftList--;
				delete nodePtr;
			}

		}
	}
}


void ProcessTable::setCoreStatus(bool isBusy, int core, double time, int pID)
{
	if (core == 1)
	{
		cores[0].ifBusy = isBusy;
		cores[0].busyUntil += time;
		cores[0].usedBy = pID;
	}

	else
	{
		cores[1].ifBusy = isBusy;
		cores[1].busyUntil += time;
		cores[1].usedBy = pID;
	}
}

void ProcessTable::freeCore(int core)
{
	cores[core - 1].ifBusy = false;
	cores[core - 1].busyUntil = 0;
	cores[core - 1].usedBy = -1;
}

bool ProcessTable::getCoreStatus(int core)
{
	if (core == 1)
	{
		return cores[0].ifBusy;
	}

	else
		return cores[1].ifBusy;

}

int ProcessTable::getCoreStatusTime(int core)
{
	if (core == 1)
	{
		return cores[0].busyUntil;
	}

	else
		return cores[1].busyUntil;

}


int ProcessTable::getCoreUsedBy(int core)
{
	if (core == 1)
	{
		return cores[0].usedBy;
	}

	else
		return cores[1].usedBy;
}
int ProcessTable::getNumOfBusyCores()
{
	if (cores[0].ifBusy == true && cores[1].ifBusy == true)
		return 2;

	else if (cores[0].ifBusy == true || cores[1].ifBusy == true)
		return 1;

	else
		return 0;

}

bool ProcessTable::isProcessTableEmpty()
{
	if (sizeOftList > 0)
		return false;
	else
		return true;
}

void ProcessTable::deleteProcessFromList(int pID) // check if deleting process id in the fucntion works
{
	ProcessTableNode *nodePtr;
	bool found = false;
	nodePtr = head;

	while (!found && nodePtr != NULL)
	{
		if (nodePtr->processID == pID)
		{
			nodePtr->processList.deleteFront();
			found = true;
		}

		else
			nodePtr = nodePtr->next;
	}
}

void ProcessTable::displayTable()
{
	ProcessTableNode *nodePtr;
	nodePtr = head;

	cout << "PROCESS TABLE:" << endl;

	while (nodePtr != NULL)
	{
		cout << "Process " << nodePtr->processID << " started at " << nodePtr->startT << ", got " << nodePtr->CoreTime << " ms of CORE time and is " << nodePtr->status << endl;
		nodePtr = nodePtr->next;
	}
}

void ProcessTable::setPriority(int pID, char p)
{
	ProcessTableNode *nodePtr;

	nodePtr = head;

	for (int i = 0; i < sizeOftList; i++)
	{
		if (nodePtr->processID == pID)
		{
			nodePtr->priority = p;
		}

		else
			nodePtr = nodePtr->next;
	}
}

char ProcessTable::getPriority(int pID)
{
	ProcessTableNode *nodePtr;

	nodePtr = head;


	//search for process id in order to add proccess operations and parameters to the data table list.
	for (int i = 0; i < sizeOftList; i++)
	{
		if (nodePtr->processID == pID)
		{
			return nodePtr->priority;
		}

		else
			nodePtr = nodePtr->next;
	}
}

string ProcessTable::getOpT(int pID)
{
	ProcessTableNode *nodePtr;

	nodePtr = head;


	//search for process id in order to add proccess operations and parameters to the data table list.
	for (int i = 0; i < sizeOftList; i++)
	{
		if (nodePtr->processID == pID)
		{
			return nodePtr->processList.getOp();
		}

		else
			nodePtr = nodePtr->next;
	}

	return "";
}

double ProcessTable::getParaT(int pID)
{
	ProcessTableNode *nodePtr;

	nodePtr = head;


	//search for process id in order to add proccess operations and parameters to the data table list.
	for (int i = 0; i < sizeOftList; i++)
	{
		if (nodePtr->processID == pID)
		{
			return nodePtr->processList.getPara();
		}

		else
			nodePtr = nodePtr->next;
	}
	return -1;
}

int ProcessTable::getSizeT_List()
{
	return sizeOftList;
}

void ProcessTable::addCoreTime(int pID, int time)
{
	ProcessTableNode *nodePtr;
	bool found = false;
	nodePtr = head;

	while (!found && nodePtr != NULL)
	{
		if (nodePtr->processID == pID)
		{
			nodePtr->CoreTime += time;
			found = true;
		}

		else
			nodePtr = nodePtr->next;
	}
}

void ProcessTable::setStatus(int pID, string status)
{
	ProcessTableNode *nodePtr;
	bool found = false;
	nodePtr = head;

	while (!found && nodePtr != NULL)
	{
		if (nodePtr->processID == pID)
		{
			nodePtr->status = status;
			found = true;
		}

		else
			nodePtr = nodePtr->next;
	}
}