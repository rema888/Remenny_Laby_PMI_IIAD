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
        mt::Node* current = head->next; // Возвращаемся к первому реальному узлу
        while (current != nullptr) 
        {
            // Проверяем, если последняя цифра равна 0
            if (current->data % 10 == 0) 
            {
                // Создаем новый узел и вставляем его после текущего узла
                mt::Node* newNode = new mt::Node{current->data, current->next}; 
                current->next = newNode; // Вставляем новый узел
                current = newNode; // Переходим к следующему узлу, который был вставлен
            } 
            else
            {
                // Переходим к следующему узлу
                current = current->next; 
            }
        }

        current = head->next; // Начинаем с первого реального узла
        mt::Node* prev = head; // Указатель на предыдущий узел

        while (current != nullptr)
        {
            // Проверяем, является ли текущее значение простым
            if (mt::hasPrime(head)) 
            {
                // Удаляем узел через указатель "prev"
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
    }

    
    else
    {
        std::cout << "Чилл";
    }


	mt::Print(head);

	Clear(head); // Освобождаем память перед завершением программы
}