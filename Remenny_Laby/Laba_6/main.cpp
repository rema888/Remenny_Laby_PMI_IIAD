#include <iostream>
using namespace std;


int main()
{
    // Задание 1
    int mas[10000];
    int lastDigit[10000];
    bool ravenstvo = false;
    int n;
    std::cout << "Введите длину массива: "; std::cin >> n;
    std::cout << "Введите элементы массива: ";
   
    for(int i=0;i<n;i++)
    {
        std::cin >> mas[i];
        lastDigit[i] = (mas[i] % 10);
    }

    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if (mas[i] == mas[j])
            {
                ravenstvo = true;
                break;
            }
    //swap sort
    if (ravenstvo)
    {
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
                if (lastDigit[i] < lastDigit[j])
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


