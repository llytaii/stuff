#include <iostream>
#include <iomanip>
#include <string>

int main(const int argc, const char* argv[])
{
    if(argc == 1)
    {
        std::cout << "input:  character(s) as parameter\n"
                  << "output: ascii code for character(s)\n";
        return -1;
    }

    std::string s;
    for(size_t i{1}; i < argc; ++i)
    {
        s += argv[i];
        s += ' ';
    } 

    std::cout << s << std::endl;

    for(char c : s)
    {
        if(c == ' ')
            std::cout << ' ';
        else
            std::cout << static_cast<int>(c);
    }

    std::cout << std::endl;
    return 0;
}