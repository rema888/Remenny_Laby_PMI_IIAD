#include <iostream>
#include <fstream>

unsigned long long factorial(int n) 
{
    if (n <= 1) 
        return 1;    
    return n * factorial(n - 1);
}

void Search(int i, int j, int step, int n, int m, char field[100][100], int table[100][100])
{
    if (step >= table[i][j])
        return;

    table[i][j] = step;    

    if(field[i][j] == 'E')
        return;
    // Все возможные ходы
    if (i + 1 < n && field[i+1][j] != '#')    
        Search(i+1,j,step+1,n,m,field,table);
    if (i - 1 >= 0 && field[i-1][j] != '#')  
        Search(i-1,j,step+1,n,m,field,table);
    if (j + 1 < m && field[i][j+1] != '#')  
        Search(i,j+1,step+1,n,m,field,table);
    if (j - 1 >= 0 && field[i][j-1] != '#')      
        Search(i,j-1,step+1,n,m,field,table);
}

int main() 
{
    // Задание 1
    int N;
    std::cout << "Введите число N (от 1 до 19 включительно): ";
    std::cin >> N;
    if (N < 1 || N > 19) 
    {
        std::cout << "Ошибка: N должно быть в диапазоне от 1 до 19." << std::endl;
    }
    std::cout << "Факториал числа " << N << " равен " << factorial(N) << std::endl;

    // Задание 3
    std::ifstream in("input.txt");
    char field[100][100];
    int table[100][100];
    int n, m;
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

    Search(is, js, 0, n, m, field, table); // 0 - количество шагов    
    std:: cout << table[ie][je] << std::endl;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            std::cout << field[i][j] << ' ';
        std::cout << std::endl;    
    }
}