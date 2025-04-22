#include <iostream>

class MyVector
{
    int* m_arr;
    size_t m_size;
    size_t m_cap;

    public:

        MyVector()
        {
            m_size = 0;
            m_cap = 0;
            m_arr = nullptr;
        }

        MyVector(size_t size, int value)
        {
            m_arr = new int[size];
            m_cap = size;
            m_size = size;
        }

        ~MyVector()
        {
            if(m_arr != nullptr) // Если нам есть что удалить
                delete[] m_arr;
        }      

        void reserve(size_t cap)
        {
            if(m_size >= cap)
                return;
            m_cap = m_cap * 2 + 1;
            int* tmp = new int[m_cap];
            for(int i=0;i<m_size;i++)
                tmp[i] = m_arr[i];
            delete[] m_arr;
            m_arr = tmp;
        }

        void shrink_to_fit()
        {
            m_cap = m_size;
            int* tmp = new int[m_cap];
            for(int i=0;i<m_size;i++)
                tmp[i] = m_arr[i];
            delete[] m_arr;
            m_arr = tmp;
        }

        size_t size()
        {
            return m_size;
        }

        size_t capacity()
        {
            return m_cap;
        }

        void push_back(int value)
        {
            if(m_size + 1 <= m_cap)
            {
                m_arr[m_size] = value;
                m_size++;
                return;
            }

            m_cap = m_cap * 2 + 1;
            int* tmp = new int[m_cap];
            for(int i=0;i<m_size;i++)
                tmp[i] = m_arr[i];
            tmp[m_size] = value;
            delete[] m_arr;
            m_arr = tmp;
            m_size++;
        }

        int operator[](size_t index)
        {
            return m_arr[index];
        }
};

int main()
{
    MyVector mas;
    for(int i=0;i<100;i++)
    {
        mas.push_back(i);
        std::cout << mas[50] << std::endl;
        // std::cout << "Allocate " << mas.size() << " " << mas.capacity() << std::endl;
    }
}