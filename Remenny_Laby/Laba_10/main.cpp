#include <iostream>
#include <func.hpp>


int main()
{
	mt::Node* head; // Указатель на голову списка 
	mt::Make(head); // Создаем пустой список с фиктивным узлом 

    int x, n;
    std::cout << "Введите длину списка: "; std::cin >> n;
    std::cout << "Введите последовательность натуральных чисел: " << std::endl;

    for(int i=0;i<n;i++)
    {
        std::cin >> x;
        mt::Pushback(head, x); // Добавляем число в список
    }

    
    if (mt::IsPalindrome(head)) 
    {
        // Переходим к началу списка, пропуская фиктивный узел
        mt::Node* current = head->next; 
        mt::Node* prev = head; // Указатель на предыдущий узел для удаления

        // Удаляем простые числа
        while (current != nullptr)
        {
            if (mt::isPrime(current->data)) // Проверяем, является ли текущее значение простым
            {
                prev->next = current->next; // Соединяем предыдущий узел с следующим узлом   
                mt::Node* toDelete = current; // Узел, который мы удалим
                current = current->next; // Переход к следующему узлу после удаления
                delete toDelete; // Освобождаем память
            }
            else
            {
                prev = current; // Переход к следующему элементу
                current = current->next; // Переход к следующему узлу
            }
        }

        // Вернемся к новому началу списка для дублирования
        current = head->next;

        // Дублируем числа, оканчивающиеся на 0
        while (current != nullptr) 
        {
            if (current->data % 10 == 0) // Проверяем, если последняя цифра равна 0
            {
                mt::Node* newNode = new mt::Node{current->data, current->next}; 
                current->next = newNode; // Вставляем новый узел
                current = newNode->next; // Переходим к следующему узлу, который был вставлен
            } 
            else
            {
                current = current->next; // Переход к следующему узлу
            }
        }
    }

        
    
    else
    {
        //mt::Sort(head);
    }


	mt::Print(head);

	Clear(head); // Освобождаем память перед завершением программы
}