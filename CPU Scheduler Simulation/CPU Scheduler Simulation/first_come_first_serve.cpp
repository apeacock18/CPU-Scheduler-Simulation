#pragma once
#include "first_come_first_serve.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

FirstComeFirstServe::FirstComeFirstServe(int num_of_cores = 1) : Scheduler(), q(), multicore_processes(num_of_cores, nullptr) {
	current_core_index = 0;

}


Process* FirstComeFirstServe::schedule() {
	cout << "Scheduling FCFS..." << endl;
	Process* to_return = nullptr;

	if (multicore_processes[current_core_index] && multicore_processes[current_core_index]->isCpuBurst()) {
		to_return = multicore_processes[current_core_index];
	}
	else if (!q.empty()) {
		multicore_processes[current_core_index] = q.front();
		q.pop();
		to_return = multicore_processes[current_core_index];
	}
	else {
		multicore_processes[current_core_index] = nullptr;
		to_return = multicore_processes[current_core_index];
	}

	current_core_index = (current_core_index + 1) % multicore_processes.size();
	return to_return;
}

void FirstComeFirstServe::addProcess(Process* p) {
	q.push(p);
}

int FirstComeFirstServe::getNumInReadyQueue() {
	return q.size();
}
