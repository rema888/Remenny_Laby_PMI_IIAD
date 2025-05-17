#include <iostream>

class MyVector
{
    int* m_arr;
    size_t m_size; // Длина вектора
    size_t m_cap; // Сколько всего выделено ячеек

    public:
        // Базовый конструктор
        MyVector() // Пустой вектор
        {
            m_size = 0;
            m_cap = 0;
            m_arr = nullptr;
        }

        MyVector(size_t size, int value) // Передаем размер и некоторое значение, которым заполним вектор
        {
            m_arr = new int[size];
            m_cap = size;
            m_size = size;
            for (int i = 0; i < size; i++) 
                m_arr[i] = value;  // Заполняем массив значением value
        }

        // Конструктор копирования
        MyVector(const MyVector& other)
        {
            m_size = other.m_size;
            m_cap = other.m_cap;
            m_arr = new int[m_size];
            for (int i = 0; i < m_size; i++)
                m_arr[i] = other.m_arr[i];
        }

        // Оператор присваивания копированием
        MyVector& operator=(const MyVector& other) 
        {
            // Освобождаем старую память
            delete[] m_arr;

            m_size = other.m_size;
            m_cap = other.m_cap;
            m_arr = new int[m_size];
            for (int i = 0; i < m_size; i++)
                m_arr[i] = other.m_arr[i];

            return *this;  // Возвращаем ссылку на текущий объект
        }

        // Деструктор
        ~MyVector()
        {
            if(m_arr != nullptr) // Если нам есть что удалить (В пустом векторе мы не можем удалить nullptr)
                delete[] m_arr;
        }      

        // Методы
        void reserve(size_t cap) // Метод увеличивает capacity, сохранив все что есть в векторе 
        {
            if (m_size >= cap) // Capacity не может быть меньше size
                return;
            m_cap = cap;
            int* tmp = new int[m_cap];
            for (int i = 0; i < m_size; i++)
                tmp[i] = m_arr[i];
            delete[] m_arr;
            m_arr = tmp;
        }
        
        void push_back(int value)
        {
            if (m_size + 1 > m_cap) 
                reserve(m_cap * 2 + 1);
            
            m_arr[m_size] = value;
            m_size++;
        }

        void resize(size_t size) // Метод изменяет size и заполняет новые ячейки нулями
        {
            // Если новый размер меньше текущего - просто уменьшаем размер
            if (size <= m_size) 
                m_size = size;
                
            else 
            {
                // Если не хватает capacity - перевыделяем память
                if (size > m_cap)
                    reserve(size);

                // Заполняем новые элементы 0
                for (size_t i = m_size; i < size; i++)
                    m_arr[i] = 0;

                m_size = size;
            }
        }

        void shrink_to_fit() // Метод делает capacity = size
        {
            m_cap = m_size;
            int* tmp = new int[m_cap]; // Новый массив размера m_cap
            for(int i = 0; i < m_size; i++)
                tmp[i] = m_arr[i];
            delete[] m_arr;
            m_arr = tmp;
        }

        void insert(size_t pos, int value) 
        {
            // Проверка корректности позиции
            if (pos >= m_size)
                throw std::out_of_range("Ошибка: выход за границы вектора");

            // Если нужно больше места - расширяем capacity
            if (m_size + 1 > m_cap)
                reserve(m_cap * 2 + 1);

            // Сдвигаем элементы вправо начиная с pos
            for (size_t i = m_size; i > pos; i--) 
                m_arr[i] = m_arr[i - 1];

            // Вставляем новый элемент
            m_arr[pos] = value;
            m_size++;
        }

        void erase(size_t start, size_t end)
        {
            if (start > end || end >= m_size)
                throw std::out_of_range("Ошибка: некорректный диапазон");

            size_t count = end - start + 1; // Удаляем все элементы с start по end включительно
            
            for (size_t i = start; i + count < m_size; i++)
                m_arr[i] = m_arr[i + count]; // Сдвигаем оставшиеся элементы влево

            m_size -= count; // Уменьшаем размер
        }

        int& front() // Метод возвращает первый элемент вектора
        {
            return m_arr[0];
        }
        
