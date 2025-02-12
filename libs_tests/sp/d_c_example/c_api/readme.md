# Build test example
First build object file and then the main test example:
```bash
clang++ sentencepiece.cpp -c
clang++ test.cpp sentencepiece.o --std=c++11 -lsentencepiece -rpath /usr/local/lib
```

Build object file for D:
```bash
clang++ sentencepiece.cpp --std=c++11 -I../../sentencepiece/src/ -L../../sentencepiece/build/src -lsentencepiece -c -o sp_c_api.o
```