#include <vector>
#include <string>
#include <string_view>

namespace test {
    class Status {
        public:
        int error_message();
        void print_string(std::string_view input);
        void fix_array(std::string_view input, std::vector<std::string>* words);
    };
}