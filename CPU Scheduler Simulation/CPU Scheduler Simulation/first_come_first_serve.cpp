#pragma once
#include "first_come_first_serve.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

FirstComeFirstServe::FirstComeFirstServe(int num_of_cores) : Scheduler(), q(), multicore_processes(num_of_cores, nullptr) {
	current_core_index = 0;
	this->num_of_cores = num_of_cores;

}


Process* FirstComeFirstServe::schedule() {
	cout << "Scheduling FCFS with " << num_of_cores << " cores..." << endl;
	Process* to_return = nullptr;

	if (multicore_processes[current_core_index] && multicore_processes[current_core_index]->isCpuBurst() && !multicore_processes[current_core_index]->isFinished()) {
		to_return = multicore_processes[current_core_index];
	}
	else if (!q.empty()) {
		multicore_processes[current_core_index] = q.front();
		q.pop();
		to_return = multicore_processes[current_core_index];
		to_return->setIsContextSwitching(true);
	}
	else {
		multicore_processes[current_core_index] = nullptr;
		to_return = multicore_processes[current_core_index];
	}

	//if a process is about to finish, remove it from the vector so we don't run it again accidentally
	if (to_return && to_return->getCurrentBurstLength() == 1 && !to_return->isContextSwitching()) {
		multicore_processes[current_core_index] = nullptr;
	}

	incrementCoreIndex();
	return to_return;
}

void FirstComeFirstServe::addProcess(Process* p) {
	q.push(p);
}

int FirstComeFirstServe::getNumInReadyQueue() {
	int num_in_multicore_processes = 0;
	for (int i = 0; i < num_of_cores; ++i) {
		if (multicore_processes[i] && !multicore_processes[i]->isFinished())
			++num_in_multicore_processes;
	}
	return q.size() + num_in_multicore_processes;
}
