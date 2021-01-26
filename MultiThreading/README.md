# thread  
1. std::thread t1(factorial, 6);  
2. std::this_thread::sleep_for(chrono::milliseconds(3));  
3. chrono::steady_clock::time_point tp = chrono::steady_clock::now() + chrono::microseconds(4);
4. std::this_thread::sleep_until(tp);  
  
# mutex  
1. std::mutex mu;  
2. std::lock_guard<std::mutex> locker(mu);  
3. std::unique_lock<std::mutex> ulocker(mu);
4. ulocker.try_lock();  
5. ulocker.try_lock_for(chrono::nanoseconds(500));  
6. ulocker.try_lock_until(tp);    
  
# Condition Variable  
1. std::condition_variable cond;
2. cond.wait_for(ulocker, chrono::microsecond(2));  
3. cond.wait_until(ulocker, tp);    
  
# Future and Promise  
1. std::promise<int> p;  
2. std::future<int> f = p.get_future();  
3. f.get();  
4. f.wait();  
5. f.wait_for(chrono::...);
6. f.wait_until(tp);  

# Async()  
1. std::future<int> fu = async(factorial, 6);  

# Packaged Task  
1. std::packaged_task<int(int)> t(factorial);  
2. std::future<int> fu2 = t.get_future();  
3. t(6);