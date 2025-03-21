#include <func.hpp>
#include <iostream>

int sum_of_digits(int N) 
{
    if (N == 0) 
    {
        return 0;
    }
    // Последняя цифра + сумма цифр оставшейся части
    return (N % 10) + sum_of_digits(N / 10);
}

void QuickSort(int arr[], int left, int right) 
{
    if(left > right)  // значит все отсортировано
        return;

    int p = arr[(left + right) / 2]; // Выбор опорного элемента

    int i = left; // индекс i указывает на левую границу, сначала i у первого элемента
    int j = right; // индекс j указывает на правую границу, сначала j у последнего элемента

    while (i <= j) // пока индексы не разойдутся
    {
        while(arr[i] < p) i++; // перемещаем i вправо, пока не найдем элемент, больший или равный опорному
        while(arr[j] > p) j--; // перемещаем j влево, пока не найдем элемент, меньший или равный опорному
        if (i <= j) // когда отсортируем 1 раз массив и индекс j будет левее, а индекс i будет правее
                    // те элементы что левее j - меньше или равны опорному, те что правее i - больше или равны опорному
        {
            int tmp = arr[i]; // меняем местами элементы с индексами i и  j
            arr[i] = arr[j];
            arr[j] = tmp;
            i++; // продвигаем i на один шаг а j уменьшаем
            j--;
        }
    }
    // i стал больше j 
    QuickSort(arr, left, j); // для каждой из полученных частей вызываем QuickSort отдельно
    QuickSort(arr, i, right);
}

void Search(int i, int j, int step, int n, int m, char field[100][100], int table[100][100]) 
{
    if(step >= table[i][j])
        return;

    table[i][j] = step;

    if(field[i][j] == 'E')
        return;

    // Прямые ходы
    if(i + 1 < n && field[i+1][j] != '#')
        Search(i+1,j,step+1,n,m,field,table);
    if(i - 1 >= 0 && field[i-1][j] != '#')
        Search(i-1,j,step+1,n,m,field,table);
    if(j + 1 < m && field[i][j + 1] != '#')
        Search(i,j+1,step+1,n,m,field,table);
    if(j - 1 >= 0 && field[i][j - 1] != '#')
        Search(i,j-1,step+1,n,m,field,table);

    // Диагональные ходы
    if (i + 1 < n && j + 1 < m && field[i + 1][j + 1] != '#')
    Search(i + 1, j + 1, step + 1, n, m, field, table);
    if (i + 1 < n && j - 1 >= 0 && field[i + 1][j - 1] != '#')
        Search(i + 1, j - 1, step + 1, n, m, field, table);
    if (i - 1 >= 0 && j + 1 < m && field[i - 1][j + 1] != '#')
        Search(i - 1, j + 1, step + 1, n, m, field, table);
    if (i - 1 >= 0 && j - 1 >= 0 && field[i - 1][j - 1] != '#')
        Search(i - 1, j - 1, step + 1, n, m, field, table);
}