#include <iostream>
#include <thread>

void function1() {
	std::cout << "Beauty is only skin-deep" << std::endl;
}

int main() {
	std::thread t1(function1); //t1 starts running
	t1.join(); // main threads waits for t1 to finish
	// t1.detach(); // t1 will freely on its own
	/**
	if (t1.joinable()) {
		t1.join();
	}
	**/
	
	return 0;
}