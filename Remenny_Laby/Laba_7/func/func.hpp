#pragma once 

const int N_Max = 100;
const int M_Max = 100;

namespace laba_7
{
    bool isPrime(int x);
    bool same_strings(int matrix[N_Max][M_Max], int& n, int& m);
    void Read(int matrix[N_Max][M_Max], int& n, int& m);
    void Write(int matrix[N_Max][M_Max], int& n, int& m);
    int biggest_simple(int matrix[N_Max][M_Max], int& n, int& m);
    void replace_minimal(int matrix[N_Max][M_Max], int& n, int& m, int number);
}