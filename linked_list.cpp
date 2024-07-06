#include <iostream>

template <typename T>
struct Node {
    Node<T>* next; 
    T data;

    Node(const T &value) : data{value}, next{nullptr} {}
};

template <typename T>
class LinkedList {
public:

    explicit LinkedList() : head{nullptr}, size_{0} {}

    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void push_back(const T &value) {
        Node<T> *newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            size_ += 1;
            return;
        }
        Node<T> *current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        size_ += 1;
    }

    void push_front(const T &value) {
        Node<T> *newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        size_ += 1;
    }

    void erase(const size_t &index) {
        if (index < 0) {
            std::cout << "Invalid index" << std::endl;
            return;
        }

        if (index == 0) {
            if (head != nullptr) {
                Node<T> *tmp = head;
                head = head->next;
                delete tmp;
                size_ -= 1;
            }
            return;
        }

        Node<T>* current = head;
        int currentIndex = 0;

        while (current != nullptr && currentIndex < index - 1) {
            current = current->next;
            currentIndex++;
        }

        if (current != nullptr && current->next != nullptr) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            std::cout << "Index out of range." << std::endl;
        }
        size_ -= 1;
    }

    void insert(const T &value, const size_t &index) {
        if (index < 0) {
            std::cout << "Invalid index" << std::endl;
            return;
        }

        if (index == 0) {
            push_front(value);
            return;
        }

        Node<T>* newNode = new Node<T>(value);
        Node<T>* current = head;
        int count = 0;
        while (count < index - 1 && current != nullptr) {
            current = current->next;
            count++;
        }
        if (current == nullptr) {
            std::cout << "Index out of range.\n";
            return;
        }
        newNode->next = current->next;
        current->next = newNode;
        
        size_ += 1;
    }

    void print() {
        Node<T> *current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    size_t size() const { return size_; }

    T &operator[](const size_t index) const {
        if (index >= size_) {
            std::cout << "index out of range" << std::endl;
        } else {
            Node<T> *current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->data;
        }
    }

    

private:
    Node<T> *head;
    size_t size_;
};