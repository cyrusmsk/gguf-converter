# C++ example
Sentencepiece library

## Build script
If the library installed with homebrew:
```bash
clang++ --std=c++11 cpp_example.cpp -I/opt/homebrew/include/ -L/opt/homebrew/opt/sentencepiece/lib/ -lsentencepiece
```

If the library build from sources to `/usr/local`:
```bash
clang++ --std=c++11 cpp_example.cpp -I/usr/local/include -rpath /usr/local/lib/ -lsentencepiece
```