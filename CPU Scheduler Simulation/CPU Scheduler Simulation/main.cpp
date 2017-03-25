#include "operating_system.h"

using namespace std;

int main() {
	int num_of_schedulers = 9;
	//dummy OS to generate the file
	OperatingSystem fileGenerator(SchedulerType::FIRST_COME_FIRST_SERVE);
	fileGenerator.generateProcessFile("process_list.txt", 12);

	try {
		for (int i = 0; i < num_of_schedulers; ++i) {
			//run processes and generate stats for each sheduler
			OperatingSystem os = OperatingSystem((SchedulerType)i);
			os.readProcessesFromFile("process_list.txt");
			os.runProcesses();
			//if it's the first time, overwrite the stats file; otherwise append
			bool overwrite_file = (i == 0);
			os.generateStatistics(overwrite_file);
		}
	}
	catch (exception& e) {
		cout << "Something went wrong!" << endl;
		cout << "Error was " << e.what() << endl;
	}

	return 0;
}