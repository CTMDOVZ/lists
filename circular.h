#ifndef CIRCULAR_H
#define CIRCULAR_H
#include <iostream>
#include <stdexcept>
#include "list.h"

template <typename T>
class CircularList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node() : next(nullptr), prev(nullptr) {}
        Node(T value) : data(value), next(nullptr), prev(nullptr) {}

        void killSelf() {
            if (next && next != this)
                next->killSelf();
            delete this;
        }
    };

    Node* head; // sentinel
    int nodes;

public:
    CircularList() : nodes(0) {
        head = new Node(); // nodo centinela
        head->next = head;
        head->prev = head;
    }

    ~CircularList() {
        clear();
        delete head;
    }

    T front() override {
        if (is_empty()) throw std::runtime_error("List is empty");
        return head->next->data;
    }

    T back() override {
        if (is_empty()) throw std::runtime_error("List is empty");
        return head->prev->data;
    }

    void push_front(T data) override {
        Node* newNode = new Node(data);
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
        nodes++;
    }

    void push_back(T data) override {
        Node* newNode = new Node(data);
        newNode->prev = head->prev;
        newNode->next = head;
        head->prev->next = newNode;
        head->prev = newNode;
        nodes++;
    }

    T pop_front() override {
        if (is_empty()) throw std::runtime_error("List is empty");
        Node* temp = head->next;
        T data = temp->data;
        head->next = temp->next;
        temp->next->prev = head;
        delete temp;
        nodes--;
        return data;
    }

    T pop_back() override {
        if (is_empty()) throw std::runtime_error("List is empty");
        Node* temp = head->prev;
        T data = temp->data;
        head->prev = temp->prev;
        temp->prev->next = head;
        delete temp;
        nodes--;
        return data;
    }

    bool insert(T data, int pos) override {
        if (pos < 0 || pos > nodes) return false;
        Node* current = head->next;
        for (int i = 0; i < pos; ++i)
            current = current->next;
        Node* newNode = new Node(data);
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        nodes++;
        return true;
    }

    bool remove(int pos) override {
        if (pos < 0 || pos >= nodes) return false;
        Node* current = head->next;
        for (int i = 0; i < pos; ++i)
            current = current->next;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        nodes--;
        return true;
    }

    T& operator[](int pos) override {
        if (pos < 0 || pos >= nodes) throw std::out_of_range("Index out of range");
        Node* current = head->next;
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
        Node* i = head->next;
        while (i != head) {
            Node* j = i->next;
            while (j != head) {
                if (i->data > j->data)
                    std::swap(i->data, j->data);
                j = j->next;
            }
            i = i->next;
        }
    }

    bool is_sorted() override {
        if (nodes < 2) return true;
        Node* current = head->next;
        while (current->next != head) {
            if (current->data > current->next->data)
                return false;
            current = current->next;
        }
        return true;
    }

    void reverse() override {
        Node* current = head;
        do {
            std::swap(current->next, current->prev);
            current = current->prev;  // antes next, ahora prev
        } while (current != head);
    }

    std::string name() override {
        return "CircularList";
    }
};

#endif
