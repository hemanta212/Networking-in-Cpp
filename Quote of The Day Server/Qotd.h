#pragma once
#include <string>
#include <fstream>
#include <vector>

class CQotd {
public:
    // Constructor
    CQotd(std::string filename);

    // Get a random quote from the file
    std::string GetRandomQuote();

    

private:
    std::vector<std::string> m_quotes;
};
