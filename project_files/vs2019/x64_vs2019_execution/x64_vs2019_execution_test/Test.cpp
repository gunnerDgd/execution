#include <iostream>
#include <thread>
#include <mutex>

#include <string>
#include <chrono>

#include <Windows.h>

#include <execution/executor.hpp>
#include <execution/branch.hpp>

#include <boost/asio.hpp>

std::chrono::steady_clock::time_point time_point;

void test_branch_acquire(execution::branch::handle_type& hnd)
{
	for (int i = 0; i < 5; i++)
	{
		time_point = std::chrono::high_resolution_clock::now();
		hnd.yield();
	}
}

void test_branch_release(execution::branch::handle_type& hnd)
{
	for (int i = 0; i < 5; i++)
	{
		std::cout << (std::chrono::high_resolution_clock::now() - time_point).count() << std::endl;
		hnd.yield();
	}
}

void test_thread_acquire(std::mutex& hnd)
{
	for (int i = 0; i < 5; i++)
	{
		hnd.lock();
		std::cout << (std::chrono::high_resolution_clock::now() - time_point).count() << std::endl;
		hnd.unlock();
	}
}

void test_thread_release(std::mutex& hnd)
{
	for (int i = 0; i < 5; i++)
	{
		hnd.lock();
		time_point = std::chrono::high_resolution_clock::now();

		hnd.unlock();
	}
}

int main()
{
	using namespace std::string_literals;
	
	execution::executor     Executor;
	boost::asio::io_context BoostExecutor;

	BoostExecutor.dispatch()

		std::mutex  th_lock;
	std::thread th_1(test_thread_release, std::ref(th_lock)), th_2(test_thread_acquire, std::ref(th_lock));

	th_1.join();
	th_2.join();

	auto r1 = Executor.dispatch(test_branch_acquire);
	auto r2 = Executor.dispatch(test_branch_release);

	while (Executor.execute());
		
}