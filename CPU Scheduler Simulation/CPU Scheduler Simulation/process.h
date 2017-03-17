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
	int arrival_time;
	int exit_time;

public:
	Process(int id, int arrival_time, vector<int> bursts);

	int getId() { return id; }
	int getArrivalTime() { return arrival_time; }
	int getCpuWait() { return cpu_wait; }
	int getIoWait() { return io_wait; }
	

	int cpu();
	int io();
	void updateCpuWaitTime(int current_time);
	void updateIoWaitTime(int current_time);
};