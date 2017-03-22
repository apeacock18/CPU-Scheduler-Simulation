#pragma once
#include "process.h"
using namespace std;

class Scheduler {
protected:
	Process* current_process;
	int current_core_index;
	int num_of_cores;

public:
	//constructor 
	Scheduler();

	//getters
	Process* getCurrentProcess() { return current_process;}

	//setters 
	void setCurrentProcess() { this->current_process = current_process; }

	//
	virtual Process* schedule() = 0;
	virtual void addProcess(Process* p) = 0;
	virtual int getNumInReadyQueue() = 0;

	/* 
	Increments CPU index using modular arithmetic.
	Do not call if schedule has already been called for the core this tick
	*/
	virtual void incrementCoreIndex();
};