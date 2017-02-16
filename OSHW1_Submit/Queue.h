#ifndef QUEUE_H
#define QUEUE_H

//Will be using a dynamic queue.

class Queue
{

private:
	struct QueNode
	{
		int IdNum;
		QueNode *next;
	};

	QueNode *front;
	QueNode *end;

	int NumInQue;

public:
	Queue();
	~Queue();

	void enQueue(int);
	void deQueue(int &val);
	bool isEmpty() const;
	void clear();
	void displayQue();

};

#endif