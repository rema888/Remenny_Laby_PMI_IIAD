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
    if(left > right)
        return;

    int p = arr[(left + right) / 2]; // Выбор опорного элемента

    int i = left;
    int j = right;
    while (i <= j)
    {
        while(arr[i] < p) i++;
        while(arr[j] > p) j--;
        if (i <= j)
        {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    QuickSort(arr, left, j);
    QuickSort(arr, i, right);
}

void Search(int i, int j, int step, int n, int m, char field[100][100], int table[100][100]) 
{
    if(step >= table[i][j])
        return;

    table[i][j] = step;

    if(field[i][j] == 'E')
        return;

    if(i + 1 < n && field[i+1][j] != '#')
        Search(i+1,j,step+1,n,m,field,table);
    if(i - 1 >= 0 && field[i-1][j] != '#')
        Search(i-1,j,step+1,n,m,field,table);
    if(j + 1 < m && field[i][j + 1] != '#')
        Search(i,j+1,step+1,n,m,field,table);
    if(j - 1 >= 0 && field[i][j - 1] != '#')
        Search(i,j-1,step+1,n,m,field,table);
}