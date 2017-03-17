#pragma once
#include "smallest_process_next.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

SmallestProcessNext::SmallestProcessNext() : Scheduler() {

}


Process* SmallestProcessNext::schedule() {
	cout << "Scheduling SPN..." << endl;
	return nullptr;
}

void SmallestProcessNext::addProcess(Process* p) {

}
