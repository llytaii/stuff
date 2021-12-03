#include <array>
#include <cmath>
#include <iostream>

int main()
{
    for (size_t i = 35; i < 128; i++)
    {
        std::cout << "{\"" << char(i) << "\"," << i - 34 << "}," << std::endl;
    }
    for (size_t i = 0; i < 256; i++)
    {
        std::cout << "{" << i - 34 << ",\"" << char(i) << "\"}," << std::endl;
    }
}
