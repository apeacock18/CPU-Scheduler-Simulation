#pragma once
#include "scheduler.h"
#include <vector>
#include <queue>

/** Comparator used to sort the SPN priority queue */
struct SPNComparator {
	bool operator()(Process* const lhs, Process* const rhs) const{
		return (lhs->getCurrentBurstLength() > rhs->getCurrentBurstLength());
	}
};

class SmallestProcessNext : public Scheduler {
private:
	/** Sorted on running time of current CPU burst */
	priority_queue<Process*, vector<Process*>, SPNComparator> q;

public:
	//no arg construtor 
	SmallestProcessNext();

	/**
	Returns a process to run on the CPU using an SPN algorithm
	Process is selected from the priority queue, sorted on running time of current CPU burst
	@return process to run, or nullptr if none are in the queue
	**/
	Process* schedule();

	/** Adds a process to the priority queue */
	void addProcess(Process* p);

	/** @return the number of processes in the priority queue */
	int getNumInReadyQueue();
};