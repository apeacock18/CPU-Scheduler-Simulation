#pragma once

//verbose logs for testing
#define LOG_VERBOSE

#include <queue>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "process.h"
#include "scheduler.h"
#include "first_come_first_serve.h"
#include "round_robin.h"
#include "smallest_process_next.h"
#include "multilevel_feedback_queue.h"

using namespace std;

enum SchedulerType {
	FIRST_COME_FIRST_SERVE,
	ROUND_ROBIN_QUANTUM_5,
	ROUND_ROBIN_QUANTUM_20,
	SMALLEST_PROCESS_NEXT,
	MULTILEVEL_FEEBACK_QUEUE,
	FOUR_CORE_FCFS,
	EIGHT_CORE_FCFS
	
};

/* Comparator used to sort arrival_queue */
struct ArrivalComparator {
	bool operator()(Process* const lhs, Process* const rhs) const {
		return (lhs->getArrivalTime() > rhs->getArrivalTime());
	}
};

class OperatingSystem {
private:
	Scheduler* s;
	string sched_type;
	queue<Process*> io_queue;
	unordered_map<int, Process*> process_table;
	/* Contains a pointer to every process, sorted by arrival time */
	priority_queue<Process*, vector<Process*>, ArrivalComparator> arrival_queue;
	/* Accumulated processor time across simulation */
	int processor_time;
	int current_time;
	/* Accumulated idle time across simulation */
	int idle_time;
	int num_of_cores;

	int generateRandomNumberInBounds(int min, int max);
	/* Initializes arrival_queue */
	void initializeArrivalQueue();
	/* Adds a process to the scheduler if its arrival time matches the current time */
	void checkForNewlyArrivedProcesses();
	/* @return true if all processes have arrived */
	bool allProcessesHaveArrived();

public:
	OperatingSystem() {}
	/* Initializes class with scheduler 
	@param type The type of scheduler to create with the OS
	*/
	OperatingSystem(SchedulerType);

	~OperatingSystem();

	/* Generates stats */
	void generateStatistics();

	/* Generates random processes and places the data in file_name */
	void generateProcessFile(string file_name, int num_processes);

	/* Reads process data from txt file and initializes process table */
	void readProcessesFromFile(string file_name);

	/* Execute all processes in the process table */
	void runProcesses();

	/* Decrements current IO burst on process at front of queue and removes from queue if finished with IO */
	void updateIoQueue();

};