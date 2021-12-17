#pragma once

#include <map>
#include <string>

namespace lzw
{
    /* available functions */

    std::map<std::string, uint16_t> initialize_compression_dict();
    std::map<uint16_t, std::string> initialize_decompression_dict();

    std::string compress(
        const std::string &_text,
        std::map<std::string, uint16_t> dict = initialize_compression_dict()
    );

    std::string decompress(
        const std::string &_compressed_text,
        std::map<uint16_t, std::string> dict = initialize_decompression_dict()
    );



    // implementation
    std::string compress(
        const std::string &_text,
        std::map<std::string, uint16_t> dict 
    )
    {
        std::string compressed_message;

        std::string last;
        std::string current;
        for(auto c : _text)
        {
            current = c;

            if(dict.find(std::string{last + current}) != dict.end())
            {
                last = last + current;
            } else {
                compressed_message += std::to_string(dict[last]) + ' ';
                dict.insert({last + current, dict.size()});
                last = current;
            }
        }
        compressed_message += std::to_string(dict[last]) + ' ';
        return compressed_message;
    }

    std::string decompress(
        const std::string &_compressed_text,
        std::map<uint16_t, std::string> dict
    )
    {
        return std::string{};
    }

    std::map<std::string, uint16_t> initialize_compression_dict()
    {
        return std::map<std::string, uint16_t>{
            {"#", 1},
            {"$", 2},
            {"%", 3},
            {"&", 4},
            {"'", 5},
            {"(", 6},
            {")", 7},
            {"*", 8},
            {"+", 9},
            {",", 10},
            {"-", 11},
            {".", 12},
            {"/", 13},
            {"0", 14},
            {"1", 15},
            {"2", 16},
            {"3", 17},
            {"4", 18},
            {"5", 19},
            {"6", 20},
            {"7", 21},
            {"8", 22},
            {"9", 23},
            {":", 24},
            {";", 25},
            {"<", 26},
            {"=", 27},
            {">", 28},
            {"?", 29},
            {"@", 30},
            {"A", 31},
            {"B", 32},
            {"C", 33},
            {"D", 34},
            {"E", 35},
            {"F", 36},
            {"G", 37},
            {"H", 38},
            {"I", 39},
            {"J", 40},
            {"K", 41},
            {"L", 42},
            {"M", 43},
            {"N", 44},
            {"O", 45},
            {"P", 46},
            {"Q", 47},
            {"R", 48},
            {"S", 49},
            {"T", 50},
            {"U", 51},
            {"V", 52},
            {"W", 53},
            {"X", 54},
            {"Y", 55},
            {"Z", 56},
            {"[", 57},
            {"\\", 58},
            {"]", 59},
            {"^", 60},
            {"_", 61},
            {"`", 62},
            {"a", 63},
            {"b", 64},
            {"c", 65},
            {"d", 66},
            {"e", 67},
            {"f", 68},
            {"g", 69},
            {"h", 70},
            {"i", 71},
            {"j", 72},
            {"k", 73},
            {"l", 74},
            {"m", 75},
            {"n", 76},
            {"o", 77},
            {"p", 78},
            {"q", 79},
            {"r", 80},
            {"s", 81},
            {"t", 82},
            {"u", 83},
            {"v", 84},
            {"w", 85},
            {"x", 86},
            {"y", 87},
            {"z", 88},
            {"{", 89},
            {"|", 90},
            {"}", 91},
            {"~", 92},
            {"!", 93}
        };
    }
    std::map<uint16_t, std::string> initialize_decompression_dict()
    {
        return std::map<uint16_t, std::string>{
            {1, "#"},
            {2, "$"},
            {3, "%"},
            {4, "&"},
            {5, "'"},
            {6, "("},
            {7, ")"},
            {8, "*"},
            {9, "+"},
            {10, ","},
            {11, "-"},
            {12, "."},
            {13, "/"},
            {14, "0"},
            {15, "1"},
            {16, "2"},
            {17, "3"},
            {18, "4"},
            {19, "5"},
            {20, "6"},
            {21, "7"},
            {22, "8"},
            {23, "9"},
            {24, ":"},
            {25, ";"},
            {26, "<"},
            {27, "="},
            {28, ">"},
            {29, "?"},
            {30, "@"},
            {31, "A"},
            {32, "B"},
            {33, "C"},
            {34, "D"},
            {35, "E"},
            {36, "F"},
            {37, "G"},
            {38, "H"},
            {39, "I"},
            {40, "J"},
            {41, "K"},
            {42, "L"},
            {43, "M"},
            {44, "N"},
            {45, "O"},
            {46, "P"},
            {47, "Q"},
            {48, "R"},
            {49, "S"},
            {50, "T"},
            {51, "U"},
            {52, "V"},
            {53, "W"},
            {54, "X"},
            {55, "Y"},
            {56, "Z"},
            {57, "["},
            {58, "\\"},
            {59, "]"},
            {60, "^"},
            {61, "_"},
            {62, "`"},
            {63, "a"},
            {64, "b"},
            {65, "c"},
            {66, "d"},
            {67, "e"},
            {68, "f"},
            {69, "g"},
            {70, "h"},
            {71, "i"},
            {72, "j"},
            {73, "k"},
            {74, "l"},
            {75, "m"},
            {76, "n"},
            {77, "o"},
            {78, "p"},
            {79, "q"},
            {80, "r"},
            {81, "s"},
            {82, "t"},
            {83, "u"},
            {84, "v"},
            {85, "w"},
            {86, "x"},
            {87, "y"},
            {88, "z"},
            {89, "{"},
            {90, "|"},
            {91, "}"},
            {92, "~"},
            {93, ""},
            {93, "!"}
        };
    }
}
