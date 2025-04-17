#include <iostream>
#include <cmath>
#include <string>
#include <stdexcept>

class Rectangle
{
    private:  
        // Поля
        double r_width;
        double r_height;

    public:   
        // Конструктор по умолчанию
        Rectangle() : r_width(1), r_height(1) {}
        // Member Initializer List
        Rectangle(double width, double height): r_width(width), r_height(height) 
        {
            if (width <= 0 || height <= 0)
                std::cout << ("Ошибка: высота и ширина прямоугольника должны быть положительны");
        }

        // Методы
        double area_calculation()
        {
            return r_width * r_height;
        } 

        double perimeter_calculation()
        {
            return 2 * (r_width + r_height);
        }

        double length_of_diagonal_calculation()
        {
            return std::sqrt(r_width * r_width + r_height * r_height);
        }

        // Дополнительный метод для вывода всей информации о прямоугольнике сразу
        std::string info_about_rectangle()
        {
            return "Площадь прямоугольника равна: " + std::to_string(r_width * r_height) + "\n" +
                   "Периметр прямоугольника равен: " + std::to_string(2 * (r_width + r_height)) + "\n" +
                   "Длина диагонали прямоугольника равна: " + std::to_string(std::sqrt(r_width * r_width + r_height * r_height));
        }
};

int main()
{
    Rectangle rect1;
    std::cout << "Площадь прямоугольника равна: " << rect1.area_calculation() << std::endl;
    std::cout << "Периметр прямоугольника равен: " << rect1.perimeter_calculation() << std::endl;
    std::cout << "Длина диагонали прямоугольника равна: " << rect1.length_of_diagonal_calculation() << std::endl;
    std::cout << std::endl;

    Rectangle rect2(3.1, 4);
    std::cout << rect2.info_about_rectangle() << std::endl;
    std::cout << std::endl;
    // Ошибка  
    try
    {
        Rectangle rect3(1, -2); // Попытка создать невалидный прямоугольник
        rect3.info_about_rectangle(); // не выполнится если было исключение
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }   
    
    return 0;
}