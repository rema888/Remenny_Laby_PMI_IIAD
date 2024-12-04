#include <iostream>

int main()
{
    long long x;
    std::cout << "Введите число: ";
    std::cin >> x;

    unsigned char* c = reinterpret_cast<unsigned char*>(&x);

    for (int i = 0; i < sizeof(long long); i++)
    {
        std::cout << "Байт " << i+1 << ": " << static_cast<int>(c[i]) << std::endl;
    }
}
