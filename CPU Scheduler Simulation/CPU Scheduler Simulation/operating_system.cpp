#include "operating_system.h"

using namespace std;

int OperatingSystem::generateRandomNumberInBounds(int min, int max) {
	return rand() % (max - min) + min;
}

void OperatingSystem::initializeArrivalQueue() {
	//load initial processes to scheduler
	unordered_map<int, Process*>::iterator it = process_table.begin();
	//add to priority queue sorted by arrival time
	for (it; it != process_table.end(); ++it) {
		arrival_queue.push(it->second);
	}
}

void OperatingSystem::checkForNewlyArrivedProcesses() {
	if (!allProcessesHaveArrived()) {
		Process* earliest = arrival_queue.top();
		if (current_time == earliest->getArrivalTime()) {
			cout << "Adding process #" << earliest->getId() << " to scheduler" << endl;
			s->addProcess(earliest);
			arrival_queue.pop();
		}
	}
}

bool OperatingSystem::allProcessesHaveArrived(){
	return (arrival_queue.empty());
}

OperatingSystem::OperatingSystem(SchedulerType type) {
	switch (type)
	{
	case FIRST_COME_FIRST_SERVE:
		sched_type = "FIRST_COME_FIRST_SERVE";
		s = new FirstComeFirstServe(1);
		num_of_cores = 1;
		break;
	case FOUR_CORE_FCFS:
		sched_type = "FOUR_CORE_FCFS";
		s = new FirstComeFirstServe(4);
		num_of_cores = 4;
		break;
	case EIGHT_CORE_FCFS:
		sched_type = "EIGHT_CORE_FCFS";
		s = new FirstComeFirstServe(8);
		num_of_cores = 8;
		break;
	case ROUND_ROBIN:
		sched_type = "ROUND_ROBIN";
		s = new RoundRobin();
		num_of_cores = 1;
		break;
	case SMALLEST_PROCESS_NEXT:
		sched_type = "SMALLEST_PROCESS_NEXT";
		s = new SmallestProcessNext();
		num_of_cores = 1;
		break;
	case MULTILEVEL_FEEBACK_QUEUE:
		sched_type = "MULTILEVEL_FEEBACK_QUEUE";
		s = new MultilevelFeedbackQueue();
		num_of_cores = 1;
		break;
	default:
		sched_type = "NO_SCHEDULER";
		break;
	}
	idle_time = 0;
	processor_time = 0;
	current_time = 0;
}

void OperatingSystem::generateStatistics() {
	//through put
	//avg wait time
	//response time
	//turnaround time
	//processor time
	ofstream outfile;
	outfile.open("stats.txt");

	if (outfile.fail()) {
		cout << "failed to open file" << endl;
		return;
	}

	double num_processes = (double)process_table.size();
	double through_put = num_processes / current_time;
	double processor_utilization = processor_time / (double)current_time;
	double total_wait = 0;
	double total_response = 0;
	double total_turnaround = 0;
	unordered_map<int, Process*>::iterator it = process_table.begin();
	for (it; it != process_table.end(); ++it) {
		total_wait += it->second->getCpuWait();
		total_response += it->second->getResponseTime();
		total_turnaround += it->second->getTurnaroundTime();
	}
	double avg_wait = total_wait / num_processes;
	double avg_response = total_response / num_processes;
	double avg_turnaround = total_turnaround / num_processes;

	const int col_width = 25;

	#ifdef LOG_VERBOSE
	it = process_table.begin();
	for (it; it != process_table.end(); ++it) {
		Process* pr = it->second;
		outfile << left << setw(col_width) << "PID: " << pr->getId() << endl;
		outfile << left << setw(col_width) << "Arrival time: " << pr->getArrivalTime() << " ms" << endl;
		outfile << left << setw(col_width) << "Exit time: " << pr->getExitTime() << " ms" << endl;
		outfile << left << setw(col_width) << "Time to completion: " << pr->getExitTime() - pr->getArrivalTime() << " ms" << endl;
		outfile << left << setw(col_width) << "Total CPU wait: " << pr->getCpuWait() << " ms" << endl;
		outfile << left << setw(col_width) << "Total IO wait: " << pr->getIoWait() << " ms" << endl;
		outfile << left << setw(col_width) << "Response time: " << pr->getResponseTime() << " ms" << endl << endl;
	}
	#endif

	outfile << "Sheduler type: " << sched_type << endl;
	outfile << "Total runtime: " << current_time << " ms" << endl;
	outfile << "Throughput: " << through_put << " processes/ms" << endl;
	outfile << "Average wait time: " << avg_wait << " ms" << endl;
	outfile << "Average response time: " << avg_response << " ms" << endl;
	outfile << "Average turnaround time: " << avg_turnaround << " ms" << endl;
	outfile << "CPU utilization: " << processor_utilization * 100 << "%" << endl;
	outfile << "CPU time: " << processor_time << " ms" << endl;
	outfile << "Idle time: " << idle_time << " ms" << endl;
}

