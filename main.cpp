#include <iostream>
#include <string>
#include <map>

#include "src/include/app.h"
#include "src/include/avl_tree.h"
#include "src/include/license_plate.h"
#include "src/include/menu.h"
#include "src/include/config.h"
#include "src/include/path.h"

int main() {
    try {
        auto cfg = loadConfigFromFile(getSomeFilePath("resources/config.txt"));
        constexpr AVLTree<license_plate> tree;
        app<AVLTree<license_plate>, license_plate>(
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
}
