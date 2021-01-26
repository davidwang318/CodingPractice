#include <iostream>
#include <thread>
#include <string>

void function1() {
	std::cout << "Beauty is only skin-deep" << std::endl;
}

/**
// Catch exception make sure t1 will join with/without exception
int main() {
	std::thread t1(function1);

	try {
		for (int i = 0; i < 100; i++)
			std::cout << "From main: " << i << std::endl;
	} catch (...) {
		t1.join();
		throw;
	}
	t1.join(); // Need this line in case there's no exception
	return 0;
}
**/

/**
// Resource Acquisition is Initialization (RAII)
class ThreadRAII {
public:
	ThreadRAII(std::thread& th){
		std::cout << "RAII constructor" << std::endl;
		t = std::move(th);
	}
	~ThreadRAII() {
		std::cout << "RAII destructor" << std::endl;
		if (t.joinable()) {
			std::cout << "Join if joinable" << std::endl;
			t.join();
		}
	}
	// Delete the copu constructor and the assignment operator
	ThreadRAII(const ThreadRAII&)= delete;
	ThreadRAII& operator = (const ThreadRAII&)= delete;
	// Getter
	std::thread& getThread() {return t;}
private:
	std::thread t;
};

int main() {
	std::thread t1(function1);
	ThreadRAII r1_raii(t1);
	return 0;
}
**/

class Fctor {
public:
	void operator() (std::string& msg) {
		std::cout << "t1 says: " << msg << std::endl;
		msg = "Trust is the mother of deceit.";
	}
};
int main() {
	std::string s = "Where there is no trust, there is no love.";
	std::thread t1((Fctor()), std::ref(s)); // If use std::move(), we pass by value;
	t1.join();
	std::cout << "main says: " << s << std::endl;

	// Oversubscription
	std::cout << std::thread::hardware_concurrency() << std::endl;

	return 0;
}
