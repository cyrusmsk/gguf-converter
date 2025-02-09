module app;

import core.stdcpp.string_view : string_view;

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

extern (C++,`sentencepiece`)
{
  extern (C++,`util`) extern (C++,class) class Status
  {
    this(StatusCode code, string_view error_message);
    this(const ref Status s);
    bool ok() const;
    void set_error_message(const char* str);
    const(char*) error_message() const;
    const(char*) message() const;
    StatusCode code() const;
    string_view ToString() const;
    void IgnoreError();
  }
}

extern(C) void main()
{
    import core.stdc.stdio : printf;
    printf("Hi\n");
}
