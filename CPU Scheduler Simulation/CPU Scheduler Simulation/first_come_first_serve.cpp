#pragma once
#include "first_come_first_serve.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

FirstComeFirstServe::FirstComeFirstServe() : Scheduler() {

}


Process* FirstComeFirstServe::schedule() {
	cout << "Scheduling FCFS..." << endl;
	return nullptr;
}

void FirstComeFirstServe::addProcess(Process* p) {

}
