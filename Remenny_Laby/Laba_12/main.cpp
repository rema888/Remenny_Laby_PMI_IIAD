#include <iostream>
#include <fstream>
#include <func.hpp>
   
int main()
{
    // Задание 1
    int N;
    std::cout << "Введите число N (от 1 до 19 включительно): ";
    std::cin >> N;
    if (N <= 0)
    {
        std::cout << "N должно быть натуральным." << std::endl;
    }
    std::cout << "Сумма цифр числа " << N << " равна " << sum_of_digits(N) << std::endl;

    // Задание 2
    const int X = 10;
    int arr[X];

    std::cout << "Исходный массив: " << std::endl;
    for (int i=0;i<X;i++)
    {
        arr[i] = rand() % 100;
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    QuickSort(arr, 0, X-1);
    std::cout << "Отсортированный массив: " << std::endl;
    for (int i=0;i<X;i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Задание 3
    std::ifstream in("input.txt");
    char field[100][100]; // игровое поле
    int table[100][100]; // таблица с минимальным количеством шагов до каждой клетки
    int n, m; // размеры поля
    int is, js; // координаты старта
    int ie, je; // координаты конца
    in >> n >> m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            table[i][j] =  INT_MAX;
            in >> field[i][j];
            if(field[i][j] == 'S')
            {
                is = i;
                js = j;
            }
            else if(field[i][j] == 'E')
            {
                ie = i;
                je = j;
            }
        }

    Search(is, js, 0, n, m, field, table); // 0 - количество шагов когда находимся в вершине   

    if(table[ie][je] == INT_MAX)
    {
        std::cout << -1 << std::endl; // путь не найден
    }

    else
    {
        std::cout << table[ie][je] << std::endl;
    }

    std::cout << "Исходное поле:" << std::endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            std::cout << field[i][j] << ' ';
        std::cout << std::endl;    
    }
}