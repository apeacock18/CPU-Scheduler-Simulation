#pragma once

#include <vector>
using namespace std;

class Process {
private:
	int id;
	vector<int> bursts;
	int burst_index;

	int cpu_wait;
	int io_wait;
	int last_in_cpu;
	int last_in_io;

	int arrival_time;
	int exit_time;
	bool is_finished;

	int first_in_cpu;

public:
	Process(int id, int arrival_time, vector<int> bursts);

	int getId() { return id; }
	int getArrivalTime() { return arrival_time; }
	int getCpuWait() { return cpu_wait; }
	int getIoWait() { return io_wait; }
	bool isFinished() { return is_finished; }
	

	int cpu(int current_time);
	int io(int current_time);
	int executeBurst();

	void updateCpuWaitTime(int current_time);
	void updateIoWaitTime(int current_time);

	bool isCpuBurst();
	bool isIoBurst();

	int getResponseTime();
	int getTurnaroundTime();
};