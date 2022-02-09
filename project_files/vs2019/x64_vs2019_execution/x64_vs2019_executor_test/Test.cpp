#include <execution/executor_traits/forward.hpp>

void test(execution::branch::branch_handle& handle)
{
	std::cout << "Hello World\n";
}

int main()
{
	execution::executor Executor;
	Executor.execute(test);
}