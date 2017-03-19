#include "operating_system.h"

int OperatingSystem::generateRandomNumberInBounds(int min, int max) {
	return rand() % (max - min) + min;
}

OperatingSystem::OperatingSystem(SchedulerType type) {
	initScheduler(type);
	processor_time = 0;
	current_time = 0;
}

void OperatingSystem::generateStatistics() {
	//through put
	//avg wait time
	//response time
	//turnaround time
	//processor time
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

	//dummy process until we can read in from file
	/*vector<int> bursts1 = { 3, 9, 5 };
	Process* p1 = new Process(1, 0, bursts1);
	process_table.insert(make_pair(p1->getId(), p1));

	vector<int> bursts2 = { 1, 3, 7 };
	Process* p2 = new Process(2, 2, bursts2);
	process_table.insert(make_pair(p2->getId(), p2));*/
}

void OperatingSystem::runProcesses() {
	unordered_map<int, Process*>::iterator it = process_table.begin();
	for (it; it != process_table.end(); ++it) {
		//TODO: add processes based on arrival time
		s->addProcess(it->second);
	}

	int current_time = 0;
	while (true) {
		cout << "Time is " << current_time << endl;

		//get process to execute next on CPU from scheduler
		Process* p = s->schedule();
		//cout << p->getBurstIndex() << endl;
		//progress I/O queue
		//if (p != nullptr) cout << "Current PID: " << p->getId() << endl;
		updateIoQueue();

		if (p == nullptr) { //TODO: and no more processes will arrive
			//no process to execute from ready queue
			if (io_queue.empty() && s->getNumInReadyQueue() == 0) {
				//no processes remain in ready or I/O queue. Abort.
				cout << "No processes remaining." << endl;
				break;
			}
			else {
				//wait for processes in I/O queue
				cout << io_queue.size() << " processes still in IO" << endl;
				++current_time;
				continue;
			}
		}
		cout << "Running process with ID " << p->getId();
		cout << " that has " << p->getCurrentBurstLength() << " ms remaining " << endl;
		//progress CPU burst of current process
		int cpu_remaining = p->cpu(current_time);
		cout << "Process now has " << cpu_remaining << " ms remaining " << endl;
		if (cpu_remaining <= 0 && !p->isFinished()) {
			io_queue.push(p);
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

void OperatingSystem::initScheduler(SchedulerType type) {
	switch (type)
	{
	case FIRST_COME_FIRST_SERVE:
		s = new FirstComeFirstServe();
		break;
	case ROUND_ROBIN:
		s = new RoundRobin();
		break;
	case SMALLEST_PROCESS_NEXT:
		s = new SmallestProcessNext();
		break;
	case MULTILEVEL_FEEBACK_QUEUE:
		s = new MultilevelFeedbackQueue();
		break;
	default:
		break;
	}
}