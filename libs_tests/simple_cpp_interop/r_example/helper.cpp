#include <Rcpp.h>
#include <vector>
#include <string>

// [[Rcpp::export]]
std::vector<std::string> concat_strings(std::vector<std::string> input) {
  std::vector<std::string> result;
  
  // Loop through the input vector and concatenate each string
  for (size_t i = 0; i < input.size(); ++i) {
    result.push_back(input[i] + " concatenated");
  }
  
  return result;
}
