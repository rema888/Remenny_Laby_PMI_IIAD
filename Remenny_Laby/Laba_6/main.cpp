#include <iostream>
using namespace std;


int firstDigit(int x)
{
    while (abs(x) > 9)
    {
        x /= 10;
    }
    return abs(x);    // f(-324) = -3 -> нужен модуль  
}

int multipleOfDigits(int x)
{
    int mult = 1;

    if (x < 0)
    {
        mult *= -1; // Вводим модуль и умножаем число на -1 если оно отрицательное, чтобы избежать ситуации ниже
    }

    while (x != 0)
    {
        mult *= abs(x % 10);  // Если без модуля: 1) -3231 % 10 = -1
                              //                  2) -3231 % 10 = -3   ==> -1 * -3 * -2 * -3 == 18   Все числа со знаком - 
                              //                  3) -3231 % 10 = -2  
                              //                  4) -3231 % 10 = -3    
        x /= 10;
    }

    return mult;
}    

bool dif_digits(int n) 
{
    if (n < 0)
    {
        n = abs(n); 
    }

    // Проходим по всем цифрам числа
    // В начале i равно n, а затем мы делим i на 10 в каждой итерации, чтобы избавиться от последней цифры
    for (int i = n; i > 0; i /= 10) 
    {
        int digit = i % 10; // Извлекаем последнюю цифру числа i (текущую цифру для проверки)

        // Проходим по всем цифрам числа, кроме текущей
        for (int j = i / 10; j > 0; j /= 10) 
        {
            // Сравниваем текущую цифру с каждой из оставшихся цифр
            if (digit == j % 10) 
            {
                return false; 
            }
        }
    }

    return true; 
}

bool mltpl_14(int x)
{
    int mult = 1;
    
    if (x == 0)
    {
        return true; 
    }
    
    else if (x < 0)
    {
        mult *= -1; // Вводим модуль и умножаем число на -1 если оно отрицательное, чтобы избежать ситуации ниже
    }
    
    while (x != 0)
    {
        mult *= abs(x % 10);     // Если без модуля: 1) -3231 % 10 = -1
                                 //                  2) -3231 % 10 = -3   ==> -1 * -3 * -2 * -3 == 18,    Все числа со знаком - 
                                 //                  3) -3231 % 10 = -2  
                                 //                  4) -3231 % 10 = -3    
        x /= 10;
    }

    if (mult % 2 == 0 && mult % 7 == 0)
    {
        return true;
    }
    return false;
}    



