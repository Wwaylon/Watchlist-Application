#pragma once
#include <string>
#include <istream>
#include <sstream>

struct ItemData
{
    int id;
    std::string name, genre, status;

    // Simple and not error-proof. Do not use in production.
    /*
    static ItemData fromCsvLine(std::istream &stream)
    {
        constexpr int count = 7;

        std::string line;
        std::stringstream lineStream;

        if (std::getline(stream, line))
        {
            std::string cells[count];
            lineStream << line;

            for (int i = 0; i < count && std::getline(lineStream, cells[i], ','); i++)
                ;

            auto doubleOrZero = [](const std::string &str)
            { return str.empty() ? 0.0 : std::stod(str); };
            auto intOrZero = [](const std::string &str)
            { return str.empty() ? 0 : std::stoi(str); };

            ItemData result{
                intOrZero(cells[0]),
                cells[1],
                cells[2]};

            return result;
        }
        else
        {
            return {};
        }
    }*/
};