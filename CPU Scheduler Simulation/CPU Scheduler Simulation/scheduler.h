#pragma once
#include "process.h"
using namespace std;

class Scheduler {
private:
	Process* current_process;

public:
	//constructor 
	Scheduler();

	//getters
	//Process* getCurrentProcess() { return Process* p;}

	//setters 
	void setCurrentProcess() { this->current_process = current_process; }

	//
	virtual Process* schedule();
	virtual void addProcess(Process* p);
};