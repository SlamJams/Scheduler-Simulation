#ifndef PROCESSTABLE_H
#define PROCESSTABLE_H
#include <string>
#include "DataTable.h"
#include "Queue.h"
using namespace std;



class ProcessTable : public DataTable
{

protected:
	struct ProcessTableNode
	{
		int processID;
		int startT;
		char priority;
		int CoreTime;
		string status;
		DataTable processList;
		ProcessTableNode *next;
	};
	
	struct core
	{
		bool ifBusy;
		int busyUntil;
		int usedBy;
	};
	


	core cores[2];


	ProcessTableNode *head;

	int sizeOftList;

public:

	ProcessTable();

	
	void appendTable(int, double);
	void appendTableProcessList(int, string, double);
	void deleteProcess(int pID);
	bool isProcessTableEmpty();
	void deleteProcessFromList(int);
	void displayTable();
	//set functions
	void setPriority(int, char);
	void setCoreStatus(bool isBusy, int core, double time, int);
	void freeCore(int);
	void addCoreTime(int, int);
	void setStatus(int, string);
	//get functions
	string getOpT(int);
	double getParaT(int);
	int getSizeT_List();
	char getPriority(int);
	bool getCoreStatus(int core);
	int getCoreStatusTime(int core);
	int getCoreUsedBy(int);
	int getNumOfBusyCores();
};

#endif