#include <iostream>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>

std::string caesarCipher(std::string _s, int _key)
{
    int letter_space{26};
    _key %= letter_space;

    for (int i{0}; i < _s.size(); ++i)
    {
        if (_s[i] >= 'a' && _s[i] <= 'z')
            _s[i] += (_s[i] + _key < 'a') ? _key + letter_space : (_s[i] + _key > 'z') ? _key - letter_space
                                                                                       : _key;
        else if (_s[i] >= 'A' && _s[i] <= 'Z')
            _s[i] += (_s[i] + _key < 'A') ? _key + letter_space : (_s[i] + _key > 'Z') ? _key - letter_space
                                                                                       : _key;
    }
    return _s;
}

int main(const int _argc, const char *_argv[])
{
    if (_argc < 3)
    {
        std::cout << "usage: <message> <key:int>" << std::endl;
        std::cout << "only works for 'a' - 'z' / 'A' - 'Z'" << std::endl;
        return -1;
    }

    std::string input{};
    int key;
    try
    {
        key = boost::lexical_cast<int>(_argv[_argc - 1]);
    }
    catch (const boost::bad_lexical_cast &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    for (size_t i{1}; i < _argc - 1; ++i)
        input += std::string{_argv[i]} + ' ';

    boost::algorithm::trim(input);

    std::cout << "original  : " << input << std::endl;
    std::cout << "encrypted : " << caesarCipher(input, key) << std::endl;
    std::cout << "decrypted : " << caesarCipher(caesarCipher(input, key), -key) << std::endl;
}
