#include <iostream>
int main()
{
    // Номер 1

    unsigned int a,b,c;
    std::cout<< "Введите три натуральных числа: ";
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
   
    if (a % c == 0 && b % c == 0)
    {
        std::cout << (a+b)/c << std::endl;
    }
    
    else if (a % c == 0 && b % c != 0)
    {
        std::cout << a/c +b << std::endl;
    }

    else
    {
        std::cout << int(a-b-c) << std::endl;
    }

    // Номер 2

    unsigned int n;
   
    std::cout << "Введите номер дня недели: "; std::cin >> n;

    while (n > 7 || n < 1)
    {
        std::cout << "Число должно быть от 1 до 7, попробуйте повторный ввод: "; std::cin >> n; 
    }

    switch(n)
    {
        case 1:
            std::cout << "Понедельник\n";
            break;
        case 2:
            std::cout << "Вторник\n";
            break;
        case 3:
            std::cout << "Среда\n";
            break;
        case 4:
            std::cout << "Четверг\n";
            break;
        case 5:
            std::cout << "Пятница\n";
            break;
        case 6:
            std::cout << "Суббота\n";
            break;
        case 7:
            std::cout << "Воскресенье\n";
            break;                             
    }

    // Номер 3 

    int x;

    std::cout << "Введите x: "; std::cin >> x;

    if (x == 1)
    {
        std::cout << "Positive number";
    }

    else if (x == -1)
    {
        std::cout << "Negative number";
    }

    else
    {
        std::cout << "Error ";
    }
}
