#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>


class LogFile {
public:
	LogFile() {}
	void shared_print(std::string id, int value) {

		// Lazy initialization
		// Once flag
		// std::call_once(flag_, [&](){f_.open("log.txt");}); // file will be opened only once by one thread!
		{
			std::unique_lock<mutex> locker2(mu_init_);
			if(!_f.is_open())
				_f.open("log.txt");
		}

		// Finer-grained lock
		std::unique_lock<mutex> locker(mu_);
		std::cout << "From " << id << ": " << value << std::endl;
		locker.unlock();
		/*
		std::unique_lock<mutex> locker(mu_, defer_lock);
		// Do something
		locker.lock();
		std::cout << "From " << id << ": " << value << std::endl; <- Process using shared resources
		locker.unlock();
		....
		*/
		std::unique_lock<mutex> locker2 = std::move(locker);
	}
private:
	std::mutex mu_;
	std::mutex mu_init_;
	std::once_flag flag_;
	std::ofstream f_;
};