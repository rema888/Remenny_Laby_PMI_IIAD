#include <iostream>
#include <func.hpp>

int main()
{
    Node* sent = new Node; // фиктивный элемент sent  
    sent->next = sent; // стрелка вперед направленная в sent 
    sent->prev = sent; // стрелка назад направленная в sent 

    int x, n;
    std::cout << "Введите длину списка: "; std::cin >> n;
    std::cout << "Введите последовательность натуральных чисел: " << std::endl;

    for (int i = 0; i < n; i++)
    {
        std::cin >> x;
        AddBack(sent, x); // Добавляем число в двусвязный список
    }

    bool hasThreeDigitNumber = false;

    for (Node* p = sent->next; p != sent; p = p->next) 
    {
        if (dif_digits_three(p->data)) 
        {
            hasThreeDigitNumber = true;
            break;
        }
    }

    if (hasThreeDigitNumber) 
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