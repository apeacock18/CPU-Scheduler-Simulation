#pragma once
#include "scheduler.h"
#include <vector>
#include <queue>

class SmallestProcessNext : public Scheduler {
private:
	priority_queue<Process*> q;

public:
	//no arg construtor 
	SmallestProcessNext();

	//getters
	priority_queue<Process*> getPriorityQueue() {
		return q;
	}

	//setters
	void setPriortyQueue(priority_queue<Process*> q) {
		this->q = q;
	}

	//other functions
	Process* schedule();
	void addProcess(Process* p);


};