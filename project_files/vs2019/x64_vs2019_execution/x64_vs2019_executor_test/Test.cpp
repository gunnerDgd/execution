#include <boost/asio.hpp>

#include <iostream>
#include <thread>
#include <mutex>

#include <string>
#include <chrono>

#include <execution/executor.hpp>
#include <execution/branch.hpp>

#include <Windows.h>

std::chrono::steady_clock::time_point heavy_time_point;
std::chrono::steady_clock::time_point light_time_point;

void test_branch_heavy_task(execution::branch::handle_type& hnd)
{
	heavy_time_point = std::chrono::high_resolution_clock::now();

	for (int k = 0; k < 10; k++)
	{
		Sleep (100);
		hnd.yield();
	}
	
	std::cout << "Branch #1 Executed.\n";
	std::cout << "HEAVY TASK (BRANCH) :: " << (std::chrono::high_resolution_clock::now() - light_time_point).count() << " Ellapsed.\n";
}

void test_branch_light_task(execution::branch::handle_type& hnd)
{
	light_time_point = std::chrono::high_resolution_clock::now();
	
	Sleep(100);
	std::cout << "Branch #2 Executed.\n";
	std::cout << "LIGHT TASK (BRANCH) :: " << (std::chrono::high_resolution_clock::now() - light_time_point).count() << " Ellapsed.\n";
}

void test_asio_heavy_task()
{
	heavy_time_point = std::chrono::high_resolution_clock::now();

	Sleep(1000);
	std::cout << "ASIO #1 Executed.\n";
	std::cout << "HEAVY TASK (ASIO) :: " << (std::chrono::high_resolution_clock::now() - light_time_point).count() << " Ellapsed.\n";
}

void test_asio_light_task()
{
	light_time_point = std::chrono::high_resolution_clock::now();

	Sleep(100);
	std::cout << "ASIO #2 Executed.\n";
	std::cout << "LIGHT TASK (ASIO) :: " << (std::chrono::high_resolution_clock::now() - light_time_point).count() << " Ellapsed.\n";
}

int main()
{
	using namespace std::string_literals;
	
	execution::executor     Executor;
	boost::asio::io_context BoostExecutor;
	
	BoostExecutor.dispatch(test_asio_heavy_task);
	for(int i = 0 ; i < 10 ; i++)
		BoostExecutor.dispatch(test_asio_light_task);
	
	auto r1 = Executor.dispatch(test_branch_heavy_task);
	auto r2 = Executor.dispatch(test_branch_light_task);
	
	while (Executor.execute());
	while (true)			  BoostExecutor.run();
}