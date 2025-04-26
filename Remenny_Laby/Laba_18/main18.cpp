// Подключаем файл, содержащий функции для работы с графикой
#include <SFML/Graphics.hpp> 

int main()
{
    // Создаем окно для отрисовки графики
    // Конструктор класса RenderWindow принимает 2 аргумента - sf::VideoMode (устанавливает размер окна) и строка (заголовок окна)
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML window");
    // Создаем круг, прямоугольник и треугольник
    sf::CircleShape circle(100.f); // конструктор принимает 1 аргумент - радиус круга (в пикселях)
    sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f)); // sf::Vector2f - структура, содержащая два числа с плавающей точкой (x, y)
    sf::CircleShape triangle(80.f, 3); // представляем треугольник как круг с 3 вершинами, 1й аргумент - радиус описанной окружности
                                                                                        // 2й аргумент - количество вершин
    // setPosition позволяет сместить фигуру относительно системы коррдинат по x и y                                                                                    
    rectangle.setPosition(150,150);
    rectangle.setRotation(45); // поворот на 45 градусов
    rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2); // Функция setOrigin позволяет сместить начало с/к

    // Цвет фигуры
    circle.setFillColor(sf::Color::Magenta); // setFillColor - метод
    rectangle.setFillColor(sf::Color(10, 10, 250));
    triangle.setFillColor(sf::Color::Black);
    
    bool isLeftKeyPressed = false;
    while (window.isOpen()) // isOpen - метод, который проверяет что окно открыто (bool)
    {
        // Блок обработки событий
        sf::Event event; // обьект event - событие (нажать мышку, свернуть/растянуть окно)
        while (window.pollEvent(event)) // в цикле вытаскиваем каждое событие по одному
                                        // в функцию pollEvent передаем обьект event и результат это событие, которое будет записано в event
                                        // сама функция poll возвращает true (если есть событие) или false
        {
            if (event.type == sf::Event::Closed) // если наше событие - закрытие окна, то закрываем его
                window.close();
        }

        /* Функция isKeyPressed с параметром, в который можем установить нажатую кнопку
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Если произошло нажатие на кнопку
        {
            rectangle.setRotation(45); // задаем поворот абсолютно (1 раз только поворот)
        }*/

       
        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Если произошло нажатие на кнопку
        {
            rectangle.rotate(1); // у rectangle есть поле angle, и когда мы пишем rotate, то к angle добавляем аргумент 45гр.
        }*/
           
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Если произошло нажатие на кнопку
        {
            if(!isLeftKeyPressed) // Если кнопка ранее не была нажата
            {
                rectangle.rotate(10); // у rectangle есть поле angle, и когда мы пишем rotate, то к angle добавляем аргумент 45гр.
                isLeftKeyPressed = true; // говорим, что кнопка в данный момент нажата (пока держим клавишу)
            }       
        }
        else
        {
            isLeftKeyPressed = false; // когда отпустили клавишу
        }
        
        // Функция clear очищает окно (все в окне становится по умолчанию черным цветом(r,g,b,a = 0))
        window.clear(sf::Color(255,0,0));
        // Функция draw рисует фигуры
        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);
        // Метод display выведет фигуры на экран
        window.display();
    }
}