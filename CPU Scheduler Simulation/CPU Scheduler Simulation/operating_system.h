#pragma once

#include <queue>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "process.h"

class FCFS;
class RoundRobin;
class SmallestProcess;
class Multilevel;

using namespace std;

enum SchedulerType {
	FIRST_COME_FIRST_SERVE,
	ROUND_ROBIN,
	SMALLEST_PROCESS_NEXT,
	MULTILEVEL_FEEBACK_QUEUE
};

class Scheduler;
class Process;

class OperatingSystem {
private:
	Scheduler* s;
	queue<Process*> io_queue;
	unordered_map<int, Process*> process_table;
	int processor_time;
	int current_time;

	int generateRandomNumberInBounds(int min, int max);

public:
	OperatingSystem() {}
	/* Initializes class with scheduler 
	@param type The type of scheduler to create with the OS
	*/
	OperatingSystem(SchedulerType);

	/* Generates stats */
	void generateStatistics();

	/* Generates random processes and places the data in file_name */
	void generateProcessFile(string file_name, int num_processes);

	/* Reads process data from txt file and initializes process table */
	void readProcessesFromFile(string file_name);

	/* Execute all processes in the process table */
	void runProcesses();

	/* Generates stats */
	void initScheduler(SchedulerType);

};