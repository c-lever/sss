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
        if (index < 0) {
            std::cout << "Invalid index" << std::endl;
            return;
        } else if (index > size_) {
            std::cout << "Index out of range" << std::endl;
            return;
        }

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
        if (index < 0) {
            std::cout << "Invalid index" << std::endl;
            return;
        } else if (index > size_) {
            std::cout << "Index out of range" << std::endl;
            return;
        }

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
            std::cout << "Index out of range" << std::endl;
        } else {
            return data_[index];
        }
    }

private:
    T *data_;
    size_t size_;
};