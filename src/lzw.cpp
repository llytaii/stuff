#include <iostream>

#include "lzw.h"

int main()
{
    std::cout << lzw::compress("Hello World!") << std::endl;
}