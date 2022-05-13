#include "Qotd.h"

// Constructor
CQotd::CQotd(std::string filename) {
    std::ifstream file;
    file.open(filename);
    if (file.is_open()) {
        std::string line;
        std::string running = "";
        while (getline(file, line)) {
            if (line != "%") {
                running = running + line + "\n";
            }
            else {
                m_quotes.push_back(running);
                running = "";
            }
        }
    }

}

    // Get a random quote from the file
std::string CQotd::GetRandomQuote() {
    int random = rand() % m_quotes.size();
    return m_quotes[random];
}

 