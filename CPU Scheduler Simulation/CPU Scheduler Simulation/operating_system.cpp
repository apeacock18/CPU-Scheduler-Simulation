#include "operating_system.h"

int OperatingSystem::generateRandomNumberInBounds(int min, int max) {
	return rand() % (max - min) + min;
}

OperatingSystem::OperatingSystem(SchedulerType type) {
	switch (type)
	{
	case FIRST_COME_FIRST_SERVE:
		sched_type = "FIRST_COME_FIRST_SERVE";
		s = new FirstComeFirstServe(1);
		break;
	case ROUND_ROBIN:
		sched_type = "ROUND_ROBIN";
		s = new RoundRobin();
		break;
	case SMALLEST_PROCESS_NEXT:
		sched_type = "SMALLEST_PROCESS_NEXT";
		s = new SmallestProcessNext();
		break;
	case MULTILEVEL_FEEBACK_QUEUE:
		sched_type = "MULTILEVEL_FEEBACK_QUEUE";
		s = new MultilevelFeedbackQueue();
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

bool  pCompare(Process* lhs, Process* rhs) {
	return lhs->getArrivalTime() < rhs->getArrivalTime();
}

void OperatingSystem::runProcesses() {
	//load initial processes to scheduler
	unordered_map<int, Process*>::iterator it = process_table.begin();
	vector<Process*> processList;
	for (it; it != process_table.end(); ++it) {
		processList.push_back(it->second);
	}
	//sort processes based off of arrival time
	sort(processList.begin(), processList.end(), pCompare);
	for (int i = 0; i < processList.size(); i++) {
		cout << "PID: " << processList[i]->getId() << endl;
		s->addProcess(processList[i]);
	}
	current_time = 0;
	int current_pid = -1;
	while (true) {
		cout << "Time is " << current_time << endl;

		//get process to execute next on CPU from scheduler
		Process* p = s->schedule();
		if (p && p->getId() != current_pid) {
			//process has switched
			//update wait time for newly arrived process
			p->updateCpuWaitTime(current_time);
			current_pid = p->getId();
		}
		//progress I/O queue
		updateIoQueue();

		if (p == nullptr) { //TODO: and no more processes will arrive
			//no process to execute from ready queue
			if (io_queue.empty() && s->getNumInReadyQueue() == 0) {
				//no processes remain in ready or I/O queue. Abort.
				cout << "No processes remaining." << endl;
				break;
			}
			else {
				idle_time++;
				//wait for processes in I/O queue
				cout << io_queue.size() << " processes still in IO" << endl;
				++current_time;
				continue;
			}
		}
		//increment processor time
		processor_time++;
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