        int& back() // Метод возвращает последний элемент вектора 
        {
            return m_arr[m_size-1];
        }

        bool empty() // Метод проверяет, пуст ли вектор
        {
            return m_size == 0;
        }

        size_t size() // Метод возвращает размер (Геттер)
        {
            return m_size;
        }

        size_t capacity() // Метод возвращает capacity
        {
            return m_cap;
        }

        int& operator[](size_t index)
        {
            if (index >= m_size) 
                throw std::out_of_range("Выход за границы вектора");
            return m_arr[index]; // [] к указателю знает как применять
        }

        const int& operator[](size_t index) const 
        {
            if (index >= m_size) 
                throw std::out_of_range("Выход за границы вектора");
            return m_arr[index];
        }

        friend std::istream& operator>>(std::istream& in, MyVector& other);
        friend std::ostream& operator<<(std::ostream& out, const MyVector& other);
};

// Оператор вывода
std::ostream& operator<<(std::ostream& out, const MyVector& other) 
{
    out << "["; // Выводим скобку
    for (int i = 0; i < other.m_size; i++) // Проходим по элементам вектора
    {
        out << other.m_arr[i]; // Выводим элементы вектора
        if (i != other.m_size - 1) // Если не последний элемент
            out << ", "; // Выводим запятую
    }
    out << "]"; // Выводим скобку
    return out; // возвращаем ссылку на поток вывода
}

// Оператор ввода
std::istream& operator>>(std::istream& in, MyVector& other) 
{
    int count;
    in >> count;  // Считываем количество элементов

    if (count < 0)
        throw std::invalid_argument("Количество элементов не может быть отрицательным");
        
    other.m_size = count;
    other.m_cap = count;

    if (other.m_arr != nullptr)
        delete[] other.m_arr;  // Очищаем старые данные

    other.m_arr = new int[count];  // Выделяем память

    for (size_t i = 0; i < other.m_size; i++) 
    {
        if (!(in >> other.m_arr[i]))  // Если ввод элемента не удался
            throw std::runtime_error("Ошибка ввода элемента");
    }

    return in;
}

int main()
{
    MyVector v1;
    MyVector v2(3, 5);
    MyVector v3 = v2;
    MyVector v4(2,1);
    v4 = v1;
    std::cout << "1) v1 - пустой вектор: " << v1 << std::endl;
    std::cout << "2) v3 - конструктор копирования v2(3, 5): " << v3 << std::endl;
    std::cout << "3) v4 - Оператор присваивания копированием v1(): " << v4 << std::endl;

    v1.push_back(9);
    std::cout << "4) v1 - push_back(9): " << v1 << std::endl;

    std::cout << "5) v1 - capacity(): " << v1.capacity() << std::endl;
    v1.reserve(2000);
    std::cout << "6) v1 - capacity(): (После reserve(2000)): " << v1.capacity() << std::endl;
    v1.shrink_to_fit();
    std::cout << "7) v1 - capacity(): (После shrink_to_fit()): " << v1.capacity()<< std::endl;
    v1.resize(10);
    std::cout << "8) v1.resize(10): " << v1 << std::endl;
    v1.insert(4,7);
    std::cout << "9) v1.insert(4,7): " << v1 << std::endl;

    MyVector v5;
    for (int i=1; i<=10; i++) 
        v5.push_back(i);
    std::cout << "10) v5: " << v5 << std::endl;
    v5.erase(0,3);
    std::cout << "    v5.erase(0,3): " << v5 << std::endl;

    std::cout << "11) v2[1]: " << v2[1] << std::endl;
    v2[2] = 4;
    std::cout << "12) v2[1] = 4: " << v2 << std::endl;
    
    std::cout << "13) v2.front(): " << v2.front() << std::endl;
    std::cout << "14) v2.back(): " << v2.back() << std::endl;
    std::cout << "15) v2.empty(): " << v2.empty() << std::endl;

    try
    {
        MyVector v6;
        std::cout << "16) Введите количество элементов и сами элементы: ";
        std::cin >> v6; 
        std::cout << "    Вектор после ввода: " << v6 << std::endl;
    }

    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}