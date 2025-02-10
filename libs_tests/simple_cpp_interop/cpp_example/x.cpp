#include "test.hpp"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int main() {
    auto x = test::Status();
    
    // Example input string_view and vector of strings
    std::string_view input = "hello world this is C++";
    std::vector<std::string> words;

    // Call the function with a pointer to the vector
    x.fix_array(input, &words);

    // Print the result stored in the vector
    std::cout << "Modified words: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    return 0;
}