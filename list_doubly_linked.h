#ifndef LIST_DOUBLY_LINKED_H
#define LIST_DOUBLY_LINKED_H

#include <memory>
#include <stdexcept> // for std::out_of_range
#include <iostream>  // for debugging or optional print

/**
 * Implementation of a List ADT using a doubly linked list data structure with smart pointers.
 * 
 * Q1.1 – Design:
 * We will maintain both a head and tail pointer for O(1) insertions/removals 
 * at both ends, and a size counter.
 *
 * Q1.2 – Smart Pointer Design:
 * Each node will own its `next` node using `std::unique_ptr`, meaning that 
 * destroying one node will automatically destroy all following nodes. 
 * The `prev` pointer will be a `std::weak_ptr` since it should not own 
 * the previous node (to prevent cyclic ownership and memory leaks).
 */

template <typename T>
class ListDoublyLinked {
private:
    // Node structure for doubly linked list
    struct Node {
        T data;
        std::unique_ptr<Node> next; // owns the next node
        Node* prev;                 // raw pointer to previous node (non-owning)

        Node(const T& item) : data(item), next(nullptr), prev(nullptr) {}
    };

    // Head of list owns the entire chain through unique_ptr
    std::unique_ptr<Node> head;

    // Tail pointer (non-owning) to last node for O(1) access at end
    Node* tail;

    // Number of items in the list
    unsigned int size;

    /**
     * Q1.3 – Helper method: returns pointer to node at position @pos
     * Throws std::out_of_range if position invalid.
     */
    Node* GetNode(unsigned int pos) {
        if (pos >= size) throw std::out_of_range("Position out of range");
        Node* curr = head.get();
        for (unsigned int i = 0; i < pos; ++i) {
            curr = curr->next.get();
        }
        return curr;
    }

public:
    // Q2.1 – Default constructor and destructor
    ListDoublyLinked() : head(nullptr), tail(nullptr), size(0) {}

    ~ListDoublyLinked() = default; // unique_ptr auto-cleans nodes

    // Q2.2 – Return number of items in list
    unsigned int Size() const {
        return size;
    }

    // Q2.3 – Return item at position @pos
    const T& Get(const unsigned int pos) {
        Node* node = GetNode(pos);
        return node->data;
    }

    // Q2.4 – Return position of first occurrence of @item (-1 if not found)
    int Find(const T &item) {
        Node* curr = head.get();
        unsigned int index = 0;
        while (curr) {
            if (curr->data == item) return index;
            curr = curr->next.get();
            ++index;
        }
        return -1;
    }

    // Q2.5 – Remove item at position @pos
    /**
     * Scenarios:
     * 1. Removing head (pos == 0)
     * 2. Removing tail (pos == size - 1)
     * 3. Removing middle node
     */
    void Remove(const unsigned int pos) {
        if (pos >= size) throw std::out_of_range("Invalid remove position");

        // Case 1: Remove head
        if (pos == 0) {
            head = std::move(head->next);
            if (head) head->prev = nullptr;
            else tail = nullptr; // list became empty
        }
        // Case 2 & 3: Remove middle or tail
        else {
            Node* prevNode = GetNode(pos - 1);
            std::unique_ptr<Node> toDelete = std::move(prevNode->next);
            prevNode->next = std::move(toDelete->next);

            if (prevNode->next) { // not deleting tail
                prevNode->next->prev = prevNode;
            } else {
                tail = prevNode; // deleted the tail
            }
        }

        --size;
    }

    // Q2.6 – Insert @item at position @pos
    /**
     * Scenarios:
     * 1. Insert at head (pos == 0)
     * 2. Insert at tail (pos == size)
     * 3. Insert in middle
     */
    void Insert(const T& item, const unsigned int pos) {
        if (pos > size) throw std::out_of_range("Invalid insert position");

        std::unique_ptr<Node> newNode = std::make_unique<Node>(item);

        // Case 1: Insert at head
        if (pos == 0) {
            newNode->next = std::move(head);
            if (newNode->next) newNode->next->prev = newNode.get();
            head = std::move(newNode);
            if (size == 0) tail = head.get(); // list was empty
        }
        // Case 2: Insert at tail
        else if (pos == size) {
            newNode->prev = tail;
            tail->next = std::move(newNode);
            tail = tail->next.get();
        }
        // Case 3: Insert in middle
        else {
            Node* prevNode = GetNode(pos - 1);
            std::unique_ptr<Node> temp = std::move(prevNode->next);
            newNode->next = std::move(temp);
            newNode->prev = prevNode;
            if (newNode->next) newNode->next->prev = newNode.get();
            prevNode->next = std::move(newNode);
        }

        ++size;
    }

    // (Optional) helper for debugging
    void PrintList() const {
        Node* curr = head.get();
        std::cout << "[";
        while (curr) {
            std::cout << curr->data;
            if (curr->next) std::cout << ", ";
            curr = curr->next.get();
        }
        std::cout << "]\n";
    }
};

#endif // LIST_DOUBLY_LINKED_H