int main()
{
    // Задание 1
    int mas1[10000];
    bool ravenstvo1 = false;
    int n1;
    std::cout << "Задание 1" << std::endl;
    std::cout << "Введите длину массива: "; std::cin >> n1;
    std::cout << "Введите элементы массива: ";
   
    // Ввод массива
    for(int i=0;i<n1;i++)
    {
        std::cin >> mas1[i];
    }

    // Проверка на наличие одинаковых чисел в массиве 
    for(int i=0;i<n1;i++)
        for(int j=i+1;j<n1;j++)
            if (mas1[i] == mas1[j])
            {
                ravenstvo1 = true;
                break;
            }

    // Сортировка обменом (Swap sort) - если есть одинаковые числа (по убыванию)
    if (ravenstvo1)
    {
        for(int i=0;i<n1;i++)
            for(int j=i+1;j<n1;j++)
                if ((abs(mas1[i]) % 10) < (abs(mas1[j]) % 10))  // -324 % 10 = -4 -> нужен модуль 
                {
                    int tmp = mas1[i];
                    mas1[i] = mas1[j];
                    mas1[j] = tmp;
                }
                
        std::cout << "Отсортированный массив по последней цифре числа: ";
        for(int i=0;i<n1;i++)
        {
            std::cout << mas1[i] << " ";
        }  
    }    

    else
    {
        std::cout << "Массив остаётся прежним: ";
        for(int i=0;i<n1;i++)
        {
            std::cout << mas1[i] << " ";
        }  
    }  
    std::cout << std::endl;

    // Задание 2  - тест 5 ; 983 -345 345 -3225 5932

    int mas2[1000];
    int masFirst[1000];
    int masMult[1000];
    int n2;
    std::cout << "Задание 2" << std::endl;
    std::cout << "Введите длину массива: "; std::cin >> n2;
    std::cout << "Введите элементы массива: ";
   
    // Ввод массива
    for(int i=0;i<n2;i++)
    {
        std::cin >> mas2[i];
        masFirst[i] = firstDigit(mas2[i]);
        masMult[i] = multipleOfDigits(mas2[i]);
    }

     // Сортировка по первой цифре числа

    for(int i=0;i<n2;i++)
        for(int j=i+1;j<n2;j++)
            if (masFirst[i] > masFirst[j])
            {
                int tmp = mas2[i];
                mas2[i] = mas2[j];
                mas2[j] = tmp;

                int tmp2 = masFirst[i];
                masFirst[i] = masFirst[j];
                masFirst[j] = tmp2;

                int tmp3 = masMult[i];
                masMult[i] = masMult[j];
                masMult[j] = tmp3;
            }

    std::cout << "По возр. первой цифры: ";
    for(int i=0;i<n2;i++)
    {
        std::cout << mas2[i] << " ";
    }  

    // Сортировка чисел с одинаковой первой цифрой по возрастанию произведения цифр

    for(int i=0;i<n2;i++)
        for(int j=i+1;j<n2;j++)
            if (masFirst[i] == masFirst[j])
            {
                if (masMult[i] > masMult[j])
                {
                    int tmp = mas2[i];
                    mas2[i] = mas2[j];
                    mas2[j] = tmp;

                    int tmp2 = masFirst[i];
                    masFirst[i] = masFirst[j];
                    masFirst[j] = tmp2;

                    int tmp3 = masMult[i];
                    masMult[i] = masMult[j];
                    masMult[j] = tmp3;
                }
            }

    std::cout << "По возр. произведения цифр: ";
    for(int i=0;i<n2;i++)
    {
        std::cout << mas2[i] << " ";
    }  

    // Сортировка чисел с одинаковой первой цифрой и произведением по возрастанию самих чисел

    for(int i=0;i<n2;i++)
        for(int j=i+1;j<n2;j++)
            if ((masFirst[i] == masFirst[j]) && (masMult[i] == masMult[j]))
            {
                if (mas2[i] > mas2[j])
                {
                    int tmp = mas2[i];
                    mas2[i] = mas2[j];
                    mas2[j] = tmp;

                    int tmp2 = masFirst[i];
                    masFirst[i] = masFirst[j];
                    masFirst[j] = tmp2;

                    int tmp3 = masMult[i];
                    masMult[i] = masMult[j];
                    masMult[j] = tmp3;
                }         
            }

    std::cout << "По возр.самих чисел: ";
    for(int i=0;i<n2;i++)
    {
        std::cout << mas2[i] << " ";
    }  
    std::cout << std::endl;

    // Задание 3 

    int matrix[100][100];
    int n3,m3;
    int column_summ;
    int min_summ = pow(2,30);
    int min_column_number;
    std::cout << "Задание 3" << std::endl;
    std::cout << "Введите количество строк и столбцов матрицы: "; std::cin >> n3 >> m3;

    // Ввод матрицы
    std::cout << "Введите элементы матрицы: " << std::endl;
    for(int i=0;i<n3;i++)
        for(int j=0;j<m3;j++)
        {
            std::cin >> matrix[i][j];
        }
    
    // Считаем сумму элементов столбца и, записав значения min_summ и min_column_number для 1 столбца, сравниваем min_summ со след.столбцами
    for (int j=0;j<m3;j++) { 
        column_summ = 0;
		for (int i=0;i<n3;i++) 
        {
			column_summ += matrix[i][j];
		}

		if (column_summ < min_summ) 
        {
			min_summ = column_summ;
			min_column_number = j;
		}
	}

    // Элементы столбца с минимальной суммой увеличиваем на 3 
    for(int i=0;i<n3;i++)
    {
        matrix[i][min_column_number] += 3;
    }

    // Вывод матрицы
    std::cout << "Полученная матрица: " << std::endl;
    for(int i=0;i<n3;i++)
    {
        for(int j=0;j<m3;j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;    
    }

    // Задание 4

    int mas4[20000];
    int n4;
    std::cout << "Задание 4" << std::endl;
    std::cout << "Введите длину массива: "; std::cin >> n4;
    std::cout << "Введите элементы массива: ";
   
    // Ввод массива
    for(int i=0;i<n4;i++)
    {
        std::cin >> mas4[i];
    }

    // Удаление
    for(int i=0;i<n4;i++)
    {
        if(dif_digits(mas4[i]))
        {
            for(int j=i;j<n4-1;j++)
                mas4[j] = mas4[j+1];
            i--;
            n4--;   
        }
    }


    // Дублирование
    for(int i=0;i<n4;i++)
    {
        if(mltpl_14(mas4[i])) 
        {
            for(int j=n4;j>i;j--)
                mas4[j] = mas4[j-1];
            i++;
            n4++;   
        }
    }
    
   

    // Вывод массива
    std::cout << "Отсортированный массив: ";
    for(int i=0;i<n4;i++)
    {
        std::cout << mas4[i] << " ";
    }  
}