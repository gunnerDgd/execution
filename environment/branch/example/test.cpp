#include <executor/executor_forward.hpp>

void test() { std::cout << "Hello World\n"; }

int main()
{
    executor::branch test_branch(test);
}