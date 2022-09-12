#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <map>
#include <string>

#include <boost/algorithm/string/trim.hpp>

// fetch input from pipe or arg into _text
bool fetch_input(const int _argc, const char *_argv[], std::string &_message);

// Informationsgehalt eines Zeichens: I(x) = log2(1/p(x)) Bit
double I(double _p);                                    
// Entropie (mittlerer Informationsgehalt der Zeichen einer Nachricht), Summe aus p(x) * I(x)
double H(size_t _char_sum, std::map<char, size_t> &_char_counts); 
 // Entscheidungsgehalt == maximaler Informationsgehalt == Gleichverteilung                                                                 
double H0(size_t _alphabet_sum);                                  
// Redundanz: R = H0 - H
double R(double _H0, double _H);                                  
// relative Redundanz: r = (H0 - H) / H0
double r(double _H0, double _H);                                  
// TODO: L (mittlere Codewortlänge)

int main(const int argc, const char *argv[])
{

    std::string message;
    if (!fetch_input(argc, argv, message))
    {
        std::cout << "usage: provide a message via environment arguments or pipe\n";
        return -1;
    }

    std::map<char, size_t> char_table;
    size_t char_sum = char_table.size();

    // Timer start
    auto start = std::chrono::high_resolution_clock::now();

    for (auto c : message)
        ++char_table[c];

    // Timer stop
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::map<size_t, char> char_table2;
    for(auto& p : char_table)
        char_table2.insert({p.second, p.first});

    // Berechnungen
    double entropie = H(char_sum, char_table);
    double max_entropie = H0(char_table.size());
    double redundanz = R(max_entropie, entropie);
    double rel_redundanz = r(max_entropie, entropie);


    // Ausgabe
    // std::cout << "Nachricht: " << nachricht << std::endl;
    std::cout << "Länge: " << message.size() << " Zeichen" << std::endl;
    std::cout << "Alphabet: ";
    for (auto c : char_table2)
        std::cout << "\"" << c.second << "\" : " << c.first << ";" << ' ';
    std::cout << std::endl;
    std::cout << "Maximale Entropie H0: " << max_entropie << std::endl;
    std::cout << "Entropie H: " << entropie << std::endl;
    std::cout << "Redundanz R: " << redundanz << std::endl;
    std::cout << "Relative Redundanz r: " << rel_redundanz << std::endl;
    std::cout << "Dauer: " << duration.count() << " ms" << std::endl;

    return 0;
}

double I(double _p)
{
    return log2(1.0 / _p);
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

bool fetch_input(const int _argc, const char *_argv[], std::string &_message)
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
