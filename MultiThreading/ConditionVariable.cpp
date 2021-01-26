#include <deque>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <iostream>
#include <vector>
#include <condition_variable>

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

void function1() {
	int count = 10;
	while (count > 0) {
		std::unique_lock<std::mutex> locker(mu);
		q.push_front(count); // Shared-resources
		std::cout << "Push " << count << std::endl;
		locker.unlock();
		cond.notify_one(); // Notify one waiting thread, if there is one.
		// cond.notify_all();
		std::cout << "notify_one" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1)); // Imply other process
		count --;
	}
}

void function2() {
	int data = 0;
	while (data != 1) {
		std::unique_lock<std::mutex> locker(mu);
		/*
		if (!q.empty()) {
			data = q.back();
			q.pop_back();
			locker.unlock();
			std::cout << "t2 got a value from t1: " << data << std::endl;
		}
		else {
			locker.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		*/
		// cond.wait(locker, [](){return !q.empty();});
		cond.wait(locker);
		std::cout << "Receive notification" << std::endl;
		data = q.back();
		q.pop_back();
		locker.unlock();
		std::cout << std::this_thread::get_id() << " got a value from t1: " << data << std::endl;
	}
}

int main() {
	// Consumer
	int numOfWorker = 1;
	std::vector<std::thread> worker;
	for (int i = 0; i < numOfWorker; i++) {
		std::thread tmp(function2);
		worker.push_back(std::move(tmp));
	}
	// Producer
	std::thread t1(function1);


	t1.join();
	std::cout << "poducer join" << std::endl;
	for (auto& t : worker)
		t.join();
	std::cout << "worker Join" << std::endl;

	return 0;
}