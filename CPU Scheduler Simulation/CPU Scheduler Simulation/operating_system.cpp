#include "operating_system.h"

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

void OperatingSystem::readProcessesFromFile(string file_name) {
	ifstream file;
	file.open("process_list.txt");
	//ignore comment
	string str;
	getline(file, str);
	while (getline(file, str)) {
		//Process p = Process();
		int id, arrival_time;
		vector<int> bursts;
	}
}

void OperatingSystem::runProcesses() {

}

void OperatingSystem::initScheduler(SchedulerType type) {
	switch (type)
	{
	case FIRST_COME_FIRST_SERVE:
		break;
	case ROUND_ROBIN:
		break;
	case SMALLEST_PROCESS_NEXT:
		break;
	case MULTILEVEL_FEEBACK_QUEUE:
		break;
	default:
		break;
	}
}