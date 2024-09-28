#include <iostream>
using namespace std;
 
int main()
{
    
    int h, a;

//  Вводим данные

    std::cout << "Введите высоту треугольника: ";
    std::cout << "h = "; std::cin >> h;
    std::cout << "Введите основание треугольника: ";
    std::cout << "a = "; std::cin >> a;

// Если данные неверны по условию

    while (h <= 0 || a <= 0 || a > pow(10,8))
    {
        std::cout << "Высота треугольника должна быть больше 0 и основание меньше 10**8" << std::endl;
        std::cout << "Введите высоту треугольника: ";
        std::cout << "h = "; std::cin >> h;
        std::cout << "Введите основание треугольника: ";
        std::cout << "a = "; std::cin >> a;
    }
    
// Если данные верны по условию 

    std::cout << "Площадь треугольника равна " << (a*h)/2.0f << std::endl;
}