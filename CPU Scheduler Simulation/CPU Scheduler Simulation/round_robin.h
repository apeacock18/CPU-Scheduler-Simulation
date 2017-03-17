#pragma once
#include "scheduler.h"
#include <vector>
#include <queue>

class RoundRobin : public Scheduler {
private:
	int quantum;
	int counter;
	vector<queue<Process*>> queues;

public:
	//no arg construtor 
	RoundRobin() {}

	//getters
	vector<queue<Process*>> getQueues() {
		return queues;
	}

	//setters
	void setPriortyQueue(vector<queue<Process*>> queues) {
		this->queues = queues;
	}

	//other functions
	Process* schedule();
	void addProcess(Process* p);


}; 
