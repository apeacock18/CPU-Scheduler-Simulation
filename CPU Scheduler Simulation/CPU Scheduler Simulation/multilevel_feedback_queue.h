#pragma once
#include "scheduler.h"
#include "round_robin.h"
#include <vector>
#include <queue>

class MultilevelFeedbackQueue : public Scheduler {
private:
	vector<RoundRobin> schedulers;
	Process* last_process;
	int current_scheduler_index;
	int last_scheduler_index;

public:
	//no arg construtor 
	MultilevelFeedbackQueue();

	//getters
	vector<RoundRobin> getSchedulers() {
		return schedulers;
	}
	Process* lastProcess() {
		return last_process;
	}

	//setters
	void setPriortyQueue(vector<RoundRobin> schedulers) {
		this->schedulers = schedulers;
	}
	void setLastProcessPointer(Process* last_process) {
		this->last_process = last_process;
	}

	Process* schedule();
	void addProcess(Process* p);
	int getNumInReadyQueue();

};