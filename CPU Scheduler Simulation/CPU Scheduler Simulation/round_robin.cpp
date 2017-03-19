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
	return nullptr;
}

void RoundRobin::addProcess(Process* p) {

}

int RoundRobin::getNumInReadyQueue() {
	return 0;
}
