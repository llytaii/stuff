#include <chrono>

class timer
{
public:
    // start timer
    timer() : m_start{std::chrono::high_resolution_clock::now()}{};

    inline void start() {
        m_start = std::chrono::high_resolution_clock::now();
    };

    // end timer
    inline void stop() {
        m_stop = std::chrono::high_resolution_clock::now();
    };

    // get time as return_type = float/double, time_resolution = std::millis, etc
    template<typename return_type, typename time_resolution>
    inline return_type get_duration() {
        return std::chrono::duration<return_type, time_resolution>{m_stop - m_start}.count();
    };


private:
    std::chrono::_V2::system_clock::time_point m_start{};
    std::chrono::_V2::system_clock::time_point m_stop{};
};