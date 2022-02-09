#include <execution/forward.hpp>
#include <iostream>
#include <string>

void test(execution::branch::branch_handle& handle, std::string& str)
{
	std::cout << "Hello Test #1\n";
	str = "Hello Execution\n";
	handle.yield();
	std::cout << "Hello Test #2\n";
	handle.yield();
}

int main()
{
	std::string		  TestString;
	execution::branch TestBranch(test, TestString);
	
	std::cout << "Hello Main #1\n";
	TestBranch();
	std::cout << TestString << std::endl;
	std::cout << "Hello Main #2\n";
	TestBranch();
}