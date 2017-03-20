#pragma once
#include "scheduler.h"
#include <vector>
#include <queue>

class RoundRobin : public Scheduler {
private:
	int quantum;
	int counter;
	queue<Process*> q;
	bool isMFQ;

public:
	//no arg construtor 
	RoundRobin();

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
