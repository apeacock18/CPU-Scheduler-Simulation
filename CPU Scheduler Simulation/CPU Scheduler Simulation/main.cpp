#include "operating_system.h"

using namespace std;

int main() {
	OperatingSystem os = OperatingSystem(SchedulerType::MULTILEVEL_FEEBACK_QUEUE);
	os.generateProcessFile("process_list.txt", 3);
	os.readProcessesFromFile("process_list.txt");
	os.runProcesses();
	/*
	cout << endl << "///////////////////////////////////////////////////////////////////" << endl << "///////////////////////////////////////////////////////////////////" <<endl <<endl;
	os = OperatingSystem(SchedulerType::SMALLEST_PROCESS_NEXT);
	os.readProcessesFromFile("process_list.txt");
	os.runProcesses();
	*/


	return 0;
}