//
// Created by sphdx on 01.12.24.
//

#ifndef SLLIST_H
#define SLLIST_H

#include <iostream>

// Данный модуль определяет односвязный кольцевой список

template <typename T>
class SLList {
public:
    class Node {
    public:
        explicit Node(T data, Node* pNext = nullptr) {
            this->pNext = pNext;
            this->data = data;
        }
        Node* pNext = nullptr;
        T data = T();
    };

    SLList();
    ~SLList();

    void del(T data);
    void del_after(T data);
    void add(T data);
    void push_back(T data);
    Node* search(T data);
    void print();
    void print_with_id();
    SLList* copy();
    int count(T data);
    int count();
    T get_first();

    Node* head = nullptr;
};


template<typename T>
SLList<T>::SLList() = default;

template<typename T>
SLList<T>::~SLList() {
    if (this->head == nullptr) {
        return;
    }

    Node *current = this->head;
    Node *next;

    do {
        next = current->pNext;
        delete current;
        current = next;
    } while (current != this->head);
}

template<typename T>
void SLList<T>::del(T data) {
    if (this->head == nullptr) {
        return;
    }

    Node *current = this->head;
    Node *prev = nullptr;

    do {
        if (current->data == data) {
            if (prev == nullptr) {
                if (current->pNext == this->head) {
                    delete current;
                    this->head = nullptr;
                    return;
                } else {
                    Node *last = this->head;
                    while (last->pNext != this->head) {
                        last = last->pNext;
                    }
                    this->head = current->pNext;
                    last->pNext = this->head;
                    delete current;
                    current = this->head;
                    continue;
                }
            } else {
                prev->pNext = current->pNext;
                delete current;
                current = prev->pNext;
                continue;
            }
        }
        prev = current;
        current = current->pNext;
    } while (current != this->head);
}

template<typename T>
void SLList<T>::del_after(T data) {
    if (this->head == nullptr) {
        return;
    }

    Node *current = this->head;

    do {
        if (current->data == data) {
            if (current->pNext == this->head) {
                return;
            }

            Node *toDelete = current->pNext;
            current->pNext = toDelete->pNext;

            if (toDelete == this->head) {
                this->head = toDelete->pNext;
            }

            delete toDelete;
        }

        current = current->pNext;
    } while (current != this->head);
}

template<typename T>
void SLList<T>::add(T data) {
    Node *new_node = new Node(data);

    if (this->head == nullptr) {
        this->head = new_node;
        this->head->pNext = this->head;
        return;
    }

    Node *current = this->head;
    Node *prev = nullptr;

    do {
        if (current->data > data) {
            if (prev == nullptr) {
                Node *last = this->head;
                while (last->pNext != this->head) {
                    last = last->pNext;
                }
                new_node->pNext = this->head;
                this->head = new_node;
                last->pNext = this->head;
                return;
            } else {
                new_node->pNext = current;
                prev->pNext = new_node;
                return;
            }
        }
        prev = current;
        current = current->pNext;
    } while (current != this->head);

    prev->pNext = new_node;
    new_node->pNext = this->head;
}

template<typename T>
void SLList<T>::push_back(T data) {
    Node *new_node = new Node(data, nullptr);

    if (this->head == nullptr) {
        this->head = new_node;
        new_node->pNext = this->head;
        return;
    }

    Node *current = this->head;

    while (current->pNext != this->head) {
        current = current->pNext;
    }

    current->pNext = new_node;
    new_node->pNext = this->head;
}

template<typename T>
typename SLList<T>::Node *SLList<T>::search(T data) {
    if (this->head == nullptr) {
        return nullptr;
    }

    Node *current = this->head;

    do {
        if (current->data == data) {
            return current;
        }
        current = current->pNext;
    } while (current != this->head);

    return nullptr;
}

template<typename T>
void SLList<T>::print() {
    if (this->head == nullptr) {
        std::cout << "[ ]" << '\n';
        return;
    }

    Node *current = this->head;

    std::cout << "[";

    do {
        std::cout << " " << current->data;
        current = current->pNext;
    } while (current != this->head);

    std::cout << " ]" << '\n';
}

template<typename T>
void SLList<T>::print_with_id() {
    if (this->head == nullptr) {
        std::cout << "[ ]" << '\n';
        return;
    }

    Node* current = this->head;

    std::cout << "[";

    do {
        std::cout << " " << current->data << '[' << current->id << ']';
        current = current->pNext;
    } while (current != this->head);

    std::cout << " ]" << '\n';
}

template<typename T>
SLList<T> *SLList<T>::copy() {
    if (this->head == nullptr) {
        return nullptr;
    }

    bool is_have_zero = false;

    SLList<T> *new_list = new SLList<T>();

    SLList<T>::Node *current = this->head;

    do {
        if (current->data == T()) {
            is_have_zero = true;
        }
        new_list->push_back(current->data);
        current = current->pNext;
    } while (current != this->head);

    if (!is_have_zero) {
        new_list->del(T());
    }

    return new_list;
}

template<typename T>
int SLList<T>::count(T data) {
    if (this->head == nullptr) {
        return 0;
    }

    int counter = 0;
    SLList<T>::Node *current = this->head;

    do {
        if (current->data == data) {
            counter++;
        }
        current = current->pNext;
    } while (current != this->head);

    return counter;
}

template<typename T>
int SLList<T>::count() {
    if (this->head == nullptr) {
        return 0;
    }

    int counter = 0;
    SLList<T>::Node* current = this->head;

    do {
        counter++;
        current = current->pNext;
    } while (current != this->head);

    return counter;
}

template<typename T>
T SLList<T>::get_first() {
    return this->head->data;
}

#endif //SLLIST_H


