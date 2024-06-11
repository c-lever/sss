#include <iostream>


template <typename T>
class Array {
public:
    explicit Array() : data_{nullptr}, size_{0} {}

    void push_back(T value) {
        T *new_data = new T[size_ + 1];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        new_data[size_] = value;
        delete [] data_;
        data_ = new_data;
        size_ += 1;
    }

    void push_front(T value) {
        // Same .push_back() func, but reversed
        T *new_data = new T[size_ + 1];
        for (size_t i = size_; i > 0; --i) {
            new_data[i] = data_[i-1];
        }
        new_data[0] = value;
        delete [] data_;
        data_ = new_data;
        size_ += 1;
    }

    void insert(T value, size_t index) {
        T *new_data = new T[size_ + 1];
        for (size_t i = 0; i < index; ++i) {
            new_data[i] = data_[i];
        }
        new_data[index] = value;
        for (size_t j = index; j < size_; ++j) {
            new_data[j+1] = data_[j];
        }
        delete [] data_;
        data_ = new_data;
        size_ += 1;
    }

    void erase(size_t index) {
        T *new_data = new T[size_ - 1];
        for (size_t i = 0; i < size_; ++i) {
            if (i < index) {
                new_data[i] = data_[i];
            } else {
                new_data[i] = data_[i+1];
            }
        }
        delete [] data_;
        data_ = new_data;
        size_ -= 1;
    }

    void print() const {
        for (size_t i = 0; i < size_; ++i) {
            std::cout << data_[i] << " ";
        }
        std::cout << std::endl;
    }

    size_t size() const { return size_; }

    T &operator[](const size_t index) const {
        if (index >= size_) {
            std::cout << "index out of range" << std::endl;
        } else {
            return data_[index];
        }
    }

private:
    T *data_;
    size_t size_;
};



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
            std::cout << "Index out of bounds.\n";
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






template <typename T>
std::ostream &operator<<(std::ostream &os, const Array<T> &container) {
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &container) {
    return os;
}




int main() {
    // ARRAY
    std::cout << "ARRAY: " << std::endl;

    Array<int> Array_Container;
    
    for (int i = 0; i < 10; ++i) {
        Array_Container.push_back(i);
    }
    
    Array_Container.print();
    std::cout << Array_Container.size() << std::endl;
    /*
    So if I wanna delete the 3rd, 5th, and 7th elements of the list, I have to delete the 2,4,6-i elements.
    However, I cant do it all at once because the .erase() function can only delete one element at a time. 
    Therefore I will need to call this function 3 times, but each time I call it, the list will be reindexed.
    The 1st index I need to delete is still 2, but the subsequent indexes will be shifted by 1.
    As a result, I have to delete one by one 2,3,4-i elements of the list.
    */
    Array_Container.erase(2);
    Array_Container.erase(3);
    Array_Container.erase(4);
    Array_Container.print();
    Array_Container.push_front(10);
    Array_Container.print();
    Array_Container.insert(20, static_cast<size_t>(Array_Container.size() / 2));
    Array_Container.print();
    Array_Container.push_back(30);
    Array_Container.print();

    std::cout << std::endl; 

    //-----------------------------------------------------------------------------------------------------
    // LINKED LIST

    std::cout << "LINKED LIST: " << std::endl;

    LinkedList<int> LinkedList_Container;

    for (int i = 0; i < 10; ++i) {
        LinkedList_Container.push_back(i);
        
    }

    LinkedList_Container.print();
    std::cout << LinkedList_Container.size() << std::endl;
    LinkedList_Container.erase(2);
    LinkedList_Container.erase(3);
    LinkedList_Container.erase(4);
    LinkedList_Container.print();
    LinkedList_Container.push_front(10);
    LinkedList_Container.print();
    LinkedList_Container.insert(20, static_cast<size_t>(LinkedList_Container.size() / 2));
    LinkedList_Container.print();
    LinkedList_Container.push_back(30);
    LinkedList_Container.print();
    
    return 0;
}