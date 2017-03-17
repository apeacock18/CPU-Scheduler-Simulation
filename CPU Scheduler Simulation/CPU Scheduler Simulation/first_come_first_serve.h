#pragma once
#include "scheduler.h"
#include <vector>
#include <queue>

class FirstComeFirstServe : public Scheduler {
private:
	queue<Process*> q;

public:
	//no arg construtor 
	FirstComeFirstServe() {}

	//getters
	queue<Process*> getQueues() {
		return q;
	}

	//setters
	void setPriortyQueue(queue<Process*> q) {
		this->q = q;
	}

	//other functions
	Process* schedule();
	void addProcess(Process* p);


};