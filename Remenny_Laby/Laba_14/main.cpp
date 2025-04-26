#include <iostream>
#define N_Max 1000

class BigInt
{
    // Поля
    char m_value[N_Max]; // Для хранения цифр числа
    short m_size = 0;  // Для хранения количества значащих цифр в числе
    
    // Методы
    public:
    
        BigInt() // Конструктор по умолчанию
        {
            m_value[0] = 0;
            m_size = 1;
        }

        BigInt(const std::string& value) // Конструктор из строки
        { 
            size_t len = value.length(); // Записываем длину строки
            for(int i=0;i<len;i++)
                m_value[i] = value[len-i-1] - '0'; // Числа кладём в обратном порядке: "1234" хранится как m_value = {'4', '3', '2', '1', '0', ...}
                                                   // Операция - '0' вычитает ASCII-код нуля (48), преобразуя символ в соответствующее число 
                                                   // '4' (52) - '0' (48) = 4 (тип char, но значение числовое)
            for(int i=len;i<N_Max;i++)
                m_value[i] = 0; // Все оставшиеся значения заполняем нулями для корректной работы арифметических операций

            m_size = len; // Количество значащих цифр
        }
    
        BigInt& operator+=(const BigInt& other)
        {
            for(int i=0;i<m_size;i++) // Проходим по всем значащим цифрам
            {
                m_value[i] += other.m_value[i];
                if(m_value[i] > 9)
                {
                    m_value[i] -= 10; // Уменьшаем текущую цифру на 10
                    m_value[i+1]++; // Прибавляем 1 в следующий разряд
                    if(i+1 == m_size) // Если произошел перенос в новый разряд (999+1)
                        m_size++;
                }
            }
            return *this; // изменённый текущий объект класса
        }


        BigInt operator+(const BigInt& other)
        {
            BigInt result(*this); // Новый объект result, который является копией текущего объекта (используется конструктор копирования) 
            result += other;
            return result;
        }

        BigInt& operator*=(const BigInt& other) 
        {
            char temp[N_Max] = {0}; // Временный массив заполняем нулями, в нем будет храниться результат умножения

            // Алгоритм умножения в столбик
            for (int i = 0; i < m_size; i++) 
            {
                for (int j = 0; j < other.m_size; j++) 
                {
                    // Умножаем цифры и добавляем в temp со смещением i+j
                    temp[i + j] += m_value[i] * other.m_value[j];
                    
                    // Обрабатываем перенос сразу
                    if (temp[i + j] > 9) 
                    {
                        temp[i + j + 1] += temp[i + j] / 10; // В следующий разряд переносим значение десятка (2*6=12 => temp[1] += temp[0] / 10 = 12/10 = 1)
                        temp[i + j] %= 10;                   // В текущем разряде оставляем значение из разряда единиц  (temp[0] %= 10 = 12%10 = 2)
                    }
                }
            }
        
            int new_size = m_size + other.m_size; // Обновляем размер (максимальный возможный размер = m_size + other.m_size)

            while (new_size > 1 && temp[new_size - 1] == 0)
                new_size--; // Удаляем ведущие нули (Если temp содержит [4, 2, 0, 0], то после цикла new_size станет 2 (число "24"))
        
            // Копируем результат в текущий объект
            for (int i = 0; i < new_size; i++) 
            {
                m_value[i] = temp[i];
            }
            m_size = new_size;
        
            return *this;
        }
        
        BigInt operator*(const BigInt& other)
        {
            BigInt result(*this);
            result *= other;
            return result;
        }

        bool operator<(const BigInt& other)
        {
            if(m_size != other.m_size)
                return (m_size < other.m_size);
                
            for(int i = m_size-1; i >= 0; i--) // Идем от старшего разряда к младшему
            {
                if(m_value[i] != other.m_value[i])
                    return (m_value[i] < other.m_value[i]);
            }
            return false; // Если все совпало
        }

        bool operator>(const BigInt& other)
        {
            if(m_size != other.m_size)
                return m_size > other.m_size;
                
            for(int i = m_size-1; i >= 0; i--)
            {
                if(m_value[i] != other.m_value[i])
                    return m_value[i] > other.m_value[i];
            }
            return false;
        }

        bool operator==(const BigInt& other)
        {
            if(m_size != other.m_size) // Сравниваем размер
                return false;
                
            for(int i = 0; i < m_size; i++)
            {
                if(m_value[i] != other.m_value[i]) // Сравниваем все цифры
                    return false;
            }
            return true;
        }

        bool operator!=(const BigInt& other)
        {
            return !(*this == other); // Возвращает true если числа не равны, false - если равны 
                                      // 123 != 456 → !(false) = true
        }

        friend std::ostream& operator<<(std::ostream& out, const BigInt& other);
        // Оператор вывода вне класса, поэтому чтобы получить доступ к приватным полям m_value и m_size, её нужно объявить как friend внутри класса
};

std::istream& operator>>(std::istream& in, BigInt& other) // Оператор ввода, std::istream& in — ссылка на поток ввода (std::cin)
                                                          // BigInt& other — ссылка на объект BigInt, в который будет записано введённое число
{
    std::string s;
    in >> s; // читаем строку из потока 
    for (char c: s)
    {
        if(c < '0' || c > '9')
        {
            throw std::invalid_argument("Ошибка: в строке должны быть только цифры!");
        }
    }
    other = BigInt(s); // записываем результат в переданный обьект 
    return in; // возвращаем ссылку на поток ввода, чтобы можно было делать цепочку операций ввода 
}

std::ostream& operator<<(std::ostream& out, const BigInt& other) // Оператор вывода, std::ostream& out — ссылка на поток вывода (std::cout)
{
    for(int i=0;i<other.m_size;i++) // Перебираем все цифры числа
    { 
        out << static_cast<short>(other.m_value[other.m_size-i-1]); // static_cast преобразует значение char в short, чтобы корректно отобразить число
                                                                    // other.m_value = {3, 2, 1}
                                                                    // out << other.m_value[2];  1 → выводится ASCII-символ с кодом 1 (невидимый) 
    }
    return out; // возвращаем ссылку на поток вывода, чтобы можно было делать цепочку операций вывода 
}

int main()
{
    BigInt x("1123333");
    BigInt y("999277777");
    std::cout << "x + y = " << x + y << std::endl;
    std::cout << "x += y = " << (x += y) << std::endl;

    BigInt a("1111");
    BigInt b("9513");
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a *= b = " << (a *= b) << std::endl;

    BigInt m("1345674444");
    BigInt n("134322");
    BigInt k("134322111111");
    BigInt v("134322");
    
    if (m > n)
        std::cout << "m > n" << std::endl;
    if (n < k)
        std::cout << "n < k" << std::endl;
    if (n == v)
        std::cout << "n == v" << std::endl;
    if (m != v)    
        std::cout << "m != v" << std::endl;

    try
    {
        BigInt q, p;
        std::cin >> q >> p;
        std::cout << "q = " << q << " p = "<< p << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    BigInt w;
    std::cout << "w = " << w << std::endl;

    BigInt z = x; // Конструктор копирования по умолчанию копирует значения полей объекта в новый объект
    std::cout << z << std::endl;

    BigInt h;
    h = y; // Оператор присваивания копированием по умолчанию копирует все поля из y в h
    std::cout << h << std::endl; 
}