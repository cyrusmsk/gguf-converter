# Load the Rcpp library
library(Rcpp)

# Source the C++ code
sourceCpp("helper.cpp")

# Example input
input <- c("Hello", "World", "Rcpp")

# Call the function
output <- concat_strings(input)

# Print the output
print(output)
