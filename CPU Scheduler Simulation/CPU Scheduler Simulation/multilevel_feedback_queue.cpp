#pragma once
#include "multilevel_feedback_queue.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

MultilevelFeedbackQueue::MultilevelFeedbackQueue() : Scheduler() {

}


Process* MultilevelFeedbackQueue::schedule() {
	cout << "Scheduling MLFQ..." << endl;
	return nullptr;
}

void MultilevelFeedbackQueue::addProcess(Process* p) {

}
