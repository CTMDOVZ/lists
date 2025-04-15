#ifndef DOUBLY_H
#define DOUBLY_H
#include <iostream>
#include <stdexcept>
#include "list.h"

template <typename T>
class DoubleList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node() : next(nullptr), prev(nullptr) {}
        Node(T value) : data(value), next(nullptr), prev(nullptr) {}

        void killSelf() {
            if (next) {
                next->killSelf();
                delete next;
                next = nullptr;
            }
        }
    };

    Node* head;
    Node* tail;
    int nodes;

public:
    DoubleList() : head(nullptr), tail(nullptr), nodes(0) {}

    ~DoubleList() {
        clear();
    }

    T front() override {
        if (is_empty()) throw std::runtime_error("List is empty");
        return head->data;
    }

    T back() override {
        if (is_empty()) throw std::runtime_error("List is empty");
        return tail->data;
    }

    void push_front(T data) override {
        Node* newNode = new Node(data);
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = head;
        nodes++;
    }

    void push_back(T data) override {
        Node* newNode = new Node(data);
        newNode->prev = tail;
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = tail;
        nodes++;
    }

    T pop_front() override {
        if (is_empty()) throw std::runtime_error("List is empty");
        Node* temp = head;
        T data = temp->data;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        nodes--;
        return data;
    }

    T pop_back() override {
        if (is_empty()) throw std::runtime_error("List is empty");
        Node* temp = tail;
        T data = temp->data;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        nodes--;
        return data;
    }

    bool insert(T data, int pos) override {
        if (pos < 0 || pos > nodes) return false;
        if (pos == 0) {
            push_front(data);
            return true;
        }
        if (pos == nodes) {
            push_back(data);
            return true;
        }
        Node* newNode = new Node(data);
        Node* current = head;
        for (int i = 0; i < pos; ++i) current = current->next;
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        nodes++;
        return true;
    }

    bool remove(int pos) override {
        if (pos < 0 || pos >= nodes) return false;
        if (pos == 0) {
            pop_front();
            return true;
        }
        if (pos == nodes - 1) {
            pop_back();
            return true;
        }
        Node* current = head;
        for (int i = 0; i < pos; ++i) current = current->next;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        nodes--;
        return true;
    }

    T& operator[](int pos) override {
        if (pos < 0 || pos >= nodes) throw std::out_of_range("Index out of range");
        Node* current;
        if (pos < nodes / 2) {
            current = head;
            for (int i = 0; i < pos; ++i) current = current->next;
        } else {
            current = tail;
            for (int i = nodes - 1; i > pos; --i) current = current->prev;
        }
        return current->data;
    }

    bool is_empty() override {
        return nodes == 0;
    }

    int size() override {
        return nodes;
    }

    void clear() override {
        while (!is_empty()) pop_front();
    }

    void sort() override {
        if (nodes < 2) return;
        for (Node* i = head; i != nullptr; i = i->next) {
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (i->data > j->data) std::swap(i->data, j->data);
            }
        }
    }

    bool is_sorted() override {
        if (!head || !head->next) return true;
        Node* current = head;
        while (current->next) {
            if (current->data > current->next->data) return false;
            current = current->next;
        }
        return true;
    }

    void reverse() override {
        Node* current = head;
        Node* temp = nullptr;
        while (current) {
            std::swap(current->next, current->prev);
            temp = current;
            current = current->prev;
        }
        std::swap(head, tail);
    }

    std::string name() override {
        return "DoubleList";
    }
};

#endif
