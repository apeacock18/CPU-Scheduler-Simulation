#include "process.h"

using namespace std;

Process::Process(int id, int arrival_time, vector<int> bursts) : bursts(bursts) {
	this->id = id;
	this->arrival_time = arrival_time;

	burst_index = 0;
	cpu_wait = 0;
	io_wait = 0;
}

int Process::cpu() {

}

int Process::io() {

}

void Process::updateCpuWaitTime(int current_time) {

}

void Process::updateIoWaitTime(int current_time) {

}