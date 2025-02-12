#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>
#include <vector>
#include <iostream>
#include <fstream>

#include <sentencepiece_processor.h>

using absl::string_view;
using sentencepiece::SentencePieceProcessor;
using sentencepiece::SentencePieceText;

// Inspired by:
// https://stackoverflow.com/a/14589519
template<typename E>
constexpr auto to_underlying_type(E e) -> typename std::underlying_type<E>::type 
{
   return static_cast<typename std::underlying_type<E>::type>(e);
}

extern "C" {

SentencePieceProcessor *spp_new() {
  return new SentencePieceProcessor();
}

int spp_bos_id(SentencePieceProcessor *spp) {
  return spp->bos_id();
}

int spp_decode_piece_ids(SentencePieceProcessor *spp, uint32_t const *pieces, size_t pieces_len, unsigned char **decoded, size_t *decoded_len) {
    std::vector<int> int_pieces;
    int_pieces.reserve(pieces_len);

    for (uint32_t const *piece = pieces; piece != pieces + pieces_len; ++piece) {
        int_pieces.push_back(static_cast<int>(*piece));
    }

    std::string decoded_string;
    auto status = spp->Decode(int_pieces, &decoded_string);

    *decoded_len = decoded_string.size();
    *decoded = static_cast<unsigned char *>(malloc(decoded_string.size()));
    memcpy(*decoded, decoded_string.data(), decoded_string.size());

    return to_underlying_type(status.code());
}

int spp_decode_pieces(SentencePieceProcessor *spp, char const * const *pieces, size_t pieces_len, unsigned char **decoded, size_t *decoded_len) {
    std::vector<absl::string_view> str_pieces;
    str_pieces.reserve(pieces_len);
  
    for (char const * const *piece = pieces; piece != pieces + pieces_len; ++piece) {
        str_pieces.push_back(*piece);
    }

    std::string decoded_string;
    auto status = spp->Decode(str_pieces, &decoded_string);

    *decoded_len = decoded_string.size();
    *decoded = static_cast<unsigned char *>(malloc(decoded_string.size()));
    memcpy(*decoded, decoded_string.data(), decoded_string.size());

    return to_underlying_type(status.code());
}

unsigned char *spp_encode_as_serialized_proto(SentencePieceProcessor *spp, char const *sentence, size_t sentence_len, size_t *len) {
  auto sentence_view = absl::string_view(sentence, sentence_len);
  auto serialized = spp->EncodeAsSerializedProto(sentence_view);

  *len = serialized.size();
  unsigned char *data = (unsigned char *) malloc(serialized.size());
  memcpy(data, serialized.data(), serialized.size());

  return data;
}

// new test
unsigned char **spp_encode(SentencePieceProcessor *spp, char const *sentence, size_t sentence_len, size_t *len) {
  auto sentence_view = absl::string_view(sentence, sentence_len);
  std::vector<std::string> pieces;
  auto status = spp->Encode(sentence_view, &pieces);

  // debug
  std::ofstream outFile("output.txt");
  for(const std::string& str : pieces) {
    outFile << str << std::endl;
  }
  outFile.close();
  
  *len = pieces.size();
  unsigned char** result = new unsigned char*[*len];

  for (size_t i = 0; i < *len; ++i) {
      unsigned char *data= (unsigned char *) malloc(pieces[i].size());
      memcpy(data, pieces[i].data(), pieces[i].size());
      result[i] = data;
  }

  return result;
}

unsigned char *spp_sample_encode_as_serialized_proto(SentencePieceProcessor *spp, char const *sentence, size_t sentence_len, size_t *len, size_t nbest, float alpha) {
  auto sentence_view = absl::string_view(sentence, sentence_len);
  auto serialized = spp->SampleEncodeAsSerializedProto(sentence_view, static_cast<int>(nbest), alpha);

  *len = serialized.size();
  unsigned char *data = (unsigned char *) malloc(serialized.size());
  memcpy(data, serialized.data(), serialized.size());

  return data;
}

int spp_eos_id(SentencePieceProcessor *spp) {
  return spp->eos_id();
}

int spp_load(SentencePieceProcessor *spp, char const *filename) {
  auto status = spp->Load(filename);
  return to_underlying_type(status.code());
}

bool spp_is_unknown(SentencePieceProcessor *spp, int id) {
  return spp->IsUnknown(id);
}

int spp_pad_id(SentencePieceProcessor *spp) {
  return spp->pad_id();
}

int spp_piece_size(SentencePieceProcessor *spp) {
  return spp->GetPieceSize();
}

int spp_piece_to_id(SentencePieceProcessor *spp, char const *piece) {
  return spp->PieceToId(piece);
}

int spp_from_serialized_proto(SentencePieceProcessor *spp, char const *data, size_t len) {
  auto status = spp->LoadFromSerializedProto(string_view(data, len));
  return to_underlying_type(status.code());
}

unsigned char *spp_to_serialized_proto(SentencePieceProcessor *spp, size_t *len) {
  auto serialized = spp->serialized_model_proto();

  *len = serialized.size();
  unsigned char *data = (unsigned char *) malloc(serialized.size());
  memcpy(data, serialized.data(), serialized.size());

  return data;
}

void spp_free(SentencePieceProcessor *spp) {
  delete spp;
}

int spp_unk_id(SentencePieceProcessor *spp) {
  return spp->unk_id();
}

}