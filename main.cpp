#include <iostream>
#include "array.cpp"
#include "linked_list.cpp"




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
    The 1st index I need to delete is still 2, but the subsequent indexes will be shifted by the number of deleted elements.
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