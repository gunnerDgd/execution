#include <execution/executor_traits/forward.hpp>
#include <thread>

void test(execution::branch::branch_handle& handle)
{
	while (true)
	{
		std::cout << "Hello Test\n";
		Sleep(1000);
		handle.yield();
	}
}

void test2(execution::branch::branch_handle& handle)
{
	while (true)
	{
		std::cout << "Hello Test2\n";
		Sleep(1000);
		handle.yield();
	}
}

int main()
{
	execution::executor Executor	   ;
	auto tst1 = Executor.execute(test) ;
	auto tst2 = Executor.execute(test2);
	int i = 1;

	std::thread ExecuteThread([&Executor]() { while (true) Executor.run_next(); });
	Sleep(3000);
	Executor.suspend(tst2);
	ExecuteThread.join();
}