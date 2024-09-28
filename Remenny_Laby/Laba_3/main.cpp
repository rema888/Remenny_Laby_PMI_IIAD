#include <iostream>

int main()
{
    unsigned long int x;
    int n;

    std::cout << "Введите число x и номер бита n: "; 
    std::cin >> x;
    std::cin >> n;

    // Записать единицу x |= (1 << n);

    // Записать ноль
    x &= ~(1 << n);

    std::cout << x;


}