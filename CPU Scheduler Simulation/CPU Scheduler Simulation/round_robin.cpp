#pragma once
#include "round_robin.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

RoundRobin::RoundRobin() : Scheduler() {
	quantum = 5;
	counter = 0;
}


Process* RoundRobin::schedule() {
	cout << "Scheduling Round Robin..." << endl;
	if (current_process && !current_process->isFinished() && counter < quantum) {
		counter++;
		return current_process;
	}
	counter = 0;
	if (!q.empty()) {
		cout << "Process switching..." << endl;
		if (current_process != nullptr && !current_process->isFinished()) {
			q.push(current_process);
		}
		current_process = q.front();
		q.pop();
		return current_process;
	}
	current_process = nullptr;
	return current_process;
}

void RoundRobin::addProcess(Process* p) {
	q.push(p);
}

int RoundRobin::getNumInReadyQueue() {
	return q.size();
}
