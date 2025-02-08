namespace test {
    enum class StatusCode: int {
        c1 = 0,
        c2 = 1,
    };

    class Status {
        public:
        StatusCode error_message();
    };
}