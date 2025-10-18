#ifndef LIST_DOUBLY_LINKED_H
#define LIST_DOUBLY_LINKED_H

#include <memory>
#include <stdexcept>

/**
 * Implementation of a List ADT using a doubly linked list data structure with smart pointers.
 * 
 * Design Notes:
 * - Each Node maintains both a forward pointer (next) and backward pointer (prev)
 * - Uses unique_ptr for next pointers to establish clear ownership semantics
 * - Uses raw pointers for prev pointers since the previous node owns the current node
 * - This approach prevents circular reference issues with smart pointers
 */
template <typename T>
class ListDoublyLinked {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;  // Owns the next node
        Node* prev;                   // Raw pointer to previous node (owned by its predecessor)
        
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    
    std::unique_ptr<Node> head;  // Owns the entire list
    unsigned int size;
    
    // Helper method to retrieve a node at a given position
    Node* GetNode(unsigned int pos) {
        if (pos >= size) {
            return nullptr;
        }
        
        Node* current = head.get();
        for (unsigned int i = 0; i < pos; i++) {
            current = current->next.get();
        }
        return current;
    }

public:
    // Default constructor
    ListDoublyLinked() : head(nullptr), size(0) {}
    
    // Destructor (automatically handled by unique_ptr)
    ~ListDoublyLinked() = default;
    
    // Return the number of items in the list
    unsigned int Size() const {
        return size;
    }
    
    // Return the item at a given position
    const T& Get(unsigned int pos) {
        if (pos >= size) {
            throw std::out_of_range("Position out of bounds");
        }
        return GetNode(pos)->data;
    }
    
    // Find the position of the first occurrence of an item
    int Find(const T& item) {
        Node* current = head.get();
        for (unsigned int i = 0; i < size; i++) {
            if (current->data == item) {
                return i;
            }
            current = current->next.get();
        }
        return -1;
    }
    
    // Remove the item at a given position
    void Remove(unsigned int pos) {
        if (pos >= size) {
            throw std::out_of_range("Position out of bounds");
        }
        
        // Case 1: Removing the first element (head)
        if (pos == 0) {
            head = std::move(head->next);
            if (head) {
                head->prev = nullptr;
            }
        }
        // Case 2: Removing an element that's not the head
        else {
            Node* prevNode = GetNode(pos - 1);
            prevNode->next = std::move(prevNode->next->next);
            if (prevNode->next) {
                prevNode->next->prev = prevNode;
            }
        }
        
        size--;
    }
    
    // Insert an item at a given position
    void Insert(const T& item, unsigned int pos) {
        if (pos > size) {
            throw std::out_of_range("Position out of bounds");
        }
        
        auto newNode = std::make_unique<Node>(item);
        
        // Case 1: Inserting at the head
        if (pos == 0) {
            newNode->next = std::move(head);
            if (newNode->next) {
                newNode->next->prev = newNode.get();
            }
            head = std::move(newNode);
        }
        // Case 2: Inserting at the end or in the middle
        else {
            Node* prevNode = GetNode(pos - 1);
            newNode->next = std::move(prevNode->next);
            if (newNode->next) {
                newNode->next->prev = newNode.get();
            }
            newNode->prev = prevNode;
            prevNode->next = std::move(newNode);
        }
        
        size++;
    }
};

#endif // LIST_DOUBLY_LINKED_H
