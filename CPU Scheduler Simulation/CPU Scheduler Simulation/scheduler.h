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
	Process* getCurrentProcess() { return current_process;}

	//setters 
	void setCurrentProcess() { this->current_process = current_process; }

	//
	virtual Process* schedule();
	virtual void addProcess(Process* p);
};