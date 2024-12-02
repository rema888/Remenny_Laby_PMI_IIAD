#include <func.hpp>
#include <iostream>

namespace laba_7
{
bool isPrime(int x) 
{
    if(x < 2)
        return false;
    for (int d = 2; d <= sqrt(x); d++)
        if(x % d == 0)
            return false;
    return true;       
}

void Read(int matrix[N_Max][M_Max], int& n, int& m) 
{
	std::cout << "Введите количество строк и столбцов матрицы: "; std::cin >> n >> m;
    std::cout << "Введите элементы матрицы: " << std::endl;
	for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            std::cin >> matrix[i][j];
        }
}

void Write(int matrix[N_Max][M_Max], int& n, int& m)
{
    std::cout << "Полученная матрица: " << std::endl;
	for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;    
    }
}

bool same_strings(int matrix[N_Max][M_Max], int& n, int& m)
{
    for (int i=0;i<n;i++) // Проходим по строке 
    {
        for (int j=i+1;j<n;j++) // Проходим по след строке
        {
            bool flag = true;       // Предполагаем, что строки равны
            for (int k=0;k<m;k++)   // Проходим по элементам обоих строк
            {
                if (matrix[i][k] != matrix[j][k])
                {
                    flag = false;
                    break;
                }
            }
            if (flag) return true;
        }
    }
    return false;
}

int biggest_simple(int matrix[N_Max][M_Max], int& n, int& m)
{
    int big_simple = -1'000'000'000;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++) 
        {
            if (isPrime(matrix[i][j]) && (big_simple < matrix[i][j])) 
            {
                big_simple = matrix[i][j];
            }       
        }
    }
    return big_simple;
}  

void replace_minimal(int matrix[N_Max][M_Max], int& n, int& m, int number)
    {
        for (int j=0;j<m;j++)
        {
            int minimal = 100000000;
            int index = 0;
            for (int i=0;i<n;i++)
            {
                if (matrix[i][j] < minimal) // Если 2 одинаковых мин элемента в столбце, то заменится только с высшей строки
                {
                    minimal = matrix[i][j];
                    index = i;
                }
            }
            matrix[index][j] = number;
        }
    }
}