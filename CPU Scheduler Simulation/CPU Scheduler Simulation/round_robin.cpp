#pragma once
#include "round_robin.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

RoundRobin::RoundRobin() : Scheduler() {

}


Process* RoundRobin::schedule() {
	cout << "Scheduling Round Robin..." << endl;
	if (!q.empty()) {
		Process* p = q.front();
		q.pop();
		return p;
	}
	return nullptr;
}

void RoundRobin::addProcess(Process* p) {
	q.push(p);
}

int RoundRobin::getNumInReadyQueue() {
	return q.size();
}
