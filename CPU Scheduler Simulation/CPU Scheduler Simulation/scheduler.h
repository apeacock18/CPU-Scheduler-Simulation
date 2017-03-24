#pragma once
#include "process.h"
using namespace std;

class Scheduler {
protected:
	/* Current process selected by scheduler for current cycle */
	Process* current_process;
	/* Index of current processor core */
	int current_core_index;
	/* Number of cores */
	int num_of_cores;

public:
	//constructor 
	Scheduler();

	//getters
	Process* getCurrentProcess() { return current_process;}

	//setters 
	void setCurrentProcess() { this->current_process = current_process; }

	//others
	virtual Process* schedule() = 0;
	virtual void addProcess(Process* p) = 0;
	virtual int getNumInReadyQueue() = 0;

	/* 
	Increments CPU index using modular arithmetic.
	Do not call if schedule has already been called for the core this tick
	*/
	virtual void incrementCoreIndex();
};