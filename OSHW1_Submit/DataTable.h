#ifndef DATATABLE_H
#define DATATABLE_H
#include <string>
using namespace std;



class DataTable
{

protected:
	struct Node
	{		
		string operation;
		double parameter;
		Node *next;
	};

	Node *head;

	int sizeOfList;

public:
	DataTable();
	~DataTable();

	void appendNode(string, int);
	string getOp();
	double getPara();
	bool deleteFront();
	bool isListEmpty();

};

#endif