void OperatingSystem::generateProcessFile(string file_name, int num_processes) {
	time_t seed = time(NULL);
	srand(seed);

	ofstream outfile;
	outfile.open(file_name);

	if (outfile.fail())	{
		cout << "failed to open file" << endl;
		return;
	}

	int pid_start = 1;
	int time_start = 0;
	// arrival time bounds
	int min_atime = 1;
	int max_atime = 5;
	// cpu time bounds
	int min_ctime = 3;
	int max_ctime = 30;
	// io time bounds
	int min_itime = 1;
	int max_itime = 5;
	// num of bursts bounds
	int min_bursts = 1;
	int max_bursts = 6;

	int pid = pid_start;
	int current_time = time_start;

	string format_string = "// file format: pid arrival_time cpu_burst [io_burst cpu_burst io_burst ...]";
	outfile << format_string << endl;
	for (int i = 0; i < num_processes; ++i)	{
		int arrival_time = current_time;
		outfile << pid << " " << arrival_time << " ";

		int num_bursts = generateRandomNumberInBounds(min_bursts, max_bursts);
		bool is_cpu = true;
		for (int j = 0; j < num_bursts; ++j) {
			int burst_time = (is_cpu ? generateRandomNumberInBounds(min_ctime, max_ctime) : generateRandomNumberInBounds(min_itime, max_itime));

			outfile << burst_time << " ";
			is_cpu = !is_cpu;
		}

		outfile << endl;

		int time_gap = generateRandomNumberInBounds(min_atime, max_atime);
		current_time += time_gap;
		++pid;
	}

	outfile.close();
	cout << "Successfully printed results to \"" << file_name << "\"" << endl;
}

void OperatingSystem::readProcessesFromFile(string file_name) {
	ifstream infile;
	infile.open(file_name);
	if (infile.fail()) {
		cout << "Failed to read from \"" << file_name << "\"" << endl;
		return;
	}
	//ignore comment
	string line;
	getline(infile, line);
	while (getline(infile, line)) {
		//Process p = Process();
		int id, arrival_time;
		istringstream is(line);
		is >> id >> arrival_time;
		vector<int> bursts = vector<int>(istream_iterator<int>(is), istream_iterator<int>());
		process_table.insert(make_pair(id, new Process(id, arrival_time, bursts)));
	}

	infile.close();
	cout << "Successfully read from \"" << file_name << "\"" << endl;
}

void OperatingSystem::runProcesses() {
	
	initializeArrivalQueue();
	current_time = 0;
	int current_pid = -1;
	bool all_processes_finished = false;
	vector<int> core_switch_time_remaining(num_of_cores, 0);
	while (!all_processes_finished) {
		cout << endl << "TIME: " << current_time << endl;
		checkForNewlyArrivedProcesses();
		for (int i = 0; i < num_of_cores; i++) {
			if (--core_switch_time_remaining[i] > 0) {
				cout << "Core is switching, " << core_switch_time_remaining[i] << " ms remaining" << endl;
				if (core_switch_time_remaining[i] != 0) {
					processor_time++;
					continue;
				}
			}

			//get process to execute next on CPU from scheduler
			Process* p = s->schedule();

			//we assume that the first process ran is arleady loaded into registers
			//i.e. no context switch required
			if (p && p->getId() != current_pid && current_pid != -1) {
				//process has switched
				//update wait time for newly arrived process
				p->updateCpuWaitTime(current_time);
				current_pid = p->getId();
				//set core to switching
				processor_time++;
				core_switch_time_remaining[i] = 3;
				cout << "SWITCHING PROCESS TO PID " << p->getId() << endl;
				cout << "Core is switching, " << core_switch_time_remaining[i] << " ms remaining" << endl;
				continue;
			}
			//progress I/O queue on first core schedule (per tick)
			if (i == 0) {
				updateIoQueue();
			}

			if (p == nullptr) {
				//no process to execute from ready queue
				if (io_queue.empty() && s->getNumInReadyQueue() == 0) {
					//no processes remain in ready or I/O queue.
					if (allProcessesHaveArrived())
					{
						//all processes handled from input file. end program.
						cout << "No processes remaining." << endl;
						all_processes_finished = true;
						//decrement current_time to keep stats accurate
						current_time--;
						break;
					}
					//let the program finish if time has exceeded limit
					if (current_time > 5000) {
						cout << "Program timing out..." << endl;
						all_processes_finished = true;
						//decrement current_time to keep stats accurate
						current_time--;
						break;
					}
					//wait for next process to arrive
					idle_time++;
					cout << "Waiting for " << arrival_queue.size() << " processes to arrive..." << endl;
					continue;
				}
				else {
					idle_time++;
					//wait for processes in I/O queue
					cout << io_queue.size() << " processes still in IO, " << s->getNumInReadyQueue() << " still in scheduler " << endl;
					continue;
				}
			}

			//increment processor time
			processor_time++;
			current_pid = p->getId();
			cout << "Running process with ID " << p->getId();
			cout << " that has " << p->getCurrentBurstLength() << " ms remaining " << endl;
			//progress CPU burst of current process
			int cpu_remaining = p->cpu(current_time);
			cout << "Process now has " << cpu_remaining << " ms remaining " << endl;
			//check if current burst has finished
			if (cpu_remaining <= 0) {
				//set process exit time
				p->updateExitTime(current_time);
				if (!p->isFinished()) {
					io_queue.push(p);
				}
			}			
		}
		++current_time;
	}
}


void OperatingSystem::updateIoQueue() {
	if (!io_queue.empty()) {
		Process* front = io_queue.front();
		//process io for one tick
		//cout << "updateIoQueue() - PID: " << front->getId() << endl;
		int io_remaining = front->io(current_time);
		if (io_remaining <= 0) {
			io_queue.pop();
			if (!front->isFinished()) {
				s->addProcess(front);
			}
		}
	}
}