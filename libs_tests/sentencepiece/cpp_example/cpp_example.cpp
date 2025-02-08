#include <sentencepiece_processor.h>
#include <iostream>

int main() {
    sentencepiece::SentencePieceProcessor processor;
    const auto status = processor.Load("../data/sentencepiece.bpe.model");
    if (!status.ok()) {
       std::cerr << status.ToString() << std::endl;
       // error
    }
    std::cout << "Model loaded succesffully" << std::endl;
    return 0;
}
