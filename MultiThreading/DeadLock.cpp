/* Avoiding Deadlock
1. Prefer locking single mutex.
2. Avoid locking a mutex and then calling a user provided function.
3. Use std::lock() to lock more than one mutex.
4. Lock the mutex in the same order.

Locking Granularity:
- Fine-grained lock: protects small amount of data.
- Coarse-grained lock: protects big amount of data.

If have multiple mutex:
1. std::lock(mu1, mu2 ...)
2. Use code block to lock single mutex:
{
	std::lock_guard<mutex> lock(mu1);
}
{
	std::lock_guard<mutex> lock(mu2);
}


*/

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <unistd.h>

// Deadlock demostration
class LogFile {
public:
	LogFile() {
		f.open("log.txt");
	}
	void shared_print(std::string id, int value) {
		std::lock_guard<std::mutex> locker(m_mutex);
		std::lock_guard<std::mutex> locker2(m_mutex2);
		// f << "From " << id << ": " << value << std::endl;
		std::cout << "From " << id << ": " << value << std::endl;
	}
	void shared_print2(std::string id, int value) {
		std::lock_guard<std::mutex> locker2(m_mutex2);// <------------------ Causing deadlock
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
	std::mutex m_mutex2;
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
		log.shared_print2(std::string("From main: "), i);
		usleep(1000);
	}

	t1.join();

	return 0;
}
