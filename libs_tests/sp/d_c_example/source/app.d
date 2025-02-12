import std.stdio : writeln;
import std.string : toStringz;
import std.conv : to;
import sp_c_api;

void main() {
    string input = "Hello from D";
    SentencePieceProcessor* proc = spp_new();
    int status = spp_load(proc, "../data/sentencepiece.bpe.model");
    size_t len;
    size_t sentence_len = input.length;
    auto cinput = input.toStringz();
    //auto result = spp_encode_as_serialized_proto(proc, cinput, sentence_len, &len);
    auto result = spp_encode(proc, cinput, sentence_len, &len);
    foreach(i; 0..len)
        writeln((cast(char*)result[i]).to!string);
}