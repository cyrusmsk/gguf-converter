#include "test.hpp"
#include <iostream>

int main() {
    auto x = test::Status();
    std::cout << (int)x.error_message() << std::endl;
    return 0;
}