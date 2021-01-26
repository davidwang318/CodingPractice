#include <future>
#include <iostream>
#include <thread>

/*
// It's very messy to get a return value from a thread using reference.
// mutex to protect shared memory: x
// cond to make sure the x will be changed by te function, then send to main()


std::mutex mu;
std::condition_variable cond;


void factorial(int N, int& x) {
	int res = 1;
	for (int i = N; i > 1; i--) {
		res *= i;
	}

	std::cout << "Result is: " << res << endl;
	x = res;
	return
}

int main() {
	int x;
	std::thread t1(factorial, 4, std::ref(x));
	// What if we want a return value?

	t1.join();
	return 0;

}
*/

int factorial(int N, std::future<int>& f) {
	int res = 1;
	for (int i = N; i > 1; i--) {
		res *= i;
	}
	std::cout << "Result is: " << res << std::endl;
	std::cout << "Receive promise: " << f.get() << std::endl;
	return res;
}

int main() {
	int x = 0;

	std::promise<int> p;
	std::future<int> f = p.get_future();

	std::future<int> fu = std::async(factorial, 4, std::ref(f));
	// std::shared_future<int> sf = fu.share(); // a future that can be copied
	// std::future<int> fu = std::async(std::launch::deferred, factorial, 4) // defer the execution until the get function be called
	
	// Do something
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	p.set_value(4);


	x = fu.get();
	std::cout << "Get from child: " << x << std::endl;
	// fu.get(); // crash

	return 0;
}
