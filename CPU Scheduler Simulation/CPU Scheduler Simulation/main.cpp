#include "operating_system.h"

using namespace std;

int main() {
	OperatingSystem os = OperatingSystem();
	os.readProcessesFromFile("process_list.txt");

	return 0;
}