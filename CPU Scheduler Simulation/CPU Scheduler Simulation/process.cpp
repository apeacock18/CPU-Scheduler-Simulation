#include "process.h"
#include <iostream>

using namespace std;

Process::Process(int id, int arrival_time, vector<int> bursts) : bursts(bursts) {
	this->id = id;
	this->arrival_time = arrival_time;

	burst_index = 0;
	cpu_wait = 0;
	io_wait = 0;
	first_in_cpu = -1;
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

	if (last_in_cpu == -1) {
		first_in_cpu = current_time;
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
	//return size of next burst
	int new_value = --bursts[burst_index];
	//check if current burst has completed
	if (bursts[burst_index] <= 0) {
		//move to next burst
		++burst_index;
		//check if there is a next burst
		if (burst_index >= bursts.size()) {
			//if no next burst, process is finished
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

int Process::getResponseTime() {
	if (first_in_cpu == -1) {
		return -1;
	}
	else {
		return (first_in_cpu - arrival_time);
	}
}

int Process::getTurnaroundTime() {
	if (exit_time == -1) {
		return -1;
	}
	else {
		return (exit_time - arrival_time);
	}
}