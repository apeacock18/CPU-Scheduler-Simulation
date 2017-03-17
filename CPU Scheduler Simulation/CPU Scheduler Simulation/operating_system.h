#pragma once

#include <queue>
#include <unordered_map>

using namespace std;

class Scheduler;
class Process;

class OperatingSystem {
private:
	Scheduler* s;
	queue<Process*> io_queue;
	unordered_map<int, Process*> process_table;
	int processor_time;
	int current_time;

public:
	OperatingSystem();

	void generateStatistics();
	void readProcessesFromFile(string file_name);
	void runProcesses();

};