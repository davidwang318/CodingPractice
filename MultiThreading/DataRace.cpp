#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <unistd.h>

/*
Avoiding Data Race:
1. Use mutex to synchronize data access;
2. Never leak a handle of data to outside (so it'll always synchronize);
3. Design interface appropriately (stack should have topPop() function); 
*/

class LogFile {
public:
	LogFile() {
		f.open("log.txt");
	}
	void shared_print(std::string id, int value) {
		std::lock_guard<std::mutex> locker(m_mutex);
		// f << "From " << id << ": " << value << std::endl;
		std::cout << "From " << id << ": " << value << std::endl;
	}
	// Never return f to the outside world => pass mutex to access f
	std::ofstream& getStream() {return f;}
	// Never pass f as an argument to user provided function 
	void processf(void fun(std::ofstream&)) {fun(f);}
private:
	std::mutex m_mutex;
	std::ofstream f;
};

void function1(LogFile& log) {
	for (int i = 0; i > -1000; i--) {
		log.shared_print(std::string("From thread: "), i);
		usleep(1000);
	}
}

int main() {
	LogFile log;
	std::thread t1(function1, std::ref(log));

	for (int i = 0; i < 1000; i++) {
		log.shared_print(std::string("From main: "), i);
		usleep(1000);
	}

	t1.join();

	return 0;
}