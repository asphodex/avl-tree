//
// Created by sphdx on 23.12.2024.
//

#include "include/menu.h"
#include <iostream>
#include "include/app.h"
#include "include/avl_tree.h"
#include "include/license_plate.h"
#include "include/path.h"

void testIsEqual() {
    AVLTree<license_plate> firstTree, secondTree;
    firstTree.insert({'A', 123, 'A', 'A'}, 1);
    firstTree.insert({'B', 123, 'A', 'A'}, 1);
    firstTree.insert({'C', 123, 'A', 'A'}, 1);
    firstTree.insert({'D', 123, 'A', 'A'}, 1);

    secondTree.insert({'D', 123, 'A', 'A'}, 2);
    secondTree.insert({'A', 123, 'A', 'A'}, 1);
    secondTree.insert({'B', 123, 'A', 'A'}, 1);
    secondTree.insert({'C', 123, 'A', 'A'}, 1);

    if (firstTree == secondTree) {
        std::cout << "equal" << std::endl;
    } else {
        std::cout << "not equal" << std::endl;
    }
}

int counter = 0;

void menu(const int& action, std::string& key, int& id) {
    switch (action) {
        case 1:
        again_1:
            app<AVLTree<license_plate>, license_plate>::showGetInputText();
            std::cin >> key;

            if (isValidLicensePlate(key)) {
                const license_plate lp = parseLicensePlate(key);
                ++counter;
                app<AVLTree<license_plate>, license_plate>::performAction(&AVLTree<license_plate>::insert, lp, counter);
            } else {
                app<AVLTree<license_plate>, license_plate>::showWrongInputText();
                goto again_1;
            }
            break;
        case 2:
            again_2:
            app<AVLTree<license_plate>, license_plate>::showGetInputText();
            std::cin >> key >> id;

            if (isValidLicensePlate(key)) {
                const license_plate lp = parseLicensePlate(key);
                app<AVLTree<license_plate>, license_plate>::performAction(&AVLTree<license_plate>::del, lp, id);
            } else {
                app<AVLTree<license_plate>, license_plate>::showWrongInputText();
                goto again_2;
            }
            break;
        case 3:
            app<AVLTree<license_plate>, license_plate>::performPrint(&AVLTree<license_plate>::printTree);
            break;
        case 4:
            app<AVLTree<license_plate>, license_plate>::performPrint(&AVLTree<license_plate>::printInOrder);
            break;
        case 5:
            app<AVLTree<license_plate>, license_plate>::performPrint(&AVLTree<license_plate>::printPreOrder);
            break;
        case 6:
            app<AVLTree<license_plate>, license_plate>::performPrint(&AVLTree<license_plate>::printPostOrder);
            break;
        case 7:
            app<AVLTree<license_plate>, license_plate>::performPrint(&AVLTree<license_plate>::printReverseInOrder);
            break;
        case 8:
            app<AVLTree<license_plate>, license_plate>::showMenu();
            break;
        case 9:
            app<AVLTree<license_plate>, license_plate>::loadDataFromFile(getSomeFilePath("resources/input.txt"), &AVLTree<license_plate>::clear, &AVLTree<license_plate>::insert, isValidLicensePlate, parseLicensePlate);
            break;
        case 10:
            app<AVLTree<license_plate>, license_plate>::saveTreeToFile(getSomeFilePath( "output/tree.txt"), &AVLTree<license_plate>::printTree);
            break;
        case 11:
            app<AVLTree<license_plate>, license_plate>::saveTreeToFile(getSomeFilePath("output/in_order.txt"), &AVLTree<license_plate>::printInOrder);
            app<AVLTree<license_plate>, license_plate>::saveTreeToFile(getSomeFilePath("output/post_order.txt"), &AVLTree<license_plate>::printPostOrder);
            app<AVLTree<license_plate>, license_plate>::saveTreeToFile(getSomeFilePath("output/pre_order.txt"), &AVLTree<license_plate>::printPreOrder);
            break;
        case 12:
            counter = 0;
            app<AVLTree<license_plate>, license_plate>::performAction(&AVLTree<license_plate>::clear);
            break;
        case 13:
        again_3:
            app<AVLTree<license_plate>, license_plate>::showGetInputText();
            std::cin >> key >> id;

            if (isValidLicensePlate(key)) {
                const license_plate lp = parseLicensePlate(key);
                app<AVLTree<license_plate>, license_plate>::performAction(&AVLTree<license_plate>::search, lp, id);
            } else {
                app<AVLTree<license_plate>, license_plate>::showWrongInputText();
                goto again_3;
            }
            break;
        case 14:
            testIsEqual();
            break;
        default:
            break;
    }
}
