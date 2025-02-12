#include <sentencepiece_processor.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
    sentencepiece::SentencePieceProcessor processor;
    const auto status = processor.Load("../data/sentencepiece.bpe.model");
    if (!status.ok()) {
       std::cerr << status.ToString() << std::endl;
       // error
    }
    std::cout << "Model loaded successfully" << std::endl;
    std::vector<std::string> pieces;
    processor.Encode("Hello from C++", &pieces);
    for (const std::string &token : pieces)
        std::cout << token << std::endl;
    return 0;
}
