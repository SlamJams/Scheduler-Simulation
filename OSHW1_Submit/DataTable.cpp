#include "Queue.h"
#include <iostream>
#include <string>
#include "DataTable.h"
using namespace std;

DataTable::DataTable()
{
	head = NULL;
	sizeOfList = 0;
}

DataTable::~DataTable()
{
	Node *temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

void DataTable::appendNode(string op, int num)
{
	Node *newNode;
	Node *nodePtr;

	newNode = new Node;
	newNode->operation = op;
	newNode->parameter = num;
	newNode->next = NULL;

	if (head == NULL)
	{
		head = newNode;
		sizeOfList++;
	}

	else
	{
		nodePtr = head;
		while (nodePtr->next)
		{
			nodePtr = nodePtr->next;
		}

		nodePtr->next = newNode;
		sizeOfList++;
	}
}

string DataTable::getOp()
{
	return head->operation;
}

double DataTable::getPara()
{

	return head->parameter;
}


bool DataTable::deleteFront()
{
	Node *temp;

	temp = head;

	if (temp == NULL)
	{
		return isListEmpty();
	}

	else
	{
		head = head->next;
		delete temp;
		sizeOfList--;
		return isListEmpty();
	}
}

bool DataTable::isListEmpty()
{
	if (head == NULL)
		return true;
	else
		return false;
}
