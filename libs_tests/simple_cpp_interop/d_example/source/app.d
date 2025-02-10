import std.stdio : writeln;
import std.string;
import std.conv;
import core.stdcpp.string_view;

extern (C++,`test`) extern (C++,struct) struct Status
{
    int error_message();
    void print_string(string_view input);
}

extern (C)
{
    void fix_array_capi(Status* x, string_view input, char*** words, size_t* num_words);
}

void main()
{
    auto x = new Status();

    string_view input = string_view("hello world this is D");
    char** words;
    size_t num_words;

    x.print_string(input);

    fix_array_capi(x, input, &words, &num_words);

    writeln("Modified words: ");
    foreach (k; 0 .. num_words)
        writeln(words[k].to!string);
}
