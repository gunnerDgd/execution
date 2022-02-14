#include <iostream>
#include <thread>
#include <mutex>

#include <string>
#include <chrono>

#include <Windows.h>

#include <execution/executor.hpp>
#include <execution/branch.hpp>

std::chrono::steady_clock::time_point Time;

void test(execution::branch::handle_type& hnd, std::string str)
{
	while (true)
	{
		std::cout << (std::uint64_t)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - Time).count() << std::endl;
		//std::cout << str;

		hnd.yield();
	}
}


int main()
{
	using namespace std::string_literals;
	execution::executor Executor;

	std::mutex lock;
	std::thread t1([&lock]()
		{
			while (true)
			{
				lock.lock();
				Time = std::chrono::high_resolution_clock::now();
				lock.unlock();
			}
		}), t2([&lock]()
			{
				while (true)
				{
					lock.lock();
					std::cout << (std::chrono::high_resolution_clock::now() - Time).count() << std::endl;
					lock.unlock();
				}
			});

		t1.join();
		t2.join();

	auto r1 = Executor.dispatch  (test, "Hello Test1\n"s);
	auto r2 = Executor.dispatch  (test, "Hello Test2\n"s);
	auto r3 = Executor.dispatch  (execution::execution_types::avoid, r2, test, "Hello Test3\n");
	
	while (true)
	{
		Time = std::chrono::high_resolution_clock::now();
		Executor.execute();
	}
}