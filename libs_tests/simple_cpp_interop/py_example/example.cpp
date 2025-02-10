#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <string>

namespace py = pybind11;

std::vector<std::string> process_strings(const std::vector<std::string>& input) {
    std::vector<std::string> result;
    for (const auto& str : input) {
        result.push_back(str + "_processed");  // Adding "_processed" to each string
    }
    return result;
}

PYBIND11_MODULE(example, m) {
    m.def("process_strings", &process_strings, "Process a list of strings");
}