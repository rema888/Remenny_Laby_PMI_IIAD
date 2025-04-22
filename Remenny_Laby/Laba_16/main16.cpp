#include <iostream>
#include <stdexcept>
#include <initializer_list>
template <typename T, size_t N, size_t M> // объявление шаблона класса с тремя параметрами: typename T - параметр типа (int, float, double и т.д.)
                                          //                                                size_t N, M - параметры-константы для количества строк и столбцов
class Matrix
{
    static_assert(N <= 3 && M <= 3, "Максимальный размер матрицы - 3 на 3"); // static_assert — ключевое слово, которое проверяет условие на этапе компиляции    
    static_assert(std::is_arithmetic_v<T> && !std::is_same_v<T, char> && !std::is_same_v<T, bool>, "Матрицы поддерживают только числовые типы (не включая char и bool)");
    private:
        T data[N][M]; // Двумерный массив (матрица)
   
    public:

        Matrix() // Базовый конструктор (заполняет нулями)
        {
            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < M; j++)
                {
                    data[i][j] = 0;
                }
            }
        }
       
        /* Конструктор копирования
        Matrix(const Matrix& other) 
        {
            for (size_t i = 0; i < N; ++i) 
            {
                for (size_t j = 0; j < M; ++j) 
                {
                    data[i][j] = other.data[i][j];
                }
            }
        }*/

        /* Оператор присваивания
        Matrix& operator=(const Matrix& other) 
        {
            if (this != &other) 
            {
                for (size_t i = 0; i < N; ++i) 
                {
                    for (size_t j = 0; j < M; ++j) 
                    {
                        data[i][j] = other.data[i][j];
                    }
                }
            }
            return *this;
        }*/

        Matrix(std::initializer_list<std::initializer_list<T>> init)
        {
            size_t i = 0; // Индекс строки
            for (auto& row : init) // Проходим по каждой строке в инициализаторе
            {
                size_t j = 0; // Индекс столбца
                for (auto& val : row) // Проходим по каждому элементу в строке
                {
                    if (i < N && j < M) // Проверяем, что индексы не выходят за пределы матрицы
                    {
                        data[i][j] = val; // Записываем значение в матрицу
                    }
                    j++;
                }
                i++;
            }
        }
        // Оператор доступа по индексу
        T& operator()(size_t row, size_t col)
        {
            if (row >= N || col >= M)
                throw std::out_of_range("Введенные индексы должны быть меньше или равны 2");    
            return data[row][col];
        }
        // Константная версия для оператора умножения
        const T& operator()(size_t row, size_t col) const
        {
            if (row >= N || col >= M)
                throw std::out_of_range("Введенные индексы должны быть меньше или равны 2");
            return data[row][col];
        }

        // Преобразование матрицы в double
        Matrix<double, N, M> toDouble() const
        {
            Matrix<double, N, M> result;
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    result(i, j) = static_cast<double>(data[i][j]);
                }
            }
            return result;
        }

        // Оператор сложения с преобразованием в double
        template <typename U>
        Matrix<double, N, M> operator+(const Matrix<U, N, M>& other) const
        {
            auto thisDouble = this->toDouble();
            auto otherDouble = other.toDouble();
            
            Matrix<double, N, M> result;
            
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    result(i,j) = thisDouble(i,j) + otherDouble(i,j);
            
            return result;
        }

        
       
        // Нельзя изменить тип существующего объекта!!!!!
        // Вар 1 - Оператор += с преобразованием в double (создает новую матрицу)
        template <typename U>
        Matrix<double, N, M> operator+=(const Matrix<U, N, M>& other) 
        {
            Matrix<double, N, M> result = this->toDouble();
            auto otherDouble = other.toDouble();
            
            for (size_t i = 0; i < N; ++i) 
                for (size_t j = 0; j < M; ++j) 
                    result(i,j) += otherDouble(i,j);
            
            return result; // Но это уже не будет традиционным +=
        }
        
        // Вар 2 - Оператор += для  матриц одного типа
        Matrix<T, N, M>& operator+=(const Matrix<T, N, M>& other) 
        {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    this->data[i][j] += other.data[i][j];
                
            return *this; // Возвращаем ссылку на текущую матрицу
        }

        template <size_t K>
        Matrix<T, N, K> operator*(const Matrix<T, M, K>& other) const
        {
            Matrix<T, N, K> result;
            
            auto thisDouble = this->toDouble();
            auto otherDouble = other.toDouble();

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < K; ++j)
                {
                    result(i,j) = 0;
                    for (size_t k = 0; k < M; ++k)
                    {
                        result(i,j) += thisDouble(i,k) * otherDouble(k,j);
                    }
                }
            }
            
            return result;
        }

        // Оператор *= с преобразованием в double
        Matrix& operator*=(const Matrix& other)
        {
            *this = *this * other.toDouble(); // Преобразуем другую матрицу в double перед умножением
            return *this;
        }
       
        // Оператор ++
        Matrix& operator++() {
            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < M; j++)
                {
                    data[i][j]++;
                }
            }
            return *this;
        }
       
        // Метод вычисления определителя (только для квадратных матриц)
        T det() const
        {
            static_assert(N == M, "Determinant is only defined for square matrices");
           
            if constexpr (N == 1)
                return data[0][0];  
            else if constexpr (N == 2)
                return data[0][0] * data[1][1] - data[0][1] * data[1][0];
            else if constexpr (N == 3)
                return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
                    data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
                    data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
        }
       
        // Оператор ввода
        friend std::istream& operator>>(std::istream& in, Matrix& matrix)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    in >> matrix.data[i][j];
                }
            }
            return in;
        }
       
        // Оператор вывода
        friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    out << matrix.data[i][j] << ' ';
                }
                out << '\n';
            }
            return out;
        }
};
int main()
{
    // Конструктор копирования
    Matrix<short, 2, 2> m1;
    Matrix m2 = m1;
    std::cout << m2 << std::endl;
   
    // Оператор присваивания копированием
    Matrix<int, 3, 3> m3 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    Matrix<int, 3, 3> m4;
    m4 = m3;
    std::cout << m4 << std::endl;

    Matrix<int, 2, 2> m5 = {
        {10, 20},
        {30, 40}
    };
    Matrix<float, 2, 2> m6= {
        {1.2, 2.5},
        {3.1, 4.7}
    };
    Matrix<int, 2, 2> m7 = {
        {15, 25},
        {35, 45}
    };

    // Оператор сложения
    Matrix m8 = m5 + m6;
    std::cout << "1) m5 + m6\n" << m8;

    // Оператор умножения
    //Matrix<int, 2, 2> m8 = m5 * m6;
    //std::cout << "m5 * m6 =\n" << m8;

    // Оператор += для матриц разного типа
    std::cout << "3.1) m5 += m6\n" << (m5+=m6);

    // Оператор += для матриц одного типа
    std::cout << "3.2) m5 += m7\n" << (m5+=m7);

    // Оператор *=
    //std::cout << "4) m5 *= m5 =\n" << (m5*=m6);

    // Оператор ++
    std::cout << "5) ++m1\n" << ++m1;

    // Оператор доступа к элементу по индексу
    m3(0,0) = 100;
    std::cout << "6) m3(0,0) = 100\n" << m3;

    // Метод вычисления определителя
    std::cout << "7) det m3\n" << m3.det() << std::endl;
    
    /* Оператор ввода и вывода
    Matrix<int, 2, 2> m9;
    std::cout << "Введите элементы матрицы (через пробел или Enter):\n";
    std::cin >> m9;
    std::cout << m9;*/
}