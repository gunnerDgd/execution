#include <execution/forward.hpp>
#include <execution/executor_traits/forward.hpp>

#include <Windows.h>
#include <iostream>
#include <thread>

void test(execution::branch::branch_handle& hnd, std::string& msg)
{
	while(true)
	{
		Sleep(1000);
		std::cout << msg;
		hnd.yield();
	}
}

void test2(execution::branch::branch_handle& hnd, std::string& msg)
{
	while (true)
	{
		Sleep(1000);
		std::cout << msg;
		hnd.yield();
	}
}

int main()
{
	execution::executor Executor;

	std::string msg_test  = "Hello Test\n";
	std::string msg_test2 = "Hello Test2\n";

	auto rq_test      = Executor.dispatch([](execution::branch::branch_handle& h, std::string msg){ test(h, msg); } , msg_test);
	auto rq_test2     = Executor.dispatch(test2, msg_test2);

	std::thread ExecuteThread([&Executor]()
		{
			while (true)
				Executor.execute();
		});

	Sleep(5000);
	auto sq_test2 = Executor.suspend(rq_test2);
	
	Sleep(5000);
	Executor	 .resume(sq_test2);
	ExecuteThread.join();
}