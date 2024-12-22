#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "app.h"
#include "AVL.h"
#include "LicensePlate.h"

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
            // если найдена новая секция, сохраняем предыдущую
            if (!currentKey.empty()) {
                config[currentKey] = currentText.str();
            }

            // начинаем новую секцию
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

    // сохраяем последнюю секцию
    if (!currentKey.empty()) {
        config[currentKey] = currentText.str();
    }

    file.close();

    return config;
}

void menu(const int& action, std::string& key, int& id) {
    switch (action) {
        case 1:
        case 2: {
            App<AVLTree<LicensePlate>, LicensePlate>::showGetInputText();
            std::cin >> key >> id;

            if (isValidLicensePlate(key)) {
                const LicensePlate lp = parseLicensePlate(key);

                if (action == 1) {
                    App<AVLTree<LicensePlate>, LicensePlate>::performAction(&AVLTree<LicensePlate>::insert, lp, id);
                } else {
                    App<AVLTree<LicensePlate>, LicensePlate>::performAction(&AVLTree<LicensePlate>::del, lp, id);
                }
            } else {
                App<AVLTree<LicensePlate>, LicensePlate>::showWrongInputText();
            }
            break;
        }
        case 3:
            App<AVLTree<LicensePlate>, LicensePlate>::performPrint(&AVLTree<LicensePlate>::printTree);
            break;
        case 4:
            App<AVLTree<LicensePlate>, LicensePlate>::performPrint(&AVLTree<LicensePlate>::printInOrder);
            break;
        case 5:
            App<AVLTree<LicensePlate>, LicensePlate>::performPrint(&AVLTree<LicensePlate>::printPreOrder);
            break;
        case 6:
            App<AVLTree<LicensePlate>, LicensePlate>::performPrint(&AVLTree<LicensePlate>::printPostOrder);
            break;
        case 7:
            App<AVLTree<LicensePlate>, LicensePlate>::performPrint(&AVLTree<LicensePlate>::printReverseInOrder);
            break;
        case 8:
            App<AVLTree<LicensePlate>, LicensePlate>::showMenu();
            break;
        case 9:
            App<AVLTree<LicensePlate>, LicensePlate>::loadDataFromFile("C:/Projects/cpp/avl-tree/input.txt", &AVLTree<LicensePlate>::clear, &AVLTree<LicensePlate>::insert, isValidLicensePlate, parseLicensePlate);
            break;
        case 10:
            App<AVLTree<LicensePlate>, LicensePlate>::saveTreeToFile("C:/Projects/cpp/avl-tree/result/tree.txt", &AVLTree<LicensePlate>::printTree);
            break;
        case 11:
            App<AVLTree<LicensePlate>, LicensePlate>::saveTreeToFile("C:/Projects/cpp/avl-tree/result/in_order.txt", &AVLTree<LicensePlate>::printInOrder);
            App<AVLTree<LicensePlate>, LicensePlate>::saveTreeToFile("C:/Projects/cpp/avl-tree/result/post_order.txt", &AVLTree<LicensePlate>::printPostOrder);
            App<AVLTree<LicensePlate>, LicensePlate>::saveTreeToFile("C:/Projects/cpp/avl-tree/result/pre_order.txt", &AVLTree<LicensePlate>::printPreOrder);
            break;
        default:
            break;
    }
}

int main(const int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No file name provided. Usage: " << argv[0] << " <menu.txt path> <input.txt path>" << std::endl;
        return 1;
    }

    try {
        auto cfg = loadConfigFromFile(argv[1]);
        constexpr AVLTree<LicensePlate> tree;
        App<AVLTree<LicensePlate>, LicensePlate>(
            cfg["Menu"],
            cfg["Get input"],
            cfg["Wrong input"],
            tree,
            menu,
            std::stoi(cfg["Max action"]),
            std::stoi(cfg["Min action"])).start();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
