#ifndef DoubleLinkedList_H
#define DoubleLinkedList_H

#include <iostream>

using namespace std;

template <class T> // Hace la clase generica, puede utilizar cualquier tipo de dato para instanciar esta clase.
class Node
{
public:
    T data; // T : tipo de dato que solicito.
    Node<T> *prev;
    Node<T> *next;

    Node(T value) : data(value), prev(nullptr), next(nullptr) {} // Es lo mismo que vimos en clases.
};

template <class T>
class DoubleLinkedList
{
public:
    int size;                                                     // Tamaño de la doble lista enlazada
    DoubleLinkedList() : size(0), head(nullptr), tail(nullptr){}; // Inicializacion de size, head, tail.
    ~DoubleLinkedList()
    {
        clear(); // Libera memoria
    };

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
    void pushBack(T value) // Lo mismo anterior para la cola.
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
    bool popFront() // Extraccion de dato de frente.
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

    bool popBack() // Extraccion de dato de atras.
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
    T get(int index) // Devuelve el dato que esta en el indice indicado.
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

    void set(int index, T value) // Modifica el dato que esta en el indice indicado.
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
    bool isEmpty()
    {
        return head == nullptr;
    };
    void clear()
    {
        while (!isEmpty())
        {
            popFront();
        }
    };
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