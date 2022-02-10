#include <execution/branch.hpp>
#include <execution/executor.hpp>

#include <Windows.h>
#include <iostream>
#include <thread>

void test(execution::branch::branch_handle& hnd, std::string& msg)
{
	while(true)
	{
		Sleep(1000);
		hnd.yield();
	}
}

void test2(execution::branch::branch_handle& hnd, std::string& msg)
{
	while (true)
	{
		Sleep(1000);
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

	Executor.trigger_if<execution::trigger::executed>([](execution::executor::running) { std::cout << "Um is "; });
	Executor.trigger_if<execution::trigger::yielded> ([](execution::executor::running) { std::cout << "Still Alive\n"; });

	std::thread ExecuteThread([&Executor]()
		{
			while (true)
				Executor.execute();
		});
	ExecuteThread.join();
}