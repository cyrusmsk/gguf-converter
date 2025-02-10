# CMakeLists.txt
cmake_minimum_required(VERSION 3.12)
project(example)

# Specify the location of pybind11 (if not installed system-wide)
# You can install pybind11 using: pip install pybind11
find_package(pybind11 REQUIRED)

# Add the source code
pybind11_add_module(example example.cpp)