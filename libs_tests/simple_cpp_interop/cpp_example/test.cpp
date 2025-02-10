#include <vector>
#include <iostream>
#include <string>
#include <string_view>
#include "test.hpp"

namespace test {
    int Status::error_message() {
        return 1;
    }

    void Status::print_string(std::string_view input) {
        std::cout << input << std::endl;
    }

    void Status::fix_array(std::string_view input, std::vector<std::string>* words) {
        // Clear the vector to ensure it's empty before adding new results
        words->clear();

        // Process the input string using string_view
        //std::stringstream ss(std::string(input));  // Convert string_view to string
        //std::string word;
    
        //// Add underscore to each word and store in the vector
        //while (ss >> word) {
        //    words->push_back("_" + word);  // Add word with leading underscore to the vector
        //}

        size_t start = 0;
        for (size_t i = 0; i <= input.size(); ++i) {
            // When we find a space or reach the end of the string
            if (i == input.size() || input[i] == ' ') {
                if (i > start) {
                    // Extract the word and add underscore
                    words->push_back("_" + std::string(input.substr(start, i - start)));
                }
                start = i + 1; // Move past the space
            }
        }
    }
}