#include "scheduler.h"
using namespace std;


Scheduler::Scheduler() {
	current_process = nullptr;
}

void Scheduler::incrementCoreIndex() {
	current_core_index = (current_core_index + 1) % num_of_cores;
}

