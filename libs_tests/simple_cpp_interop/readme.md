# Build code commands

## For D example
Simplest example:
```bash
clang++ test.cpp -c
ldc2 sp.d test.o -L-lstdc++
```

With dub just use:
```bash
cd source
clang++ --std=c++20 test2.cpp -c
mv test2.o ../
dub build
```

## For C++ example
```bash
clang++ --std=c++20 x.cpp test.cpp
```

## For R example
Install `Rcpp` and run:
```bash
Rscript r_example.R
```

## For Python example
Install `Pybind11` first.
First build C++ code:
```bash
mkdir build
cd build
cmake ..
make
```

Then just run Python:
```python
python py_example.py
```
