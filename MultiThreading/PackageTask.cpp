/*
main adventage of package list:
1. link a callable object to a future

Summary:
3 ways to get a future:
- promise::get_future()
- packaged_task::get_future()
- async(): returns a future
*/

#include <future>
#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>
#include <functional>

int factorial(int N) {
	int res = 1;
	for (int i = N; i > 1; i--) {
		res *= i;
	}
	std::cout << "Result is: " << res << std::endl;
	// std::cout << "Receive promise: " << f.get() << std::endl;
	return res;
}

std::deque<std::packaged_task<int()>> task_q;
std::mutex mu; // for the deque
std::condition_variable cond;

void thread_1() {
	std::packaged_task<int()> t;
	{
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker, [](){return !task_q.empty();});
		t = std::move(task_q.front()); // thread 1 gets the job
		task_q.pop_front();
	}
	t(); // what about its return value?
}

int main() {
	/*
	// std::thread t1(factorial, 6); // the same as the package task
	std::packaged_task<int(int)> t (factorial);
	// std::packaged_task<int()> t (std::bind(factorial, 6)); 
	t(6); // always return void
	// t(); // for the bind version
	int x = t.get_future().get(); // Need this to get a value from package task
	*/

	std::thread t1(thread_1);
	std::packaged_task<int()> t(std::bind(factorial, 6));
	std::future<int> fu = t.get_future(); // when t() gets called, the future will get
	{
		std::lock_guard<std::mutex> locker(mu);
		task_q.push_back(std::move(t)); // Main thread creates a job
		cond.notify_one();
	}

	std::cout << fu.get() << std::endl;
	t1.join();

	return 0;
}