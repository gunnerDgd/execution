#include <execution/forward.hpp>
#include <iostream>

void test(execution::branch::branch_handle& handle)
{
	std::cout << "Hello Test #1\n";
	handle.yield();
	std::cout << "Hello Test #2\n";
	handle.yield();
}

int main()
{
	execution::branch MainBranch, TestBranch(MainBranch, test);
	std::cout << "Hello Main #1\n";
	MainBranch();
	std::cout << "Hello Main #2\n";
	MainBranch();
}