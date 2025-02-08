# Build code commands

## For D example
clang++ test.cpp -c
ldc2 sp.d test.o -L-lstdc++

## For C++ example
clang++ --std=c++20 x.cpp test.cpp