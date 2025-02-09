module app;

import core.stdcpp.string_view : string_view;
import core.stdcpp.memory : unique_ptr;
import core.stdcpp.utility : pair;
import bc.string : RCString;
import dvector;

extern (C++,`sentencepiece`)
{
  extern (C++,`util`)
  {
    enum StatusCode : int
    {
      kOk = 0,
      kCancelled = 1,
      kUnknown = 2,
      kInvalidArgument = 3,
      kDeadlineExceeded = 4,
      kNotFound = 5,
      kAlreadyExists = 6,
      kPermissionDenied = 7,
      kResourceExhausted = 8,
      kFailedPrecondition = 9,
      kAborted = 10,
      kOutOfRange = 11,
      kUnimplemented = 12,
      kInternal = 13,
      kUnavailable = 14,
      kDataLoss = 15,
      kUnauthenticated = 16,
    }

    extern (C++, struct) struct Status
    {
    public:
      //this();
      ~this();
      this(StatusCode code, string_view error_message);
      this(ref const Status s);
      //bool opEquals(ref Status s) const;
      bool ok() const {return rep_ is null;};
      void set_error_message(const char* str);
      const(char*) error_message() const;
      const(char*) message() const
      {
        return error_message();
      }

      StatusCode code() const;
      string_view ToString() const;
      void IgnoreError();
    private:
      struct Rep {}
      Rep* rep_;
    }
  }
  extern (C++,struct) struct NBestSentencePieceText;
  extern (C++,struct) struct ModelInterface;
  extern (C++,struct) struct SentencePieceText;
  extern (C++,struct) struct ModelProto;
  extern (C++,struct) struct NormalizerSpec;

  extern (C++,`normalizer`) extern (C++,struct) struct Normalizer;

  extern (C++,class) class SentencePieceProcessor
  {
    this();
    ~this();
    abstract Status Load(string_view filename);
    abstract void LoadOrDie(string_view filename);
    abstract Status Load(const(ModelProto*) model_proto);
    //TODO: fix move function
    //abstract Status Load(unique_ptr!ModelProto model_proto);
    abstract Status LoadFromSerializedProto(string_view serialized);
    abstract Status status() const;
    abstract Status SetEncodeExtraOptions(string_view extra_option);
    abstract Status SetDecodeExtraOptions(string_view extra_option);

    // Vocabulary restriction
    //TODO: fix type. it should be vector<string_view>
    abstract Status SetVocabulary(Dvector!RCString valid_vocab);
    abstract Status ResetVocabulary();
    abstract Status LoadVocabulary(string_view file_name, int threshold);

    // Simple Econde and Decode API
    abstract Status Encode(string_view input, Dvector!RCString* pieces) const;
    abstract Status Encode(string_view input, Dvector!int* ids) const;
    abstract Status Decode(const(Dvector!RCString) pieces, RCString* detokenized) const;
    abstract Status Decode(const(Dvector!string) pieces, RCString* detokenized) const;
    abstract Status Decode(const(Dvector!int) ids, RCString* detokenized) const;

    // NBest API
    abstract Status NBestEncode(string_view input, int nbest_size,
      ref Dvector!(Dvector!(string))* pieces) const;
    abstract Status NBestEncode(string_view input, int nbest_size,
      ref Dvector!(Dvector!(int))* ids) const;

    // Sampling API
    abstract Status SampleEncodeAndScore(
      string_view input, int num_samples, float alpha, bool wor,
      bool include_best,
      Dvector!(pair!(Dvector!RCString, float))* pieces) const;
    abstract Status SampleEncodeAndScore(
      string_view input, int num_samples, float alpha, bool wor,
      bool include_best,
      Dvector!(pair!(Dvector!int, float))* ids) const;

    // Entropy API
    abstract Status CalculateEntropy(string_view input, float alpha,
      float* entropy) const;
    abstract Status Encode(string_view input, SentencePieceText* spt) const;
    abstract Status NBestEncode(string_view input, int nbest_size,
      NBestSentencePieceText* nbest_spt) const;
    abstract Status SampleEncode(string_view input, int nbest_size,
      float alpha, SentencePieceText* spt) const;
    abstract Status SampleEncodeAndScore(
      string_view input, int num_samples, float alpha, bool wor,
      bool include_best, NBestSentencePieceText* samples_spt) const;
    abstract Status Decode(const(Dvector!RCString) pieces,
      SentencePieceText* spt) const;
    abstract Status Decode(const(Dvector!int) ids,
      SentencePieceText* spt) const;

    // Normalization methods
    abstract Status Normalize(string_view input, RCString* normalized) const;
    abstract Status Normalize(string_view input, RCString* normalized, Dvector!size_t* norm_to_orig) const;
    abstract RCString Normalize(string_view input) const;

    // IO related functions
    extern (C++,`io`)
    {
      Status LoadModelProto(string_view file_name, ModelProto* model_proto);
      Status SaveModelProto(string_view file_name, ref const ModelProto model_proto);
    }
  }
}

T alloc(T, Args...)(auto ref Args args)
{
  enum tsize = __traits(classInstanceSize, T);
  T t = () @trusted {
    import core.memory : pureMalloc;

    auto _t = cast(T) pureMalloc(tsize);
    if (!_t)
      return null;
    import core.stdc.string : memcpy;

    memcpy(cast(void*) _t, __traits(initSymbol, T).ptr, tsize);
    return _t;
  }();
  if (!t)
    return null;
  import core.lifetime : forward;

  t.__ctor(forward!args);

  return t;
}

void destroy(T)(ref T t)
{
  static if (__traits(hasMember, T, "__xdtor"))
    t.__xdtor();
  import core.memory : pureFree;

  pureFree(cast(void*) t);
  static if (__traits(compiles, { t = null; }))
    t = null;
}

void main()
{
  import core.stdc.stdio : printf;

  SentencePieceProcessor proc = alloc!SentencePieceProcessor();
  scope(exit) destroy(proc);
  string_view model_path = "../data/sentencepiece.bpe.model";
  printf("Model path: %s\n", cast(char*) model_path);

  if (proc is null)
  {
    printf("NULL!!\n");
  }

  printf("Before status calculated\n");
  auto status = proc.Load(model_path);

  if (!status.ok())
  {
    printf("Error %s/n", cast(char*) status.ToString());
  }
  printf("Model loaded successfully\n");
}
