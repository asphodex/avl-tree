#include "include/config.h"
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>

std::map<std::string, std::string> loadConfigFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::map<std::string, std::string> config;
    std::string line;
    std::string currentKey;
    std::ostringstream currentText;

    while (std::getline(file, line)) {
        if (line[0] == '#') {
            if (!currentKey.empty()) {
                config[currentKey] = currentText.str();
            }
            currentKey = line.substr(2);
            currentText.str("");
        } else {
            if (!currentKey.empty()) {
                if (!currentText.str().empty()) {
                    currentText << "\n";
                }
                currentText << line;
            }
        }
    }

    if (!currentKey.empty()) {
        config[currentKey] = currentText.str();
    }

    file.close();
    return config;
}