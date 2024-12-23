//
// Created by sphdx on 22.12.2024.
//

#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <vector>
#include <cmath>
#include "SLList.h"

template <typename T>
class AVLTree {
    struct Node {
        T key;
        mutable int height;
        Node *left;
        Node *right;
        SLList<int> list;

        explicit Node(const T key) {
            this->key = key;
            left = right = nullptr;
            height = 1;
        }
    };

    Node *root = nullptr;
    int nodesCount = 0;

    static int getHeight(const Node *node);
    static int balanceFactor(const Node *node);
    static void updateHeight(const Node *node);
    static Node* rightRotate(Node *node);
    static Node* leftRotate(Node *node);
    static Node* balance(Node *node);
    Node* insert(Node *node, T key, int id);
    static Node* findMinNode(Node *node);
    static Node* deleteMinNode(Node *node);
    static Node* deleteNode(Node *node, T key, int id);
    static void getTreeInOrder(const Node *node, int row, int col, int height, std::vector<std::vector<T>> &ans);
    static std::vector<std::vector<T>> treeToMatrix(Node *node);
    static void printTree(Node *node);
    static void printPreOrder(Node *node);
    static void printInOrder(Node *node);
    static void printPostOrder(Node *node);
    static void printReverseInOrder(Node *node);
    void clearTree(Node *node);
    Node * searchNode(Node *node, T key, int id);
    void inorderToArray(Node* node, T* keyArr, SLList<int>* listArr, int& index, int arrLength) const;

public:
    void printTree() const;
    void insert(T key, int id);
    void del(T key, int id);
    void printPreOrder() const;
    void printInOrder() const;
    void printPostOrder() const;
    void printReverseInOrder() const;
    void clear();
    void search(T key, int id);
    int getNodesCount() const;
    bool operator==(const AVLTree<T> &other) const;
};

template <typename T>
int AVLTree<T>::getHeight(const Node *node) {
    return node ? node->height : 0;
}

template <typename T>
 int AVLTree<T>::balanceFactor(const Node *node) {
    return getHeight(node->right) - getHeight(node->left);
}

template <typename T>
 void AVLTree<T>::updateHeight(const Node *node) {
    const int hl = getHeight(node->left);
    const int hr = getHeight(node->right);

    node->height = (hl > hr ? hl : hr) + 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Правое вращение используется когда разница высот R поддерева и b-поддерева равна 2
// и высота C <= высота L
//
//       a              b
//    b     R   ->   L     a
//  L   C                C   R
//
// Алгоритм:
// Сохраняем указатель на элемент b. Вместо левого потомка у a помещаем указатель на
// правого потомка b.
//
//       a              a
//    b     R   ->   C     R
//
// В качестве правого потомка элемента b ставим указатель на элемент a
//
//       b
//    L     a
//        C   R
//
// Далее обновляем высоты для поддеревьев а и b
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rightRotate(Node *node) {
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;

    updateHeight(node);
    updateHeight(temp);

    return temp;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Левое вращение используется когда разница высот L поддерева и b-поддерева равна 2
// и высота C <= высота R
//
//       a              b
//    L     b   ->   a     R
//        C   R    L   C
//
// Алгоритм:
// Сохраняем указатель на элемент b. Вместо правого потомка у a помещаем указатель на
// левого потомка b.
//
//       a              a
//    L     b   ->   L     C
//
// В качестве левого потомка элемента b ставим указатель на элемент a
//
//       b
//    a     R
//  L   C
//
// Далее обновляем высоты для поддеревьев а и b
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
typename AVLTree<T>::Node * AVLTree<T>::leftRotate(Node *node) {
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;

    updateHeight(node);
    updateHeight(temp);

    return temp;
}

// Метод balance осуществляет левый-правый или правый-левый (большое левое, большое правое) повороты.
template <typename T>
typename AVLTree<T>::Node * AVLTree<T>::balance(Node *node) {
    updateHeight(node);

    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->right) < 0) {
            node->right = rightRotate(node->right);
        }
        return leftRotate(node);
    }
    if (balanceFactor(node)== -2){
        if (balanceFactor(node->left) > 0) {
            node->left = leftRotate(node->left);
        }
        return rightRotate(node);
    }

    return node; // балансировка не нужна
}

