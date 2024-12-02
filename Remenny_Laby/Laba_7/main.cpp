#include <iostream>
#include <func.hpp>
using namespace std;

int main()
{
    int matrix[N_Max][M_Max];
    int n, m;
    laba_7::Read(matrix,n,m);
    int biggest_simple = laba_7::biggest_simple(matrix,n,m);
    if(laba_7::same_strings(matrix,n,m) && biggest_simple != -1'000'000'000)
    {
        laba_7::replace_minimal(matrix,n,m, biggest_simple);
    }
    laba_7::Write(matrix,n,m);
}