#include "operating_system.h"

using namespace std;

int main() {
	OperatingSystem os = OperatingSystem(SchedulerType::FIRST_COME_FIRST_SERVE);
	//os.generateProcessFile("process_list.txt", 12);
	os.readProcessesFromFile("test_case.txt");
	os.runProcesses();
	os.generateStatistics();

	//cout << endl << "///////////////////////////////////////////////////////////////////" << endl << "///////////////////////////////////////////////////////////////////" <<endl <<endl;
	//os = OperatingSystem(SchedulerType::SMALLEST_PROCESS_NEXT);
	//os.readProcessesFromFile("process_list.txt");
	//os.runProcesses();


	return 0;
}