template <typename T>
typename AVLTree<T>::Node * AVLTree<T>::insert(Node *node, const T key, int id) {
    if( !node ) { auto newNode = new Node(key); newNode->list.push_back(id); nodesCount += 1; return newNode; }

    /////////////////
    if (key == node->key) {
        node->list.push_back(id);
    }
    /////////////////


    if(key < node->key) {
        node->left = insert(node->left,key, id);
    }
    else if(key > node->key) {
        node->right = insert(node->right,key, id);
    }

    return balance(node);
}

// findMinNode осуществляет поиск минимального узла относительно дерева, для которого переданный узел
// является корнем
template <typename T>
typename AVLTree<T>::Node * AVLTree<T>::findMinNode(Node *node) {
    return node->left ? findMinNode(node->left) : node;
}

template <typename T>
typename AVLTree<T>::Node * AVLTree<T>::deleteMinNode(Node *node) {
    if (node->left == nullptr) {
        return node->right;
    }

    node->left = deleteMinNode(node->left);

    return balance(node);
}

template <typename T>
typename AVLTree<T>::Node * AVLTree<T>::deleteNode(Node *node, T key, int id) {
    if (!node) return nullptr;

    if (key < node->key)
        node->left = deleteNode(node->left,key,id);
    else if (key > node->key)
        node->right = deleteNode(node->right,key,id);
    else {
        if (node->list.search(id) != nullptr) {
            node->list.del(id);
        }

        if (node->list.count() == 0) {
            Node* leftNode = node->left;
            Node* rightNode = node->right;
            delete node;

            if (!rightNode) return leftNode;

            Node* min = findMinNode(rightNode);
            min->right = deleteMinNode(rightNode);
            min->left = leftNode;

            return balance(min);
        }
    }

    return balance(node);
}
template <typename T>
void AVLTree<T>::getTreeInOrder(const Node *node, const int row, const int col, const int height, std::vector<std::vector<T>> &ans) {
    if (!node) { return; }

    const int offset = pow(2, height - row - 1);

    if (node->left) {
        getTreeInOrder(node->left, row + 1, col - offset, height, ans);
    }

    ans[row][col] = (node->key);

    if (node->right) {
        getTreeInOrder(node->right, row + 1, col + offset, height, ans);
    }
}

template <typename T>
std::vector<std::vector<T>> AVLTree<T>::treeToMatrix(Node *node) {
    const int height = getHeight(node);

    const int rows = height + 1;
    const int cols = pow(2, height + 1) - 1;

    std::vector ans(rows, std::vector<T>(cols));

    getTreeInOrder(node, 0, (cols - 1) / 2, height, ans);

    return ans;
}

template <typename T>
void AVLTree<T>::printTree(Node *node) {
    for (auto result = treeToMatrix(node); auto &row : result) {
        for (const auto &cell: row) {
            if (cell == T()) {
                std::cout << "    ";
            } else {
                std::cout << cell;
            }
        }
        std::cout << std::endl;
    }
}

template<typename T>
void AVLTree<T>::printPreOrder(Node *node) {
    if (node == nullptr) return;

    std::cout << node->key;
    node->list.print();

    printPreOrder(node->left == nullptr ? nullptr : node->left);
    printPreOrder(node->right == nullptr ? nullptr : node->right);
}

template<typename T>
void AVLTree<T>::printInOrder(Node *node) {
    if (node == nullptr) return;

    printInOrder(node->left == nullptr ? nullptr : node->left);

    std::cout << node->key;
    node->list.print();

    printInOrder(node->right == nullptr ? nullptr : node->right);
}

template<typename T>
void AVLTree<T>::printPostOrder(Node *node) {
    if (node == nullptr) return;

    printPostOrder(node->left == nullptr ? nullptr : node->left);
    printPostOrder(node->right == nullptr ? nullptr : node->right);

    std::cout << node->key;
    node->list.print();
}

