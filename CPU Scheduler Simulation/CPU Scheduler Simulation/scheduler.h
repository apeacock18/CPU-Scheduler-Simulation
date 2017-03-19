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
	Process* getCurrentProcess() { return current_process;}

	//setters 
	void setCurrentProcess() { this->current_process = current_process; }

	//other functions
	virtual Process* schedule();
	virtual void addProcess(Process* p);
};