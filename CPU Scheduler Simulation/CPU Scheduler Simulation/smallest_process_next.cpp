#pragma once
#include "smallest_process_next.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

SmallestProcessNext::SmallestProcessNext() : Scheduler(), q() {
	
}


Process* SmallestProcessNext::schedule() {
	cout << "Scheduling SPN..." << endl;
	//If current process is still running on the CPU, let it keep running
	if (current_process && current_process->isCpuBurst()) {
		return current_process;
	}
	//Otherwise, if we have more processes in the queue...
	else if (!q.empty()) {
		current_process = q.top();
		q.pop();
		return current_process;
	}
	//Otherwise, return set current_process to nullptr - no processes left to run (for now)
	else {
		current_process = nullptr;
		return current_process;
	}
}

void SmallestProcessNext::addProcess(Process* p) {
	q.push(p);
}
