#pragma once
#include "scheduler.h"
#include <vector>
#include <queue>

class RoundRobin : public Scheduler {
private:
	/* Time slice to use when interrupting process */
	int quantum;
	/* Counts the number of ticks the process has been in the CPU */
	int counter;
	/* Ready queue for sheduler */
	queue<Process*> q;
	/* Flag for if Round Robin is used for multilevel feedback queue */
	bool isMFQ;

public:
	//no arg construtor 
	RoundRobin();
	//constructor when quantum is specified
	RoundRobin(int quantum);

	//getters
	queue<Process*> getQueue() {
		return q;
	}

	//setters
	void setQueue(queue<Process*> q) {
		this->q = q;
	}
	//for MFQ
	void setQuantum(int quantum) {
		this->quantum = quantum;
	}
	//set true when using MFQ algorithm 
	void setIsMFQ(bool isMFQ) {
		this->isMFQ = isMFQ;
	}
	//other functions
	Process* schedule();
	void addProcess(Process* p);
	int getNumInReadyQueue();

}; 
