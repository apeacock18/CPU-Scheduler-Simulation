#pragma once
#include "multilevel_feedback_queue.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

MultilevelFeedbackQueue::MultilevelFeedbackQueue() : Scheduler(), schedulers(3) {
	last_process = nullptr;
	current_scheduler_index = 0;
	last_scheduler_index = -1;

	schedulers[0].setQuantum(5);
	schedulers[1].setQuantum(10);
	schedulers[2].setQuantum(20);
	schedulers[0].setIsMFQ(true);
	schedulers[1].setIsMFQ(true);
	schedulers[2].setIsMFQ(false); //stay in the last queue if it needs more time and has not had an I/O burst
}


Process* MultilevelFeedbackQueue::schedule() {
	//TODO: acting preemptive, do we want it to be nonpreemptive?
	cout << "Scheduling MLFQ..." << endl;
	Process* p = nullptr;
	//run through the first queue if there are still processes in the queue
	if (schedulers[0].getNumInReadyQueue() > 0) {
		cout << "From queue 1" << endl;
		current_scheduler_index = 0;
		p = schedulers[0].schedule();
	}
	//if the first queue is empty, move to the second queue and run processes 
	if (p == nullptr && schedulers[1].getNumInReadyQueue() > 0) {
		cout << "From queue 2 " << endl;
		current_scheduler_index = 1;
		p = schedulers[1].schedule();
	}
	//if the first two queues are empty, run the third queue if it has processes
	if (p == nullptr && schedulers[2].getNumInReadyQueue() > 0 ) {
		cout << "From queue 3 " << endl;
		current_scheduler_index = 2;
		p = schedulers[2].schedule();
	}
	
	//if the process changed and it wasn't at the last queue and it isn't finished and it is still cpu
	if (p != last_process && last_scheduler_index < 2 && last_process != nullptr && !last_process->isFinished() && last_process->isCpuBurst()) {
		//add last_process to next queue down
		schedulers[last_scheduler_index + 1].addProcess(last_process);
	}


	last_process = p;
	last_scheduler_index = current_scheduler_index;
	return p;
}

/*
Add a process back to the top queue 
*/
void MultilevelFeedbackQueue::addProcess(Process* p) { 
	schedulers[0].addProcess(p);
}

int MultilevelFeedbackQueue::getNumInReadyQueue() {
	return schedulers[0].getNumInReadyQueue() + schedulers[1].getNumInReadyQueue() + schedulers[2].getNumInReadyQueue();
}
