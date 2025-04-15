#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include <stdexcept>
#include "list.h"

template <typename T>
class ForwardList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;

        Node() : next(nullptr) {}
        Node(T value) : data(value), next(nullptr) {}

        void killSelf() {
            if (next) {
                next->killSelf();
                delete next;
                next = nullptr;
            }
        }
    };

    Node* head;
    int nodes;

public:
    ForwardList() : head(nullptr), nodes(0) {}

    ~ForwardList() {
        clear();
    }

    T front() override {
        if (is_empty()) throw std::runtime_error("List is empty");
        return head->data;
    }

    T back() override {
        if (is_empty()) throw std::runtime_error("List is empty");
        Node* current = head;
        while (current->next) current = current->next;
        return current->data;
    }

    void push_front(T data) override {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        nodes++;
    }

    void push_back(T data) override {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) current = current->next;
            current->next = newNode;
        }
        nodes++;
    }

    T pop_front() override {
        if (is_empty()) throw std::runtime_error("List is empty");
        Node* temp = head;
        T data = temp->data;
        head = head->next;
        delete temp;
        nodes--;
        return data;
    }

    T pop_back() override {
        if (is_empty()) throw std::runtime_error("List is empty");
        if (nodes == 1) {
            return pop_front();
        }
        Node* current = head;
        while (current->next->next) current = current->next;
        T data = current->next->data;
        delete current->next;
        current->next = nullptr;
        nodes--;
        return data;
    }

    bool insert(T data, int pos) override {
        if (pos < 0 || pos > nodes) return false;
        if (pos == 0) {
            push_front(data);
            return true;
        }
        Node* newNode = new Node(data);
        Node* current = head;
        for (int i = 0; i < pos - 1; ++i)
            current = current->next;
        newNode->next = current->next;
        current->next = newNode;
        nodes++;
        return true;
    }

    bool remove(int pos) override {
        if (pos < 0 || pos >= nodes) return false;
        if (pos == 0) {
            pop_front();
            return true;
        }
        Node* current = head;
        for (int i = 0; i < pos - 1; ++i)
            current = current->next;
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        nodes--;
        return true;
    }

    T& operator[](int pos) override {
        if (pos < 0 || pos >= nodes) throw std::out_of_range("Index out of range");
        Node* current = head;
        for (int i = 0; i < pos; ++i)
            current = current->next;
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
        Node* prev = nullptr;
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        head = prev;
    }

    std::string name() override {
        return "ForwardList";
    }
};

#endif
