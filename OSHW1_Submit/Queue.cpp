#include "Queue.h"
#include <iostream>
using namespace std;

Queue::Queue()
{
	front = NULL;
	end = NULL;
	NumInQue = 0;
}


Queue::~Queue()
{
	clear();
}

void Queue::enQueue(int Id)
{
	// Create a new node in order to insert into the link list;
	QueNode *newNode;
	newNode = new QueNode;
	newNode->IdNum = Id;
	newNode->next = NULL;


	//if linklist is empty/queue is empty. add the new node to the front of the list. Else add it to the end of the list.
	if (isEmpty())
	{
		front = newNode;
		end = newNode;
	}

	else
	{
		end->next = newNode;
		end = newNode;
	}

	NumInQue++;

}

void Queue::deQueue(int &val)
{
	QueNode *temp;

	if (isEmpty())
	{
		cout << "The queue is empty, cannot delete from queue." << endl;
	}

	else
	{
		val = front->IdNum;
		temp = front;
		front = front->next;
		delete temp;
	}

	NumInQue--;
}

bool Queue::isEmpty() const
{
	if (NumInQue > 0)
	{
		return false;
	}

	else
	{
		return true;
	}
}

void Queue::clear()
{
	int temp = 0;
	while (!isEmpty())
	{
		deQueue(temp);
	}
}

void Queue::displayQue()
{
	QueNode *nodePtr;

	if (NumInQue == 0)
	{
		cout << "empty" << endl;
	}

	else
	{
		nodePtr = front;

		for (int i = 0; i < NumInQue; i++)
		{
			cout << "Process " << nodePtr->IdNum << endl;
			nodePtr = nodePtr->next;
		}

	}
}
