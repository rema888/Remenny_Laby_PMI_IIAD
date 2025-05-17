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
       
        // Конструктор копирования
        Matrix(const Matrix& other) 
        {
            for (size_t i = 0; i < N; ++i) 
            {
                for (size_t j = 0; j < M; ++j) 
                {
                    data[i][j] = other.data[i][j];
                }
            }
        }

        // Оператор присваивания копированием
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
        }

        Matrix(std::initializer_list<std::initializer_list<T>> init) // Позволяет инициализировать матрицу с помощью вложенных списков в фигурных скобках
                                                                     // Принимает std::initializer_list (список инициализации) вложенный в другой std::initializer_list 
                                                                     // Внешний список — строки матрицы. Внутренние списки — элементы каждой строки.
        {
            size_t i = 0; // Индекс строки
            for (auto& row : init) // Проходим по каждой строке в инициализаторе
                                   // auto — ключевое слово, позволяющее компилятору автоматически вывести тип переменной row на основе типа элементов в init
                                   // auto& row - автоматическая ссылка на строку из init
            {
                size_t j = 0; // Индекс столбца
                for (auto& value : row) // Проходим по каждому элементу в строке
                {
                    data[i][j] = value; // Записываем значение в матрицу
                    j++;
                }
                i++;
            }
        }

        // Оператор доступа по индексу (для измемения элементов)
        T& operator()(size_t row, size_t col)
        {
            if (row >= N || col >= M)
                throw std::out_of_range("Выход за размеры матрицы");    
            return data[row][col];
        }

        // Константная версия (для оператора умножения)
        const T& operator()(size_t row, size_t col) const
        {
            if (row >= N || col >= M)
                throw std::out_of_range("Выход за размеры матрицы");
            return data[row][col];
        }

        // Преобразование матрицы в double
        Matrix<double, N, M> toDouble() const // Метод возвращает новую матрицу с теми же размерами NxM, но с элементами типа double
                                              // Константный метод, т.к. не изменяет исходную матрицу
        {
            Matrix<double, N, M> result; // Создаётся новая матрица result типа double с размерами NxM (заполнена нулями конструктором по умолч.)
            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < M; j++)
                {
                    result(i, j) = static_cast<double>(data[i][j]);
                }
            }
            return result;
        }

        // Оператор сложения с преобразованием в double
        template <typename U> // Позволит складывать матрицы разных типов, U - тип второй матрицы 
        Matrix<double, N, M> operator+(const Matrix<U, N, M>& other) const // Оператор возвращает новую матрицу с элементами типа double
                                                                           // Константный метод, т.к. не изменяет исходные матрицы
        {
            // auto для автоматического определения типа переменной (Метод toDouble() возвращает Matrix<double, N, M>, значит thisDouble будет <double, N, M>)
            auto thisDouble =  (*this).toDouble(); // Преобразуем текущую матрицу (this) в double // Указатели используют -> для доступа к методам и полям. (*this).toDouble().
            auto otherDouble = other.toDouble(); // Преобразуем вторую матрицу (other) в  double
            
            Matrix<double, N, M> result; // Создаётся новая матрица result типа double для хранения суммы
            
            for (size_t i = 0; i < N; i++)
                for (size_t j = 0; j < M; j++)
                    result(i,j) = thisDouble(i,j) + otherDouble(i,j);
            
            return result;
        }

        
       
        // Нельзя изменить тип существующего объекта!!!!!
        // Вар 1 - Оператор += с преобразованием в double (создает новую матрицу)
        template <typename U>
        Matrix<double, N, M> operator+=(const Matrix<U, N, M>& other) 
        {
            auto result =  (*this).toDouble();
            auto otherDouble = other.toDouble();
            
            for (size_t i = 0; i < N; i++) 
                for (size_t j = 0; j < M; j++) 
                    result(i,j) += otherDouble(i,j);
            
            return result; // Но это уже не будет традиционным +=
        }
        
        // Вар 2 - Оператор += для  матриц одного типа
        Matrix<T, N, M>& operator+=(const Matrix<T, N, M>& other) 
        {
            for (size_t i = 0; i < N; i++)
                for (size_t j = 0; j < M; j++)
                    this->data[i][j] += other.data[i][j];
                
            return *this; // Возвращаем ссылку на текущую матрицу
        }
        
        // Оператор умножения
        template <typename U, size_t K>
        Matrix<double, N, K> operator*(const Matrix<U, M, K>& other)
        {

            auto thisDouble = this->toDouble();    // Преобразуем this в double
            auto otherDouble = other.toDouble();   // Преобразуем other в double

            Matrix<double, N, K> result;

            for (size_t i = 0; i < N; i++) 
            {
                for (size_t j = 0; j < K; j++) 
                {
                    result(i,j) = 0;  // Инициализация элемента
                    for (size_t k = 0; k < M; k++)
                        result(i,j) += (thisDouble(i,k) * otherDouble(k,j));  
                }
            }
            return result;
        }

        // Оператор *= для умножения матриц с совместимыми размерами
        Matrix<T, N, M>& operator*=(const Matrix<T, M, M>& other) 
        {
            Matrix<T, N, M> result;  // Временная матрица для результата
            
            for (size_t i = 0; i < N; i++) 
            {
                for (size_t j = 0; j < M; j++) 
                {
                    result(i, j) = 0;
                    for (size_t k = 0; k < M; k++)
                        result(i, j) += data[i][k] * other(k, j); // other константна, поэтому нужен константный метод
                }
            }
            
            for (size_t i = 0; i < N; i++) 
            {
                for (size_t j = 0; j < M; j++)
                    data[i][j] = result(i, j);
            }

            return *this;
        }
       
        // Оператор ++
        Matrix& operator++() 
        {
            for (size_t i = 0; i < N; i++)
                for (size_t j = 0; j < M; j++)
                    data[i][j]++;

            return *this;
        }
       
        // Метод вычисления определителя (только для квадратных матриц)
        T det() const
        {
            static_assert(N == M, "Детерминант вычисляется для матриц с одинаковым кол-вом строк и столбцов");
           
            if(N == 1)
                return data[0][0];  
            else if(N == 2)
                return data[0][0] * data[1][1] - data[0][1] * data[1][0];
            else if(N == 3)
                return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
                    data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
                    data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]); // разложили по первой строке 
        }
       
        // Оператор ввода
        friend std::istream& operator>>(std::istream& in, Matrix& matrix) 
        {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    in >> matrix.data[i][j];
                    
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
        {11, 20},
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
    Matrix<int, 2,3> m33 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    Matrix<int, 3, 3> m44 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    // Оператор сложения
    Matrix m8 = m5 + m6;
    std::cout << "1) m5 + m6\n" << m8;

    // Оператор умножения
    Matrix m9 = m5 * m6;
    std::cout << "2) m5 * m6\n" << m9;

    // Оператор += для матриц разного типа и одного размера 
    std::cout << "3.1) m5 += m6\n" << (m5+=m6);

    // Оператор += для матриц одного типа и размера
    std::cout << "3.2) m5 += m7\n" << (m5+=m7);

    // Оператор *= для матриц одного типа и размера
    std::cout << "4) m5 *= m7\n" << (m5*=m7);

    // Оператор ++
    std::cout << "5) ++m6\n" << ++m6;

    // Оператор доступа к элементу по индексу
    m3(0,0) = 100;
    std::cout << "6) m3(0,0) = 100\n" << m3;

    // Метод вычисления определителя
    std::cout << "7) det m3\n" << m3.det() << std::endl;
    
    // Оператор ввода и вывода
    Matrix<int, 3, 2> m10;
    std::cout << "8) Введите элементы матрицы (через пробел или Enter):\n";
    std::cin >> m10;
    std::cout << "m10:\n" << m10;
}