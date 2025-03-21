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

        // Делим i на 10 в каждой итерации, чтобы избавиться от последней цифры
        for (int i = n; i > 0; i /= 10) 
        {
            int digit = i % 10; // Извлекаем последнюю цифру числа 

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


bool all_digits_odd(int n) // нечетные
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

bool all_digits_even(int n) // четные
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
    p->next = sent; // у нового элемента стрелка вправо в sent 
    p->prev = sent->prev; // стрелка слева в последний текущий элемент 
    sent->prev->next = p; // из текущего элемента стрелка вправо в новый элемент
    sent->prev = p; // из сента стрелка влево в новый элемент
}

void Print(Node* sent)
{
    Node* p = sent->next; // элемент после сента
    while (p != sent)
    {
        std::cout << p->data << std::endl;
        p = p->next; // переходим к след элементу
    }
}

void Clear(Node* sent)
{
    Node* p = sent->next;
    while (p != sent)
    {
        Node* tmp = p; // временная переменная tmp, в которую сохраняется указатель на текущий элемент p. т.к. мы собираемся изменить p 
                       // на следующий элемент, и если мы изменим p без сохранения ссылки на текущий элемент, мы потеряем доступ к нему.
        p = p->next;
        delete tmp; // освобождаем память, занятую текущим элементом
    }
}

void DuplicateOdd(Node* sent)
{
    Node* p = sent->next;
    while (p != sent)
    {
        if (all_digits_odd(p->data)) 
        {
            Node* q = new Node; // новая ячейка
            q->data = p->data; // в новую ячейку положим данные элемента p
            q->prev = p;        // стрелка влево из нового элемента в p
            q->next = p->next;  // стрелка вправо в элемент после p
            p->next->prev = q; // Из элемента после p стрелка влево в q
            p->next = q; // стрелка вправо из p в q
            p = p->next; // переходим к новому продублированному элементу
        }
        p = p->next; // переходим к новому элементу, после продублированного
    }
}

void RemoveEven(Node* sent)
{
    Node* p = sent->next;
    while (p != sent)
    {
        if (all_digits_even(p->data))
        {
            Node* tmp = p; // Указатель, которой хранит адрес удаляемой ячейки
            p->prev->next = p->next; // cтрелка из элемента перед p вправо в элемент после p
            p->next->prev = p->prev; // стрелка из элемента после p влево в элемент перед p 
            p = p->prev; // p становится предыдущим элементом 
            delete tmp;
        }
        p = p->next;
    }
}


void Sort(Node* sent)
{
    bool swapped;
    do {
        swapped = false; // Используется для отслеживания, произошло ли хотя бы один обмен в текущем проходе по списку.
        Node* p = sent->next;
        
        while (p->next != sent) 
        {
            if (p->data > p->next->data) 
            {
                int tmp = p->next->data;
                p->next->data = p->data;
                p->data = tmp;
                
                swapped = true; // в текущем проходе произошел обмен
            }
            p = p->next; 
        }
    } while (swapped); // если swapped = true, начинаем новый проход по списку
}