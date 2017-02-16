/*
Brian Najera
Student ID : 1174483
COSC 3360 Assigntment 1
Due : 2/17/2016

*/

#include <iostream>
#include <string>
#include "DataTable.h"
#include "Queue.h"
#include "ProcessTable.h"
#include "EventList.h"
#include <iomanip>

using namespace std;



struct diskD
{
	bool isDbusy;
	int dBusyUntil;
};

int main()
{
	ProcessTable Scheduler;
	string line = "";
	int processID = 0;
	string operation = "";
	double parameter = 0;
	double totalCoreTime = 0;
	int systemTime = 0;
	int checkSysTime = 0;
	int index = 0;
	double clock = 0;
	int pID = 0;
	EventList Event;
	EventData EventInfo;
	EventInfo.pID = -1;
	EventInfo.time = 0;
	Queue HighPQueue;
	Queue LowPQueue;
	Queue DiskQueue;
	diskD Disk;
	Disk.dBusyUntil = 0;
	Disk.isDbusy = false;

	while (cin >> operation) // stores the files into a two dimensional linked list; The first link list holds the operations and parameters. The second link list holds the other link list and assigns the process number to it.
	{
		if (operation == "END")
		{
			Scheduler.appendTableProcessList(processID, operation, -1);
			processID++;
		}
		else
			cin >> parameter;

		if (operation == "START")
		{
			Scheduler.appendTable(processID, parameter);
			Scheduler.appendTableProcessList(processID, operation, parameter);
			Event.appendNode(processID, parameter, "START");
		}
		else
		{
			Scheduler.appendTableProcessList(processID, operation, parameter);
		}
	}

	while (!(Scheduler.isProcessTableEmpty()))
	{

		if (Event.isListEmpty() != true) // every time an event happends it is stored in the sorted linked list. Every loop returns the front of that link list.
		{
			EventInfo = Event.getData();
			operation = Scheduler.getOpT(EventInfo.pID);
			parameter = Scheduler.getParaT(EventInfo.pID);


			if (operation == "CORE") // frees the core when it is done and gives it to the process that is in high priority queue first, if high priority queue is empty, the process in the low priority queue gets the core. 
			{
				// The process that is done with the core moves on with the next operation.
				int coreNum;
				totalCoreTime += Scheduler.getParaT(EventInfo.pID);
				if (EventInfo.time == Scheduler.getCoreStatusTime(1))
				{
					Scheduler.freeCore(1);
					coreNum = 1;
				}

				else
				{
					Scheduler.freeCore(2);
					coreNum = 2;
				}


				if (HighPQueue.isEmpty() != true)
				{
					int id;
					HighPQueue.deQueue(id);
					//Scheduler.addCoreTime(id, Scheduler.getParaT(id));
					Scheduler.setStatus(id, "RUNNING");
					Scheduler.setCoreStatus(true, coreNum, EventInfo.time + Scheduler.getParaT(id), EventInfo.pID);
					Event.appendNode(id, EventInfo.time + Scheduler.getParaT(id), "CORE");
				}
				else if (LowPQueue.isEmpty() != true)
				{
					int id;
					LowPQueue.deQueue(id);
					//Scheduler.addCoreTime(id, Scheduler.getParaT(id));
					Scheduler.setStatus(id, "RUNNING");
					Scheduler.setCoreStatus(true, coreNum, EventInfo.time + Scheduler.getParaT(id), EventInfo.pID);
					Event.appendNode(id, EventInfo.time + Scheduler.getParaT(id), "CORE");

				}

				Scheduler.deleteProcessFromList(EventInfo.pID);
				operation = Scheduler.getOpT(EventInfo.pID);

			}

			else if (operation == "DISK") // Frees the disk event. If there is a process waiting to get the disk, it gets a hold of the disk as soon as it frees up. The process that completed the disk operation get set to low priority and requests the core next.
			{

				Disk.isDbusy = false;

				if (DiskQueue.isEmpty() != true)
				{
					int id;
					DiskQueue.deQueue(id);
					Disk.isDbusy = true;
					Scheduler.setStatus(id, "WAITING");
					Event.appendNode(id, EventInfo.time + Scheduler.getParaT(id), "DISK");
				}

				Scheduler.deleteProcessFromList(EventInfo.pID);
				operation = Scheduler.getOpT(EventInfo.pID);
				Scheduler.setPriority(EventInfo.pID, 'L');


			}

			else if (operation == "I/O")
			{
				Scheduler.deleteProcessFromList(EventInfo.pID);
				operation = Scheduler.getOpT(EventInfo.pID);
				Scheduler.setPriority(EventInfo.pID, 'H');
			}
		}



		if (operation == "START") // If the process starts. Set priority to high and get next operation which is a CORE operation.
		{
			Scheduler.setPriority(EventInfo.pID, 'H');
			Scheduler.deleteProcessFromList(EventInfo.pID);
			operation = Scheduler.getOpT(EventInfo.pID);
		}


		if (operation == "DISK") // If the operation requests the disk, check if it is zero delay access or not.
		{
			if (Scheduler.getParaT(EventInfo.pID) == 0) // If it is zero delay acess. The priority immediately gets set to Low priorty and goes on to request a CORE. 
			{
				Scheduler.deleteProcessFromList(EventInfo.pID);
				operation = Scheduler.getOpT(EventInfo.pID);
				Scheduler.setPriority(EventInfo.pID, 'L');
			}

			else if (Disk.isDbusy == true)	// If the disk is busy, add the operation to the disk queue.
			{
				DiskQueue.enQueue(EventInfo.pID);
			}

			else // else get access to the disk, set the disk to busy, and add the event completion time to the event list. Set process status to waiting.
			{
				Disk.isDbusy = true;
				Event.appendNode(EventInfo.pID, EventInfo.time + Scheduler.getParaT(EventInfo.pID), "DISK");
				Scheduler.setStatus(EventInfo.pID, "WAITING");
			}
		}

		if (operation == "I/O") // Add the i/o event completion time to the event list and sets the process status to waiting.
		{
			Event.appendNode(EventInfo.pID, EventInfo.time + Scheduler.getParaT(EventInfo.pID), "I/O");
			Scheduler.setStatus(EventInfo.pID, "WAITING");
		}


		if (operation == "CORE") // If the process wants a core.
		{
			Scheduler.addCoreTime(EventInfo.pID, Scheduler.getParaT(EventInfo.pID));
			if (Scheduler.getCoreStatus(1) == true && Scheduler.getCoreStatus(2) == true) // if both cores are busy, put the process in queue depending on the priority. Else get core.
			{
				if (Scheduler.getPriority(EventInfo.pID) == 'H')
				{
					HighPQueue.enQueue(EventInfo.pID);
					Scheduler.setStatus(EventInfo.pID, "READY");
				}
				else
				{
					LowPQueue.enQueue(EventInfo.pID);
					Scheduler.setStatus(EventInfo.pID, "READY");
				}
			}
			else																								// I only update the core usage of each process if they get a hold of a core, not when it requests the core and gets put in the queue.
			{
				//Scheduler.addCoreTime(EventInfo.pID, Scheduler.getParaT(EventInfo.pID)); 
				Scheduler.setStatus(EventInfo.pID, "RUNNING");
				if (Scheduler.getCoreStatus(1) == false)
				{
					Scheduler.setCoreStatus(true, 1, EventInfo.time + Scheduler.getParaT(EventInfo.pID), EventInfo.pID);
					clock = EventInfo.time + Scheduler.getParaT(EventInfo.pID);
					Event.appendNode(EventInfo.pID, clock, "CORE");
				}
				else
				{
					Scheduler.setCoreStatus(true, 2, EventInfo.time + Scheduler.getParaT(EventInfo.pID), EventInfo.pID);
					clock = EventInfo.time + Scheduler.getParaT(EventInfo.pID);
					Event.appendNode(EventInfo.pID, clock, "CORE");
				}
			}
		}// end core main if


		if (operation == "END") // deleted the process from the process table and displays all the information regarding queues, cores, and processes.
		{
			Scheduler.setStatus(EventInfo.pID, "TERMINATED");
			double AvgCoreTime = totalCoreTime / EventInfo.time;
			int time = EventInfo.time;
			cout << endl;
			cout << "CURRENT STATE OF THE SYSTEM AT TIME " << time << endl;
			cout << "Current number of busy cores: " << Scheduler.getNumOfBusyCores() << endl;
			cout << "Average number of busy cores: " << std::setprecision(4) << AvgCoreTime << endl;
			cout << "HIGH-PRIORITY READY QUEUE:" << endl;
			HighPQueue.displayQue();
			cout << "LOW-PRIORITY READY QUEUE:" << endl;
			LowPQueue.displayQue();
			cout << "DISK QUEUE:" << endl;
			DiskQueue.displayQue();
			Scheduler.displayTable();
			cout << endl;
			Scheduler.deleteProcess(EventInfo.pID);

		}

	}


	return 0;
}

