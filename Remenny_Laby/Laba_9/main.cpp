#include <iostream>

int main()
{
    long long x;
    std::cout << "Введите число: ";
    std::cin >> x;

    unsigned char* c = reinterpret_cast<unsigned char*>(&x); // &x - адрес, где хранится значение переменной x.
                                                             // Оператор приведения типов позволяет интерпретировать адрес переменной x
                                                             // как указатель на массив unsigned char.

    for (int i = 0; i < sizeof(long long); i++)
    {
        std::cout << "Байт " << i+1 << ": " << static_cast<int>(c[i]) << std::endl; //static_cast преобразует значение байта (unsigned char) в  
                                                                                    // целое число, чтобы корректно отобразить его как число.
    }
}
// 1000 - 000..... 001110100011
// 1) 232 - 11101000
// 2) 3 - 00000011
// 3) 0 - 00000000 ... 