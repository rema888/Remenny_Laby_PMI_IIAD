#include <iostream>
using namespace std;

int main()
{
    // Задание 1 

    int n;
    std::cout << "Введите количество элементов последовательности: "; std::cin >> n;

    float sum = 0;  // Для нахождения суммы 
    float max = -7; // Для нахождения максимума
    int num, num_max;// Для нахождения порядкового номера
    
    std::cout << "Введите элементы последовательности: " << std::endl;

    for(int i = 0; i < n; i++)
    {
        float x;
        std::cin >> x;

        num = i+1; // номер текущего числа 

        // Проверка на нахождение на отрезке
        if (-7 <= x && x <= 19)
        {
            sum += x; 
            if (x > max)
            {
                max = x;
                num_max = num; // записываем текущий номер в номер макс. числа
            }                                                                    
        }         
    }

    std::cout << "Сумма найденных элементов равна: " << sum << std::endl;   
    std::cout << "Максимальный элемент равен: " << max << ". Его номер: " << num_max << std::endl; 




    // Задание 2 

    int x;
    int summa = 0;
    std::cout << ". . . " << std::endl;
    std::cout << "Введите натуральное число: "; std::cin >> x;
    while (x > 0)
    {
        int d = x % 10;
        summa += d;
        x /= 10;
    }
    std::cout << "Сумма цифр числа равна: " << summa;
}