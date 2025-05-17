#include <iostream>

template<typename T>
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
        void push_back(int value)
        {
            if (m_size + 1 > m_cap) 
                reserve(m_cap * 2 + 1);
            
            m_arr[m_size] = value;
            m_size++;
        }

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

        void insert(int pos, int value) 
        {
            // Проверка корректности позиции
            if (pos > m_size || pos < 0)
                throw std::out_of_range("Ошибка: выход за границы вектора");

            // Если нужно больше места - расширяем capacity
            if (m_size + 1 > m_cap)
                reserve(m_cap * 2 + 1);

            // Сдвигаем элементы вправо начиная с pos
            for (int i = m_size; i > pos; i--) 
                m_arr[i] = m_arr[i - 1];

            // Вставляем новый элемент
            m_arr[pos] = value;
            m_size++;
        }

        void erase(int start, int end)
        {
            if (start < 0 || start > end || end > m_size)
                throw std::out_of_range("Ошибка: некорректный диапазон");

            int count = end - start + 1; // Удаляем все элементы с start по end включительно
            
            for (int i = start; i + count < m_size; i++)
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
};

struct BitRef 
{
    MyVector<uint64_t>& bits; // Ссылка на вектор, хранящий биты
    size_t m_bit_index; // Индекс бита
 
    // При создании объекта BitRef передается ссылка на вектор и индекс бита
    BitRef(MyVector<uint64_t>& vec, size_t bit_index)
        : bits(vec), m_bit_index(bit_index) {}

    // Работает как get_bit - Позволяет получать значение бита как логическое (true или false)
    operator bool()  
    {
        return (bits[m_bit_index / 64] >> (m_bit_index % 64)) & 1ULL;
    }
    // В результате возвращается true, если бит равен 1, иначе — false

    
    // Работает как set - Позволяет установить значение бита по его индексу
    BitRef& operator=(bool value) 
    {
        if (value)
            bits[m_bit_index / 64] |= (1ULL << m_bit_index % 64);
        else
            bits[m_bit_index / 64] &= ~(1ULL << m_bit_index % 64);
        
        return *this;
    }
};

template<>
class MyVector<bool> // Специализация для bool
{
    private:
    
        MyVector<uint64_t> bits; // Вектор из 64-битных беззнаковых целых чисел
        size_t m_size;

        // bits — это вектор чисел (MyVector<uint64_t>), где каждое число содержит 64 bool

        // Каждый элемент bits[i] — это 64-битное число (uint64_t)

        // Каждый бит в bits[i] хранит одно значение bool (1 = true, 0 = false)

        // bits[0] → хранит биты 0-63 (64 значения)
        // bits[1] → хранит биты 64-127

        void set_bit(size_t bit_index) // устанавливает конкретный бит в 1 внутри соответствующего 64-битного блока в векторе bits
        {
            bits[bit_index / 64] |= (1ULL << (bit_index % 64)); // bits[0] = 0b000...10001 v.set(2, true);
                                                                // 1ULL в бинарном виде: 0b000...0001
                                                                // После сдвига на 2 позиции влево: 0b000...0100
                                                                //   0b...010001  (исходное bits[0])
                                                                // | 0b...000100  (маска)
                                                                //   --------------
                                                                //   0b...010101  (результат)
        }

        void clear_bit(size_t bit_index) 
        {
            bits[bit_index / 64] &= ~(1ULL << (bit_index % 64)); // bits[0] = 0b000...10101 v.set(2, false);
                                                                 // 1ULL в бинарном виде: 0b000...0001
                                                                 // После сдвига на 2 позиции влево: 0b000...100
                                                                 // Инверсия маски (побитовое НЕ): ~(0b000...100) = 0b...111011
                                                                 //   0b...010101  
                                                                 // | 0b...111011
                                                                 //   --------------
                                                                 //   0b...010001  
        } 

        bool get_bit(size_t bit_index) const 
        {
            return (bits[bit_index / 64] >> (bit_index % 64)) & 1ULL; // bits[0] = 0b000...10101
                                                                      // После сдвига на 2 позиции вправо: 0b000...101 (нужный бит стал младшим)
                                                                      //   0b000...101 
                                                                      // & 0b...111011  
                                                                      //   --------------
                                                                      //   0b...000001 
        }

    public:

        MyVector()
        {
            m_size = 0;
            bits = MyVector<uint64_t>();
        }

        void push_back_bool(bool value) 
        {
            if (m_size % 64 == 0) 
                bits.push_back(0);
            
            if (value) 
                set_bit(m_size);
            
            m_size++;
        }

        void set(size_t index, bool value) 
        {
            if (index >= m_size) 
                throw std::out_of_range("Выход за границы вектора");

            if (value) 
                set_bit(index);
            else 
                clear_bit(index);
        }

        void insert(size_t index, bool value) 
        {
            if (index >= m_size) 
                throw std::out_of_range("Выход за границы вектора");

            push_back_bool(false);

            // Сдвигаем биты вправо от m_size-1 до index+1 
            for (size_t i = m_size - 1; i > index; i--) // До сдвига:      [1, 0, 0, 0, 1] insert(2,true)
                                                        // После сдвига:   [1, 0, 0, 0, 1, 0] -> [1, 0, 0, 0, 0, 1] -> [1, 0, 1, 0, 0, 1]
                set(i, (*this)[i - 1]); // Получаем значение элемента с индексом (i + 1)

            set(index, value);  
        }

        void erase(size_t index) 
        {
            if (index >= m_size) 
                throw std::out_of_range("Выход за границы вектора");

            // Сдвигаем биты влево
            for (size_t i = index; i < m_size - 1; ++i) // "Закрываем" наш текущий индекс другими [1, 0, 1, 0, 0, 1] -> [1, 1, 0, 0, 1, 1] -> [1, 1, 0, 0, 1]
                set(i, (*this)[i + 1]); 
            
            m_size--;
        }

        BitRef operator[](size_t index) 
        {
            if (index >= m_size)
                throw std::out_of_range("Выход за границы вектора");

            return BitRef(bits, index);
        }
        // Создает временный объект BitRef, передавая ему:
        // bits - ссылку на внутренний вектор uint64_t (где хранятся биты)
        // index - запрошенную позицию бита

        bool operator[](size_t index) const 
        {
            if (index >= m_size)
                throw std::out_of_range("Выход за границы вектора");
                
            return get_bit(index);
        }
        

        size_t size()
        {
            return m_size;
        }      
};


int main() 
{
    MyVector<bool> v;
    
    v.push_back_bool(true);
    v.push_back_bool(false);
    v.push_back_bool(false);
    v.push_back_bool(false);
    v.push_back_bool(true);

    v[2] = true;
    std::cout << v[2] << std::endl;

    // Операция	            Состояние bits[0]          	    Индексы битов	m_size
    // v.push_back(true)	0b000...0001	                Бит 0 = 1	    1
    // v.push_back(false)	0b000...0001	                Бит 1 = 0	    2
    // v.push_back(true)	0b000...0101	                Бит 2 = 1	    3
    // v.push_back(false)	0b000...0101	                Бит 3 = 0	    4
    // v.push_back(true)	0b000...10101	                Бит 4 = 1	    5

    std::cout << "Размер v: " << v.size() << std::endl;

    for (size_t i = 0; i < v.size(); i++) 
        std::cout << v[i] << " ";
    std::cout << std::endl;

    v.set(2, true);

    std::cout << "Меняем 2oй индекс на true: ";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;

    v.insert(2, true);

    std::cout << "Вставляем во 2oй индекс true: ";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;

    v.erase(1);

    std::cout << "Удаляем 1ый индекс: ";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}