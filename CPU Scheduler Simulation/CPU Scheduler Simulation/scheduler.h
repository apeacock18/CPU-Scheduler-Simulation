#pragma once
#include "process.h"
using namespace std;

class Scheduler {
protected:
	Process* current_process;

public:
	//constructor 
	Scheduler();

	//getters
	//Process* getCurrentProcess() { return Process* p;}

	//setters 
	void setCurrentProcess() { this->current_process = current_process; }

	/* @return the process that should be currently running on the CPU */
	virtual Process* schedule() = 0;
	/* Add a process to the scheduler's ready queue */
	virtual void addProcess(Process* p) = 0;
	/* @return the number of processes in the scheduler's ready queue */
	virtual int getNumInReadyQueue() = 0;
};