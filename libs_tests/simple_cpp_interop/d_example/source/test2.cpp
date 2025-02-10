#include <vector>
#include <iostream>
#include <string>
#include <string_view>
#include "test.hpp"

extern "C" {
    void fix_array_capi(test::Status* x, std::string_view input, char*** words, size_t* num_words) {
        std::vector<std::string> tmp;
        x->fix_array(input, &tmp);
        *num_words = tmp.size();
        *words = (char**)malloc(sizeof(char*) * (*num_words));
        for (size_t i = 0; i < *num_words; ++i) {
            (*words)[i] = strdup(tmp[i].c_str());
        }
    }
}