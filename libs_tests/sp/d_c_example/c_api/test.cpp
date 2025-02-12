#include "sentencepiece.h"
#include <iostream>

int main() {
    SentencePieceProcessor* proc = spp_new();
    int status = spp_load(proc, "../../data/sentencepiece.bpe.model");
    std::cout << status << std::endl;
    char* input = (char*)"Hello from C++";
    size_t len;
    auto result = spp_encode_as_serialized_proto(proc, input, 14, &len);
    std::cout << len << std::endl;
    for(int i = 0; i < len; i++) {
        std::cout << result[i] << std::endl;
    }
    return 0;
}
