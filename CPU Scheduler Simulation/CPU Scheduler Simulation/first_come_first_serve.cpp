#pragma once
#include "first_come_first_serve.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

FirstComeFirstServe::FirstComeFirstServe() : Scheduler(), q() {

}


Process* FirstComeFirstServe::schedule() {
	cout << "Scheduling FCFS..." << endl;

	if (current_process && current_process->isCpuBurst()) {
		return current_process;
	}

	else if (!q.empty()) {
		current_process = q.front();
		q.pop();
		return current_process;
	}
	else {
		current_process = nullptr;
		return current_process;
	}
	return nullptr;
}

void FirstComeFirstServe::addProcess(Process* p) {
	q.push(p);
}

int FirstComeFirstServe::getNumInReadyQueue() {
	return q.size();
}
