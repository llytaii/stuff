#include <chrono>
#include <cmath>
#include <iostream>
#include <map>
#include <string>

#include <boost/algorithm/string/trim.hpp>

bool init(const int _argc, const char *_argv[], std::string &_message);

double I(double _probability);                                    // Informationsgehalt eines Zeichens: I(x) = log2(1/p(x)) bit
double H(size_t _char_sum, std::map<char, size_t> &_char_counts); // Entropie (mittlerer Informationsgehalt der Zeichen einer Nachricht)
                                                                  // Summe aus p(x) * I(x)
double H0(size_t _alphabet_sum);                                  // Entscheidungsgehalt == maximaler Informationsgehalt == Gleichverteilung
double R(double _H0, double _H);                                  // Redundanz: R = H0 - H
double r(double _H0, double _H);                                  // relative Redundanz: r = (H0 - H) / H0 %
// TODO: L (mittlere Codewortlänge)

int main(const int argc, const char *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    std::string message;

    if (!init(argc, argv, message))
    {
        std::cout << "usage: provide a message via environment arguments or pipe\n";
        return -1;
    }

    std::map<char, size_t> char_table;
    size_t char_sum = message.size();
    for (auto c : message)
        ++char_table[c];

    // Berechnungen
    double entropie = H(char_sum, char_table);
    double max_entropie = H0(char_table.size());
    double redundanz = R(max_entropie, entropie);
    double rel_redundanz = r(max_entropie, entropie);


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    // Ausgabe
    // std::cout << "Nachricht: " << nachricht << std::endl;
    std::cout << "Länge: " << message.size() << " Zeichen" << std::endl;
    std::cout << "Alphabet: ";
    for (auto c : char_table)
        std::cout << "\"" << c.first << "\" : " << c.second << ";" << ' ';
    std::cout << std::endl;
    std::cout << "Maximale Entropie H0: " << max_entropie << std::endl;
    std::cout << "Entropie H: " << entropie << std::endl;
    std::cout << "Redundanz R: " << redundanz << std::endl;
    std::cout << "Relative Redundanz r: " << rel_redundanz << std::endl;
    std::cout << "Dauer: " << duration.count() << " ms" << std::endl;

    return 0;
}

double I(double _probability)
{
    return log2(1.0 / _probability);
}

double H(size_t _char_sum, std::map<char, size_t> &_char_counts)
{
    double entropie{0};
    for (auto c : _char_counts)
    {
        double probability{double(c.second) / _char_sum};
        entropie += probability * I(probability);
    }
    return entropie;
}

double H0(size_t _alphabet_sum)
{
    return log2(_alphabet_sum);
}

double R(double _H0, double _H)
{
    return _H0 - _H;
}

double r(double _H0, double _H)
{
    return (_H0 - _H) / _H0;
}

bool init(const int _argc, const char *_argv[], std::string &_message)
{
    if (_argc > 1)
    {
        for (size_t i{1}; i < _argc; ++i)
        {
            _message += std::string{_argv[i]} + ' ';
        }
        boost::algorithm::trim(_message);
        return true;
    }
    else
    {
        for (std::string tmp; std::getline(std::cin, tmp);)
        {
            boost::algorithm::trim(tmp);
            _message += tmp + ' ';
        }
        boost::algorithm::trim(_message);
        return true;
    }
    return false;
}
