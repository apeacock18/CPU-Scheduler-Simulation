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

RoundRobin::RoundRobin(int quantum) : Scheduler() {
	this->quantum = quantum;
	counter = 0;
	isMFQ = false;
}

//what process should be executed this cycle?
Process* RoundRobin::schedule() {
	if (!isMFQ) cout << "Scheduling Round Robin..." << endl;
	//if current process is not finished, has not hit an I/O burst, and has not exceeded the time quantum
	bool current_process_is_valid = current_process && !current_process->isFinished() && current_process->isCpuBurst();
	if (current_process_is_valid && counter < quantum) {
		//increase amount of time taken and keep current_process the same
		counter++;
	}
	else {
		//it runs a cpu burst on return, so we need to start at 1
		counter = 1;
		if (!q.empty()) {
			//if the current process exceeded the quantum but is otherwise okay...
			if (current_process_is_valid) {
				//place back if CPU time left
				//if used in a MFQ, the MFQ scheduler will take care of putting it back in the queue
				if (!isMFQ)
					q.push(current_process);
			}

			//pick a process from the queue until you find a valid one or the queue empties
			bool process_is_invalid = false;
			do {
				current_process = q.front();
				q.pop();
				process_is_invalid = current_process->isFinished() || current_process->isIoBurst();
			} while (process_is_invalid && !q.empty());
			//to take care of the possibility that we have an empty queue and the last process was unfinished
			if (process_is_invalid) {
				current_process = nullptr;
			}
		}
		else {
			current_process = nullptr;
		}
	}
	return current_process;
}

void RoundRobin::addProcess(Process* p) {
	q.push(p);
}

int RoundRobin::getNumInReadyQueue() {
	return current_process ? q.size() + 1 : q.size();
}
