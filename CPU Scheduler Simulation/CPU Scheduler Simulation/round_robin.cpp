#pragma once
#include "round_robin.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

RoundRobin::RoundRobin() : Scheduler() {
	quantum = 5;
	counter = 0;
	isMFQ = false; 
}

//what process should be executed this cycle?
Process* RoundRobin::schedule() {
	if (!isMFQ) cout << "Scheduling Round Robin..." << endl;
	//if current process is not finished, has not hit an I/O burst, and has not exceeded the time quantum
	if (current_process && !current_process->isFinished() && counter < quantum && current_process->isCpuBurst()) {
		counter++;
		return current_process;
	}
	//it runs a cpu burst on return, so we need to start at 1
	counter = 1;
	if (!q.empty()) {
		cout << "Process switching..." << endl;
		if (current_process && !current_process->isFinished() && current_process->isCpuBurst()) {
			//place back if CPU time left
			if (!isMFQ)
				q.push(current_process);
			}

		do {
			current_process = q.front();
			q.pop();
		} while (current_process->isFinished() && !q.empty());
		if (current_process->isFinished()) current_process = nullptr;

		return current_process;
	}
	current_process = nullptr;
	return current_process;
}

void RoundRobin::addProcess(Process* p) {
	q.push(p);
}

int RoundRobin::getNumInReadyQueue() {
	return current_process ? q.size() + 1 : q.size();
}
