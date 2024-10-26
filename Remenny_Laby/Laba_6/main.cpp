#include <iostream>
using namespace std;


int main()
{
    // Задание 1

    int mas[10000];
    bool ravenstvo = false;
    int n;
    std::cout << "Введите длину массива: "; std::cin >> n;
    std::cout << "Введите элементы массива: ";
   
    // Ввод массива
    for(int i=0;i<n;i++)
    {
        std::cin >> mas[i];
    }

    // Проверка на наличие одинаковых чисел в массиве 
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if (mas[i] == mas[j])
            {
                ravenstvo = true;
                break;
            }

    // Сортировка обменом (Swap sort)
    if (ravenstvo)
    {
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
                if ((mas[i] % 10) < (mas[j] % 10))
                {
                    int tmp = mas[i];
                    mas[i] = mas[j];
                    mas[j] = tmp;
                }
        std::cout << "Отсортированный массив по последней цифре числа: ";
        for(int i=0;i<n;i++)
        {
            std::cout << mas[i] << " ";
        }  
    }    

    else
    {
        std::cout << "Массив остаётся прежним: ";
        for(int i=0;i<n;i++)
        {
            std::cout << mas[i] << " ";
        }  
    }          
}


