#pragma once

#include <vector>
using namespace std;

class Process {
private:
	int id;
	/* holds alternating cpu and io burst values */
	vector<int> bursts;
	/* index of current burst in burst vector */
	int burst_index;

	/* total accumulated CPU wait time */
	int cpu_wait;
	/* total accumulated IO wait time */
	int io_wait;
	/* the last time the process was in the CPU */
	int last_in_cpu;
	/* the last time the process was in IO */
	int last_in_io;

	/* the time the process arrives */
	int arrival_time;
	/* the time the process finishes */
	int exit_time;
	/* whether the process is completely done executing */
	bool is_finished;

	/* the time the process first enters the cpu */
	int first_in_cpu;

	/* executes a burst by decrementing the current burst in the vector */
	int executeBurst();

public:
	Process(int id, int arrival_time, vector<int> bursts);

	//getters
	int getId() const { return id; }
	int getArrivalTime() const { return arrival_time; }
	int getCpuWait() const { return cpu_wait; }
	int getIoWait() const { return io_wait; }
	bool isFinished() const { return is_finished; }
	int getCurrentBurstLength() const { return bursts[burst_index]; }
	
	int getBurstIndex() const { return burst_index; }

	/**
	Runs CPU burst.
	@returns time remaining in current burst
	**/
	int cpu(int current_time);
	/**
	Runs IO burst.
	@returns time remaining in current burst
	**/
	int io(int current_time);

	/* Updates this process's CPU wait time */
	void updateCpuWaitTime(int current_time);
	/* Updates this process's IO wait time */
	void updateIoWaitTime(int current_time);

	/* @returns true if the process is currently on a CPU burst */
	bool isCpuBurst();
	/* @returns true if the process is currently on an IO burst */
	bool isIoBurst();

	/* @returns -1 if the process hasn't run yet, and the response time if it has */
	int getResponseTime();
	/* @returns -1 if the process isn't finished yet, and the turnaround time if it has */
	int getTurnaroundTime();

	/* Override comparator to sort on arrival_time */
	bool operator<(const Process &other) const {
		return arrival_time < other.arrival_time;
	}
};