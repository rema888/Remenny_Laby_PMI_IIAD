#include <func.hpp>
#include <iostream>

bool dif_digits_three(int n) 
{
    if (abs(n) < 100 || abs(n) > 999)
        return false;
    else
    {
        if (n < 0)
        {
            n = abs(n); 
        }
        // Проходим по всем цифрам числа
        // В начале i равно n, а затем мы делим i на 10 в каждой итерации, чтобы избавиться от последней цифры
        for (int i = n; i > 0; i /= 10) 
        {
            int digit = i % 10; // Извлекаем последнюю цифру числа i (текущую цифру для проверки)

            // Проходим по всем цифрам числа, кроме текущей
            for (int j = i / 10; j > 0; j /= 10) 
            {
                // Сравниваем текущую цифру с каждой из оставшихся цифр
                if (digit == j % 10) 
                {
                    return false; 
                }
            }
        }
        return true; 
    }     
}

bool all_digits_odd(int n) 
{
    n = abs(n);
    
    while (n > 0) 
    {
        int digit = n % 10; // Извлекаем последнюю цифру
        if (digit % 2 == 0) 
            return false;
        n /= 10; // Убираем последнюю цифру
    }
    return true;
}

bool all_digits_even(int n) 
{
    n = abs(n);

    while (n > 0) 
    {
        int digit = n % 10;
        if (digit % 2 != 0)
            return false;
        n /= 10;
    }
    return true;
}

void AddBack(Node* sent, int data)
{
    Node* p = new Node; // новая ячейка 
    p->data = data; // в эту ячейку положим данные
    p->next = sent; // у нового элемента в конце стрелка справа в sent (1 шаг)
    p->prev = sent->prev; // стрелка слева в последний текущий элемент (2 шаг)
    sent->prev->next = p;
    sent->prev = p;
}

void Print(Node* sent)
{
    Node* p = sent->next;
    while (p != sent)
    {
        std::cout << p->data << std::endl;
        p = p->next;
    }
}

void Clear(Node* sent)
{
    Node* p = sent->next;
    while (p != sent)
    {
        Node* tmp = p;
        p = p->next;
        delete tmp;
    }
}

void DuplicateOdd(Node* sent)
{
    Node* p = sent->next;
    while (p != sent)
    {
        if (all_digits_odd(p->data)) 
        {
            Node* q = new Node; // Новый узел 
            q->data = p->data;
            q->prev = p;        // Безопасные стрелки из нового узлп
            q->next = p->next;  //
            p->next->prev = q;
            p->next = q;
            p = p->next;
        }
        p = p->next;
    }
}

void RemoveEven(Node* sent)
{
    Node* p = sent->next;
    while (p != sent)
    {
        if (all_digits_even(p->data))
        {
            Node* tmp = p;
            p->prev->next = p->next;
            p->next->prev = p->prev;
            p = p->prev;
            delete tmp;
        }
        p = p->next;
    }
}


void Sort(Node* sent)
{
    bool swapped;
    do {
        swapped = false;
        Node* p = sent->next;
        
        while (p->next != sent) 
        {
            if (p->data > p->next->data) 
            {
                // Обмен значениями данных
                std::swap(p->data, p->next->data);
                swapped = true;
            }
            p = p->next;
        }
    } while (swapped);
}