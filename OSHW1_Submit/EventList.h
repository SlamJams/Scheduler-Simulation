#ifndef EVENT_H
#define EVENT_H
#include <string>
using namespace std;


	struct EventData
	{
		int pID;
		double time;
	};

class EventList
{

protected:
	struct Enode
	{
		int proccID;
		double timeDone;
		string eventType;
		Enode *next;
		Enode *prev;
	};

	Enode *head;
	Enode *tail;
	int count;


public:

	EventList();
	~EventList();

	void appendNode(int, double, string type);
	void deleteFront();
	EventData getData();
	bool isListEmpty();


};

#endif