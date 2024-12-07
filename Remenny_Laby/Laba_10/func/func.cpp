#include <func.hpp>
#include <iostream>

namespace mt
{
    void Make(Node*& head)
    {
        head = new Node {0, nullptr}; // фиктивный элемент, показывает на nullptr 
    }

    void Pushback(Node* head, int value)
    {
        Node* p = head; // head-> == (*head).
        while(p->next != nullptr)
            p = p->next;
        
        Node* q = new Node;
        q->data = value;
        q->next = nullptr;
        p->next = q;
    }

    void Print(Node* head) // проходим по всем элементам и печатаем data
    {
        Node* p = head->next;
        while(p != nullptr)
        {
            std::cout << p->data << " ";
            p = p->next;
        }
    }

    void Remove(Node* head, int index)
    {
        Node* p = head;
        int i = 0;
        while(p->next != nullptr && i != index)
        {
            i++;
            p = p->next;
        }

        if(p->next == nullptr)
            return;

        Node* tmp = p->next;
        p->next = p->next->next;
        delete tmp;
    }

    void Clear(Node* head)
    {
        Node* p = head;
        while(p->next != nullptr)
        {
            Node* tmp = p;
            p = p->next;
            delete tmp;
        }
    }

    bool IsPalindrome(Node* head)
    {
        Node* current = head->next; // Начинаем с первого реального узла
        while (current != nullptr) {
            int num = current->data;
            int tmp = num; // Объявляем временную переменную со значением исходного числа
            int reversed = 0; // Перевернутое число

            // Переворачиваем число
            while (tmp != 0) {
                reversed = reversed * 10 + tmp % 10; // Переворачиваем число по цифрам
                tmp /= 10; // Отбрасываем последнюю цифру
            }

            if (num == reversed) 
            {
                return true;
            }
            current = current->next;
        }
        return false; 
    }

    bool isPrime(int value) 
    {
        if (value < 2) return false; // Числа меньше 2 не являются простыми
        for (int d = 2; d * d <= value; ++d) 
        {
            if (value % d == 0) 
                return false; // Если число делится на d, оно не простое
        }
        return true; // Число простое
    }

    bool hasPrime(Node* head) 
    {
        Node* current = head->next; // Начинаем с первого реального узла
        while (current != nullptr) 
        {
            if (isPrime(current->data))
                return true;
            current = current->next; // Переходим к следующему узлу
        }      
        return false; 
    }
}