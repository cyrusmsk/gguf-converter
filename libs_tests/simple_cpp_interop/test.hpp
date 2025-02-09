namespace test {
    enum class StatusCode: int {
        c0 = 0,
        c1 = 1,
    };

    class Status {
        public:
        StatusCode error_message();
    };
}