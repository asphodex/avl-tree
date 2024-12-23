//
// Created by sphdx on 22.12.2024.
//

#ifndef APP_H
#define APP_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>
#include <limits>
#include <string>

template <typename TreeType, typename KeyType>
class app {
    static TreeType tree;
    static std::string menuText, getInputText, wrongInputText;
    int maxAction, minAction;
    void (*menu)(const int&, std::string&, int&);
public:
    app(const std::string &menuText, const std::string &getInputText, const std::string &wrongInputText, const TreeType &tree, void (*menu)(const int&, std::string&, int&), const int &maxAction, const int &minAction);

    void start() const;
    static void showMenu();
    static void showGetInputText();
    static void showWrongInputText();
    static void handleAction(int &action);
    static void performPrint(void (TreeType::*print)() const);
    static void performAction(void (TreeType::*action)(KeyType key, int id), KeyType key, int id);
    static void performAction(void (TreeType::*action)());
    static void loadDataFromFile(const std::string &pathToFile, void (TreeType::*clearTree)(), void (TreeType::*insert)(KeyType key, int id), bool (*isValid)(const std::string&), KeyType (*parseKeyType)(const std::string&));
    static void saveTreeToFile(const std::string& pathToFile, void (TreeType::*traversal)() const);
};

template <typename TreeType, typename KeyType>
TreeType app<TreeType, KeyType>::tree;
template <typename TreeType, typename KeyType>
std::string app<TreeType, KeyType>::menuText;
template <typename TreeType, typename KeyType>
std::string app<TreeType, KeyType>::getInputText;
template <typename TreeType, typename KeyType>
std::string app<TreeType, KeyType>::wrongInputText;

template <typename TreeType, typename KeyType>
app<TreeType, KeyType>::app(const std::string &menuText, const std::string &getInputText, const std::string &wrongInputText, const TreeType &tree, void (*menu)(const int&, std::string&, int&), const int &maxAction, const int &minAction) {
    app::menuText = menuText;
    app::getInputText = getInputText;
    app::wrongInputText = wrongInputText;
    app::tree = tree;
    this->menu = menu;
    this->maxAction = maxAction;
    this->minAction = minAction;
}

template <typename TreeType, typename KeyType>
void app<TreeType, KeyType>::start() const {
    showMenu();
    std::string key;
    int action = 0, id = 0;

    do {
        handleAction(action);
        menu(action, key, id);
    } while (action >= minAction && action <= maxAction);
}

template <typename TreeType, typename KeyType>
void app<TreeType, KeyType>::showMenu() {
    std::cout << menuText << std::endl;
}

template <typename TreeType, typename KeyType>
void app<TreeType, KeyType>::showGetInputText() {
    std::cout << getInputText << std::endl;
}

template <typename TreeType, typename KeyType>
void app<TreeType, KeyType>::showWrongInputText() {
    std::cout << wrongInputText << std::endl;
}

template <typename TreeType, typename KeyType>
void app<TreeType, KeyType>::handleAction(int &action) {
    std::cout << "Input: ";
    std::cin >> action;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
    std::cout << std::endl;
}

template <typename TreeType, typename KeyType>
void app<TreeType, KeyType>::performPrint(void(TreeType::*print)() const) {
     (tree.*print)();
}

template <typename TreeType, typename KeyType>
void app<TreeType, KeyType>::performAction(void(TreeType::*action)(KeyType key, int id), const KeyType key, const int id) {
    (tree.*action)(key, id);
}

template <typename TreeType, typename KeyType>
void app<TreeType, KeyType>::performAction(void (TreeType::*action)()) {
    (tree.*action)();
}

template <typename TreeType, typename KeyType>
void app<TreeType, KeyType>::loadDataFromFile(const std::string &pathToFile, void (TreeType::*clearTree)(), void (TreeType::*insert)(KeyType key, int id), bool (*isValid)(const std::string&), KeyType (*parseKeyType)(const std::string&)) {
    if (pathToFile.empty()) {
        std::cerr << "Path to file is empty" << std::endl;
        return;
    }

    (tree.*clearTree)();

    std::ifstream file(pathToFile);
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;
        if (isValid(line.substr(0, 6)))
            performAction(insert, parseKeyType(line), lineNumber);
        else
            std::cerr << "Invalid license key at line " << lineNumber << ": " << line << std::endl;
    }
}

template <typename TreeType, typename KeyType>
void app<TreeType, KeyType>::saveTreeToFile(const std::string &pathToFile, void (TreeType::*traversal)() const) {
    if (pathToFile.empty()) {
        std::cerr << "Path to file is empty" << std::endl;
        return;
    }
    std::ofstream file(pathToFile);
    std::stringstream buffer;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(buffer.rdbuf());

    (tree.*traversal)();

    std::cout.rdbuf(oldCoutBuf);
    file << buffer.str();
}

#endif //APP_H
