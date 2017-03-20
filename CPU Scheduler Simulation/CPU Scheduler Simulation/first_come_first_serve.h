#pragma once
#include "scheduler.h"
#include <vector>
#include <queue>

class FirstComeFirstServe : public Scheduler {
private:
	queue<Process*> q;
	vector<Process*> multicore_processes;
	int num_of_cores;
	int current_core_index;

public:
	//no arg construtor 
	FirstComeFirstServe(int num_of_cores);

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
	int getNumInReadyQueue();


};