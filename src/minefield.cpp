#include <iostream>
#include <vector>

int main()
{
    uint8_t rows, columns;
    std::vector<uint8_t> numbers;

    std::cin >> rows >> columns;

    for (uint8_t row = 0; row < rows; row++)
    {
        for (uint8_t column = 0; column < columns; column++)
        {
            uint8_t tmp;
            std::cin >> tmp;
            numbers.push_back(tmp);
        }
    }

    std::cout << std::endl;
    std::cout << rows << ' ' << columns;

    for (uint8_t row = 0; row < rows; row++)
    {
        for (uint8_t column = 0; column < columns; column++)
        {
            std::cout << numbers.at(rows * row + column) << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}