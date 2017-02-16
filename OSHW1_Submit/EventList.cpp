#include "EventList.h"
#include <iostream>
using namespace std;

EventList::EventList()
{
	head = NULL;
	tail = NULL;
	count = 0;
}

EventList::~EventList()
{
	Enode *temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

void EventList::appendNode(int pID, double time, string type)
{
	Enode *newNode;
	Enode *nodePtr;
	Enode *nodePrev;
	bool found;

	newNode = new Enode;

	newNode->proccID = pID;
	newNode->timeDone = time;
	newNode->eventType = type;
	newNode->next = NULL;
	newNode->prev = NULL;



	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
		count++;
	}

	else
	{
		found = false;
		nodePtr = head;
		nodePrev = NULL;

		while (!found && nodePtr != NULL)
		{
			if (nodePtr->timeDone >= time)
			{
				found = true;
			}
			else
			{
				nodePrev = nodePtr;
				nodePtr = nodePtr->next;
			}
		}

		if (nodePtr == head)
		{
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
			count++;
		}
		else
		{
			if (nodePtr != NULL)
			{

				nodePrev->next = newNode;
				newNode->next = nodePtr;
				newNode->prev = nodePrev;
				nodePtr->prev = newNode;
			}
			else
			{
				nodePrev->next = newNode;
				newNode->prev = nodePrev;
				tail = newNode;
			}
			count++;
		}
	}
}

void EventList::deleteFront()
{
	Enode *temp;

	temp = head;

	if (temp == NULL)
	{
		cout << "Cannot delete from empty event list." << endl;
	}

	else
	{
		head = head->next;
		if (head != NULL)
		{
			head->prev = NULL;
		}
		delete temp;
		count--;
	}
}


EventData EventList::getData()
{
	EventData temp;
	Enode *nodePtr;

	if (count >= 2)
	{
		if (head->timeDone == head->next->timeDone)
		{
			if (head->eventType == "CORE")
			{
				temp.pID = head->proccID;
				temp.time = head->timeDone;
				deleteFront();
				return temp;
			}

			else if (head->next->eventType == "CORE")
			{
				if (count == 2) // make sure it works.
				{
					nodePtr = head;
					nodePtr->next = NULL;
					nodePtr->prev = head->next;
					head->next = nodePtr;
					head->prev = NULL;
					tail = nodePtr;



					temp.pID = head->proccID;
					temp.time = head->timeDone;
					deleteFront();
					return temp;
				}
				else
				{
					nodePtr = head;
					head = head->next;
					head->next->prev = nodePtr;
					nodePtr->next = head->next;
					nodePtr->prev = head;
					head->next = nodePtr;
					head->prev = NULL;

					temp.pID = head->proccID;
					temp.time = head->timeDone;
					deleteFront();
					return temp;
				}
			}
			else
			{
				temp.pID = head->proccID;
				temp.time = head->timeDone;
				deleteFront();
				return temp;
			}
		}
		else
		{
			temp.pID = head->proccID;
			temp.time = head->timeDone;
			deleteFront();
			return temp;
		}
	}
	else
	{
		temp.pID = head->proccID;
		temp.time = head->timeDone;
		deleteFront();
		return temp;
	}

}

bool EventList::isListEmpty()
{
	if (count < 1)
		return true;
	else
		return false;
}
