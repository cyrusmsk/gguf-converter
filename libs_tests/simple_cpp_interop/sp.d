import std.stdio: writeln;
import std.string;

enum StatusCode: int {
    c0 = 0,
    c1 = 1 
}

extern(C++, `test`) extern(C++, class) class Status {
    StatusCode error_message();
}

void main() {
    auto x = new Status();
    writeln(x.error_message());
}