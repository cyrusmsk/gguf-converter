#include <sentencepiece_processor.h>
#include <iostream>

int main() {
    sentencepiece::util::Status status;
    if (!status.ok()) {
       std::cerr << status.ToString() << std::endl;
       // error
    }
    std::cout << "Status example" << std::endl;
    return 0;
}