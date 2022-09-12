#include <iostream>

#include "timer.h"

void test_function() {
    for(size_t i{0}; i < 1'000'000'0; ++i) std::cout << i << ' ';
    std::cout << std::endl;
}

int main(int, char**)
{
    timer t;
    test_function();
    t.stop();
    auto duration_enabled = t.get_duration<double, std::milli>();
    std::ios_base::sync_with_stdio(false);

    t.start();
    test_function();
    t.stop();
    auto duration_disabled = t.get_duration<double, std::milli>();

    std::cout << "sync_with_stdio enabled: " << duration_enabled << " ms\n";
    std::cout << "sync_with_stdio disabled: " << duration_disabled<< " ms\n";
    return 0;
}
