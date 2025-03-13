#include <iostream>
#include <func.hpp>

int main()
{
    Node* sent = new Node; // фиктивный элемент sent  
    sent->next = sent; // стрелка вправо направленная в sent 
    sent->prev = sent; // стрелка влево направленная в sent 

    int x, n;
    std::cout << "Введите длину списка: "; std::cin >> n;
    std::cout << "Введите последовательность натуральных чисел: " << std::endl;

    for (int i = 0; i < n; i++)
    {
        std::cin >> x;
        AddBack(sent, x); // Добавляем число в двусвязный список
    }

    bool Three_Digit = false;

    for (Node* p = sent->next; p != sent; p = p->next) 
    {
        if (dif_digits_three(p->data)) 
        {
            Three_Digit = true;
            break;
        }
    }

    if (Three_Digit) 
    {
        RemoveEven(sent);
        DuplicateOdd(sent);
    } 
    else 
    {
        Sort(sent);
    }

    Print(sent);
    Clear(sent);
}