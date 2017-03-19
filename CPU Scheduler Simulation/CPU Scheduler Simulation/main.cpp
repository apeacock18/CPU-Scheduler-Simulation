#include "operating_system.h"

using namespace std;

int main() {
	OperatingSystem os = OperatingSystem(SchedulerType::ROUND_ROBIN);
	os.generateProcessFile("process_list.txt", 12);
	os.readProcessesFromFile("process_list.txt");
	os.runProcesses();

	//cout << endl << "///////////////////////////////////////////////////////////////////" << endl << "///////////////////////////////////////////////////////////////////" <<endl <<endl;
	//os = OperatingSystem(SchedulerType::SMALLEST_PROCESS_NEXT);
	//os.readProcessesFromFile("process_list.txt");
	//os.runProcesses();


	return 0;
}