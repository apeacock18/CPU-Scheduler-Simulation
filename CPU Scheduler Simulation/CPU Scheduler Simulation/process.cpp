#include "process.h"
#include <iostream>

using namespace std;

Process::Process(int id, int arrival_time, vector<int> bursts) : bursts(bursts) {
	this->id = id;
	this->arrival_time = arrival_time;

	burst_index = 0;
	cpu_wait = 0;
	io_wait = 0;
	last_in_cpu = -1;
	last_in_io = -1;
	is_finished = false;
}

int Process::cpu(int current_time) {
	if (!isCpuBurst()) {
		cout << "Tried to call cpu when it was io\n";
		cout << "Calling io instead...\n";
		return io(current_time);
	}

	last_in_cpu = current_time;

	return executeBurst();
}

int Process::io(int current_time) {
	if (!isIoBurst()) {
		cout << "Tried to call io when it was cpu\n";
		cout << "Calling cpu instead...\n";
		return cpu(current_time);
	}

	last_in_io = current_time;

	return executeBurst();
}

int Process::executeBurst() {
	int new_value = --bursts[burst_index];

	if (bursts[burst_index] <= 0) {
		++burst_index;

		if (burst_index >= bursts.size()) {
			is_finished = true;
		}
	}

	return new_value;
}

void Process::updateCpuWaitTime(int current_time) {
	if (last_in_cpu == -1) {
		cpu_wait = current_time;
	} 
	else {
		cpu_wait += (current_time - last_in_cpu);
	}	
}

void Process::updateIoWaitTime(int current_time) {
	if (last_in_io == -1) {
		io_wait = current_time;
	}
	else {
		io_wait += (current_time - last_in_io);
	}
}

bool Process::isCpuBurst() {
	return (burst_index % 2 == 0);
}

bool Process::isIoBurst() {
	return !isCpuBurst();
}