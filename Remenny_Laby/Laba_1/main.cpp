
// Ременный А (ПМИ-ИИАД) - Лабораторная работа 1


// 1) Дать определение переменной, понять, что это такое.
// Переменная  - это поименованная область памяти, в которую можно записать какое-то значение.

// 2) Перечислить основные типы данных в С++: целочисленные (знаковые и беззнаковые), вещественные, символьные, логические.
// Логический тип (bool)
// Целочисленные типы (int, short, long, long long; unsigned int, unsigned short, unsigned long, unsigned long long)
// Вещественные типы (float, double, long double)
// Символьные типы (char, unsigned char)

// 3, 4) Указать для каждого типа размер в байтах. Указать минимальное и максимальное значение для каждого типа.

// bool - 1 байт, от 0 до 1       int - 4 байта, от -2147483648 до 2147483647                          float - 4 байта, от 1.1Е—38 до 3.4Е+38             char - 1 байт, от -128 до 127
//                               unsigned int -  4 байта, от 0 до 4294967295                          double - 8 байт, от 1.7Е—308 до 1.7Е+308           unsigned char - 1 байт, от 0 до 255
//                               short - 2  байта, от -32768 до 32767                                 long double - 8 байт, от 2.2-308 до 1.7Е+308        
//                               unsigned short - 2 байта, от 0 до 65535                                                                      
//                               long - 4 байта, от -2147483648 до 2147483647                                                                
//                               unsigned long - 4 байта, от 0 до 4294967295
//                               long long - 8 байт, от -9223372036854775808 до 9223372036854775807
//                               unsigned long long - 8 байт, от 0 до 18446744073709551615

// 5) Составить программу, которая выводит название типа, размер, мин. и макс. значения.

#include <iostream>
#include <limits>
using namespace std;


int main()
{
std::cout << "5)" << std::endl;

std::cout << "bool - " << sizeof(bool) << " byte" << std::endl;

std::cout << "int - " << sizeof(int) << " bytes, " << numeric_limits<int>::min() << " to " << numeric_limits<int>::max() << " bytes" << std::endl;
std::cout << "unsigned int - " << sizeof(unsigned int) << " bytes, " << numeric_limits<unsigned int>::min() << " to " << numeric_limits<unsigned int>::max() << " bytes" << std::endl;

std::cout << "short - " << sizeof(short) << " bytes, " << numeric_limits<short>::min() << " to " << numeric_limits<short>::max() << " bytes" << std::endl;
std::cout << "unsigned short - " << sizeof(unsigned short) << " bytes, " << numeric_limits<unsigned short>::min() << " to " << numeric_limits<unsigned short>::max() << " bytes" << std::endl;

std::cout << "long - " << sizeof(long) << " bytes, " << numeric_limits<long>::min() << " to " << numeric_limits<long>::max() << " bytes" << std::endl;
std::cout << "unsigned long - " << sizeof(unsigned long) << " bytes, " << numeric_limits<unsigned long>::min() << " to " << numeric_limits<unsigned long>::max() << " bytes" << std::endl;

std::cout << "long long - " << sizeof(long long) << " bytes, " << numeric_limits<long long>::min() << " to " << numeric_limits<long long>::max() << " bytes" << std::endl;
std::cout << "unsigned long long - " << sizeof(unsigned long long) << " bytes, " << numeric_limits<unsigned long long>::min() << " to " << numeric_limits<unsigned long long>::max() << " bytes" << std::endl;

std::cout << "float - " << sizeof(float) << " bytes, " << numeric_limits<float>::min() << " to " << numeric_limits<float>::max() << " bytes" << std::endl;
std::cout << "double - " << sizeof(double) << " bytes, " << numeric_limits<double>::min() << " to " << numeric_limits<double>::max() << " bytes" << std::endl;
std::cout << "long double - " << sizeof(long double) << " bytes, " << numeric_limits<long double>::min() << " to " << numeric_limits<long double>::max() << " bytes" << std::endl;

std::cout << "char - " << sizeof(char) << " byte, " << (int)numeric_limits<char>::min() << " to " << (int)numeric_limits<char>::max() << " bytes" << std::endl;
std::cout << "unsigned char - " << sizeof(unsigned char) << " byte, " << (int)numeric_limits<unsigned char>::min() << " to " << (int)numeric_limits<unsigned char>::max() << " bytes" << std::endl;


// 6) Привести пример выполнения арифметической операции с каждым типом данных.

std::cout << "6)" << std::endl;

int a1 = 10, b1 = 7;
bool c{ a1 == b1 };
std::cout << "bool  ||  10==7, c = " << c << std::endl;

std::cout << "int  ||  10-7 = " << a1 - b1 << std::endl;

unsigned int a2 = 30494, b2 = 3049454;
std::cout << "unsigned int  ||  30494+3049454 = " << a2 + b2 << std::endl;

short a3 = -3000, b3 = 8;
std::cout << "short  ||  -3000*8 = " << a3 * b3 << std::endl;

unsigned short a4 = 65535, b4 = 5;
std::cout << "unsigned short  ||  65535/5 = " << a4 / b4 << std::endl;

long a5 = -45274, b5 = 9;
std::cout << "long  ||  -45274*9  = " << a5 * b5 << std::endl;

unsigned long a6 = 1234567, b6 = -1;
std::cout << "unsigned long  ||  1234567+7654321  = " << a6 + b6 << std::endl;

long long a7 = 6473839333, b7 = 72812891;
std::cout << "long long ||  6473839333-72812891  = " << a7 - b7 << std::endl;

unsigned long long a8 = 647383933, b8 = 728191;
std::cout << "unsigned long long ||  647383933-728191  = " << a8 * b8 << std::endl;

float a9 = 4.5, b9 = 1.5;
std::cout << "float || 4.5/1.5  = " << a9 / b9 << std::endl;

double a10 = 1.56, b10 = 8.372;
std::cout << "double || 1.56+8.372  = " << a10 + b10 << std::endl;

long double a11 = 345.222, b11 = 234.111;
std::cout << "long double || 345.222-234.111 = " << a11 - b11 << std::endl;

char a12 = '&', b12 = 'z';
std::cout << "char || &+z = " << (char)(a12 + b12) << std::endl;

unsigned char a13 = '&', b13 = 'z';
std::cout << "unsigned char || &-z = " << a13 - b13 << std::endl;
}