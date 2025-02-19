#include <iostream>

int factorial(int n) 
{
    if (n == 0 || n == 1) 
        return 1;
        
    return n * factorial(n - 1);
}

int main() 
{
    int N;
    std::cout << "Введите число N (от 1 до 19 включительно): ";
    std::cin >> N;
    if (N < 1 || N > 19) 
    {
        std::cout << "Ошибка: N должно быть в диапазоне от 1 до 19." << std::endl;
    }

    int result = factorial(N);
    std::cout << "Факториал числа " << N << " равен " << result << std::endl;
}