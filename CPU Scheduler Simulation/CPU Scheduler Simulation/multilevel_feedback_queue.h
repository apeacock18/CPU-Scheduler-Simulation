#pragma once
#include "scheduler.h"
#include <vector>
#include <queue>

class MultilevelFeedbackQueue : public Scheduler {
private:
	vector<queue<Process*>> queues;

public:
	//no arg construtor 
	MultilevelFeedbackQueue();

	//getters
	vector<queue<Process*>> getQueues() {
		return queues;
	}

	//setters
	void setPriortyQueue(vector<queue<Process*>> queues) {
		this->queues = queues;
	}

	Process* schedule();
	void addProcess(Process* p);
	int getNumInReadyQueue();

};