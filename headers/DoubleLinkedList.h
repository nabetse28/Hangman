#ifndef DoubleLinkedList_H
#define DoubleLinkedList_H

#include <iostream>

using namespace std;

template <class T> // // Makes the class generic, you can use any data type to instantiate this class.
class Node
{
public:
    T data; // T: type of data requested.
    Node<T> *prev;
    Node<T> *next;

    Node(T value) : data(value), prev(nullptr), next(nullptr) {}
};
// Pushes a value to the front of the linked list.
//* @param value the value to be pushed to the front of the list.
//* @throws None
template <class T>
class DoubleLinkedList
{
public:
    int size;                                                     // Size of the double linked list
    DoubleLinkedList() : size(0), head(nullptr), tail(nullptr){}; // Initialization of size, head, tail.
    ~DoubleLinkedList()
    {
        clear(); // Free memory
    };
    // Pushes a value to the front of the linked list.
    //* @param value the value to be pushed to the front of the list.
    //* @throws None
    void pushFront(T value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        this->size++;
    };
    // Adds a new element to the end of the list.
    //  * @param value the value of the element to be added
    //  * @throws None
    void pushBack(T value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        this->size++;
    };
    // Front-end data extraction.
    // return true if the front data could be extracted, false if the list is empty.

    bool popFront()
    {
        if (isEmpty())
        {
            return false;
        }
        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            Node<T> *temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
        this->size--;
        return true;
    };

    //  * @return true if the extraction is successful, false otherwise
    bool popBack() // Back data extraction.
    {
        if (isEmpty())
        {
            return false;
        }
        if (head == tail)
        {
            delete tail;
            head = tail = nullptr;
        }
        else
        {
            Node<T> *temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        this->size--;
        return true;
    };
    //  * Removes the specified value from the linked list.
    //  * param value the value to be removed
    //  * return true if the value was successfully removed, false otherwise
    //  * throws None
    bool remove(T value)
    {
        Node<T> *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                if (current == head)
                {
                    popFront();
                }
                else if (current == tail)
                {
                    popBack();
                }
                else
                {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                }
                this->size--;
                return true;
            }
            current = current->next;
        }
        this->size--;
        return false;
    };
    //* Returns the data that is in the indicated index.
    // * @param index the index of the data to be returned
    // * @return the data that is in the indicated index
    // * @throws None
    T get(int index) // Returns the data that is at the indicated index.
    {
        if (index < 0)
        {
            cout << "Index cannot be negative" << endl;
        }

        Node<T> *current = head;
        int currentIndex = 0;

        while (current != nullptr)
        {
            if (currentIndex == index)
            {
                return current->data;
            }
            current = current->next;
            currentIndex++;
        }

        cout << "Index out of bounds" << endl;
        return T();
    };
    //  * Modifies the data at the specified index.
    //  * @param index the index of the data to be modified
    //  * @param value the new value to be set
    //  * @throws None
    void set(int index, T value) // Modifies the data that is in the indicated index.
    {
        if (index < 0)
        {
            cout << "Index cannot be negative" << endl;
        }

        Node<T> *current = head;
        int currentIndex = 0;

        while (current != nullptr)
        {
            if (currentIndex == index)
            {
                current->data = value;
                return;
            }
            current = current->next;
            currentIndex++;
        }

        cout << "Index out of bounds" << endl;
    };
    //  * Checks if the linked list is empty.
    //  * @return true if the linked list is empty, false otherwise
    bool isEmpty()
    {
        return head == nullptr;
    };
    //  * Clears the container by repeatedly calling the `popFront` function until the container is empty.
    //  * @throws None
    void clear()
    {
        while (!isEmpty())
        {
            popFront();
        }
    };
    //  Prints the elements of the linked list.
    //   @param None
    //   @return None
    //   @throws None
    void print()
    {
        Node<T> *current = head;
        cout << "[";
        while (current->next != nullptr)
        {
            cout << current->data << ",";
            current = current->next;
        }
        cout << current->data << "]" << endl;
    };

private:
    Node<T> *head;
    Node<T> *tail;
};

#endif
