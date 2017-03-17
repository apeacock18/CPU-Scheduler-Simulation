#pragma once
#include "multilevel_feedback_queue.h"
#include <vector>
#include <queue>

using namespace std;

MultilevelFeedbackQueue::MultilevelFeedbackQueue() : Scheduler() {

}


Process* MultilevelFeedbackQueue::schedule() {
	return nullptr;
}

void MultilevelFeedbackQueue::addProcess(Process* p) {

}
