#pragma once
#include "multilevel_feedback_queue.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

MultilevelFeedbackQueue::MultilevelFeedbackQueue() : Scheduler(), queues(3) {

}


Process* MultilevelFeedbackQueue::schedule() {
	cout << "Scheduling MLFQ..." << endl;
	return nullptr;
}

/*
Add a process back to the top queue 
*/
void MultilevelFeedbackQueue::addProcess(Process* p) { 
	queues[0].push(p);
}

int MultilevelFeedbackQueue::getNumInReadyQueue() {
	return 0;
}
