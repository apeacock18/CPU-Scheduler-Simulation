#pragma once
#include "scheduler.h"
#include <vector>
#include <queue>

class RoundRobin : public Scheduler {
private:
	int quantum;
	int counter;
	queue<Process*> q;

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

	//other functions
	Process* schedule();
	void addProcess(Process* p);


}; 