template<typename T>
void AVLTree<T>::printReverseInOrder(Node *node) {
    if (node == nullptr) return;

    printReverseInOrder(node->right == nullptr ? nullptr : node->right);

    std::cout << node->key;
    node->list.print();

    printReverseInOrder(node->left == nullptr ? nullptr : node->left);
}

template<typename T>
void AVLTree<T>::clearTree(Node *node) {
    if (node == nullptr) return;
    clearTree(node->left == nullptr ? nullptr : node->left);
    clearTree(node->right == nullptr ? nullptr : node->right);
    delete node;
}

template <typename T>
AVLTree<T>::Node * AVLTree<T>::searchNode(Node *node, T key, int id) {
    if (node == nullptr || (node->key == key && node->list.count(id) > 0)) return node;
    if (key < node->key)
        return searchNode(node->left, key, id);
    return searchNode(node->right, key, id);
}

// printTree печатает дерево полностью, игнорируя нулевые значения переданного типа
template <typename T>
void AVLTree<T>::printTree() const {
    printTree(this->root);
}

template <typename T>
void AVLTree<T>::insert(const T key, const int id) {
    this->root = insert(this->root, key, id);
}

template <typename T>
void AVLTree<T>::del(const T key, const int id) {
    this->root = deleteNode(this->root, key, id);
}

// printPreOrder осуществляет прямой обход дерева
template<typename T>
void AVLTree<T>::printPreOrder() const {
    printPreOrder(this->root);
}

// printInOrder осуществляет центрированный обход дерева
// такой обход выводит элементы в отсортированном порядке
template<typename T>
void AVLTree<T>::printInOrder() const {
    printInOrder(this->root);
}

// printPostOrder осуществляет обратный обход дерева
template<typename T>
void AVLTree<T>::printPostOrder() const {
    printPostOrder(this->root);
}

// printReverseInOrder осуществляет центрированный обход дерева в обратном порядке
template<typename T>
void AVLTree<T>::printReverseInOrder() const {
    printReverseInOrder(this->root);
}

template<typename T>
void AVLTree<T>::clear() {
    if (this->root == nullptr) { return; }
    clearTree(this->root->left);
    clearTree(this->root->right);
    delete this->root;
    this->root = nullptr;
}

template<typename T>
void AVLTree<T>::search(T key, const int id){
    auto node = searchNode(this->root, key, id);
    if (node == nullptr) return;
    std::cout << node->key;
    node->list.print();
}

template<typename T>
int AVLTree<T>::getNodesCount() const {
    return nodesCount;
}

template<typename T>
void AVLTree<T>::inorderToArray(Node* node, T* keyArr, SLList<int>* listArr, int& index, const int arrLength) const  {
    if (node == nullptr || index >= arrLength) {
        return;
    }

    inorderToArray(node->left, keyArr, listArr, index, arrLength);

    if (index < arrLength) {
        keyArr[index] = node->key;
        listArr[index] = node->list;
        index++;
    }

    inorderToArray(node->right, keyArr, listArr, index, arrLength);
}

template<typename T>
bool AVLTree<T>::operator==(const AVLTree &other) const {
    const int size1 = this->getNodesCount();
    const int size2 = other.getNodesCount();

    if (size1 != size2) {
        return false;
    }

    T* keyArr1 = new T[size1];
    auto* listArr1 = new SLList<int>[size1];
    T* keyArr2 = new T[size2];
    auto* listArr2 = new SLList<int>[size2];

    int index1 = 0, index2 = 0;

    inorderToArray(this->root, keyArr1, listArr1, index1, size1);

    inorderToArray(other.root, keyArr2, listArr2, index2, size2);

    for (int i = 0; i < size1; ++i) {
        if (keyArr1[i] != keyArr2[i] || listArr1[i] != listArr2[i]) {
            delete[] keyArr1;
            delete[] listArr1;
            delete[] keyArr2;
            delete[] listArr2;
            return false;
        }
    }

    delete[] keyArr1;
    delete[] listArr1;
    delete[] keyArr2;
    delete[] listArr2;

    return true;
}


#endif //AVL_H