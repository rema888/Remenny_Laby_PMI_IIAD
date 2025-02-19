#include <iostream>

int main()
{
    long long x;
    std::cout << "Введите число: ";
    std::cin >> x;

    unsigned char* c = reinterpret_cast<unsigned char*>(&x); // &x - адрес, где хранится значение переменной x.
                                                             // Оператор приведения типов позволяет интерпретировать адрес переменной x
                                                             // как указатель на массив unsigned char. (unsigned char* c хранит адрес 1ого байта x)

    for (int i = 0; i < sizeof(long long)/*=8*/ ; i++)
    {
        std::cout << "Байт " << i+1 << ": " << static_cast<int>(c[i])/*i-й байт x*/ << std::endl; //static_cast преобразует значение байта (un. char)  
                                                                                    // в целое число, чтобы корректно отобразить его.
            }
}  

// 1000 - 000..... 0011.11101000
// 1) 232 - 11101000
// 2) 3 - 00000011
// 3) 0 - 00000000 ... 