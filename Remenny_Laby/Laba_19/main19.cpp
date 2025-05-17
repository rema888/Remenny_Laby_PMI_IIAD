#include <SFML/Graphics.hpp>
#include <random>
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 700), "Memory Challenge", sf::Style::Titlebar | sf::Style::Close);
    // Черный полупрозрачный прямоугольник длдя затемнения фона по окончании игры
    sf::RectangleShape overlay(sf::Vector2f(800, 700)); 
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
 
    // Настройки игры
    const int CARD_COUNT = 16;
    const int PAIRS_COUNT = CARD_COUNT / 2;
    const float CARD_WIDTH = 100.f;
    const float CARD_HEIGHT = 150.f;
    const float DIST_BETW_CARDS = 10.f; 
    const float BOARD_WIDTH = 4 * CARD_WIDTH + 3 * DIST_BETW_CARDS; // Ширина игрового поля: 4 карточки в ряд и 3 промежутка между ними
    const float BOARD_HEIGHT = 4 * CARD_HEIGHT + 3 * DIST_BETW_CARDS;
    const float BOARD_START_X = (800 - BOARD_WIDTH) / 2;  // Первая карточка будет рисоваться на X = 185, и всё поле окажется по центру
    const float BOARD_START_Y = (700 - BOARD_HEIGHT) / 2; // Первая карточка будет рисоваться на Y = 35

    // Загружаем шрифт
    sf::Font font;
    font.loadFromFile("Arial.ttf");

    // Таймер
    sf::Clock gameClock; 
    float timeLeft = 20.0f; // хранит оставшееся время 
    sf::Text timerText; // текст для отображения таймера
    timerText.setFont(font); 
    timerText.setCharacterSize(20); // размер символов
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10.f, 20.f);

    // Сообщения о победе 
    sf::Text winText;
    winText.setFont(font);
    winText.setString("Congratulations, you won!");
    winText.setCharacterSize(40);
    winText.setFillColor(sf::Color::Green);
    winText.setPosition(170, 250);

    // Сообщения о поражении
    sf::Text loseText;
    loseText.setFont(font);
    loseText.setString("Time's up! You lost!");
    loseText.setCharacterSize(40);
    loseText.setFillColor(sf::Color::Red);
    loseText.setPosition(220, 250);

    // Кнопка Play Again
    sf::RectangleShape playAgainButton(sf::Vector2f(200, 50));
    playAgainButton.setFillColor(sf::Color(100, 200, 100));
    playAgainButton.setPosition(300, 350);
    
    sf::Text playAgainText;
    playAgainText.setFont(font);
    playAgainText.setString("Play Again");
    playAgainText.setCharacterSize(30);
    playAgainText.setFillColor(sf::Color::White);
    playAgainText.setPosition(330, 355);

    // Цвета для карточек
    std::vector<sf::Color> cardColors = {
        sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow,
        sf::Color::Magenta, sf::Color::Cyan, sf::Color(255, 165, 0), sf::Color(128, 0, 128)
    };

    // Создаем вектор, в котором будем хранить пары цветов
    std::vector<sf::Color> pairs;
    for (int i = 0; i < PAIRS_COUNT; i++) 
    {
        pairs.push_back(cardColors[i]);
        pairs.push_back(cardColors[i]);
    }
    
    // Перемешиваем карточки 
    std::random_device rd; // Генератор случайных чисел
    std::shuffle(pairs.begin(), pairs.end(), rd); // rd нужен, чтобы обеспечить равномерное распределение (каждый элемент может попасть на любую позицию).

    // Создаем карточки
    std::vector<sf::RectangleShape> cards; // Вектор из карточек
    // Векторы булевые размером CARD_COUNT
    std::vector<bool> cardRevealed(CARD_COUNT, false); // Отслеживает, какие карточки в данный момент открыты 
    std::vector<bool> cardMatched(CARD_COUNT, false); // Отслеживает, какие карточки уже были сопоставлены

    // Настраиваем карточки
    for (int i = 0; i < CARD_COUNT; i++) 
    {
        sf::RectangleShape card(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
        int row = i / 4; // Определение строки
        int col = i % 4; // Определение столбца
        card.setPosition (BOARD_START_X + col * (CARD_WIDTH + DIST_BETW_CARDS), BOARD_START_Y + row * (CARD_HEIGHT + DIST_BETW_CARDS));
        card.setFillColor(sf::Color(70, 70, 70));
        cards.push_back(card); // Созданная карточка добавляется в вектор cards
    }

    // Игровые переменные
    int firstRevealed = -1; // Индекс первой открытой карточки, -1 если игрок ещё не открыл первую карточку
    int secondRevealed = -1; // Индекс второй открытой карточки, -1 если вторая карточка еще не выбрана
    int matchedPairs = 0; // Количество найденных пар
    bool gameWon = false;  // Флаг победы
    bool gameLost = false; // Флаг поражения
    bool waitingForFlipBack = false; // Задержка перед скрытием карточек (true, если игрок открыл две карточки, но они не совпали)
    float flipBackTime = 0.f; // Таймер для задержки перед скрытием карточек

    // Функция для сброса игры 
    // [&] — захват переменных по ссылке (все внешние переменные, используемые внутри лямбды, будут доступны для изменения) 
    auto resetGame = [&]() 
    {
        timeLeft = 20.0f;
        matchedPairs = 0;
        gameWon = false;
        gameLost = false;
        firstRevealed = -1;
        secondRevealed = -1;
        waitingForFlipBack = false;
        
        std::random_device rd;
        std::shuffle(pairs.begin(), pairs.end(), rd); 
        
        // Сбрасываем состояния карточек
        for (int i = 0; i < CARD_COUNT; i++) 
        {
            cardRevealed[i] = false; // Все карточки становятся закрытыми
            cardMatched[i] = false; // Все пары сбрасываются (не найдены)
        }
        
        gameClock.restart();
    };

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                
                 // Обработка кнопки Play Again
                if ((gameWon || gameLost)) 
                {
                    if (playAgainButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) // Попал ли курсор в кнопку "Play Again"
                                                                                            // getGlobalBounds() — получает прямоугольник кнопки (позиция + размер)
                                                                                            // contains(x, y) — проверяет, есть ли точка (x, y) внутри этого прямоугольника
                    {
                        resetGame();
                    }
                    continue; // Пропускает оставшуюся часть цикла обработки событий. Это предотвращает клики по карточкам, пока не нажата кнопка Play Again
                }
                
                 // Обработка кликов по карточкам (только если игра активна)
                if (!waitingForFlipBack && event.mouseButton.button == sf::Mouse::Left) // Если не ждем переворота карточек и нажата левая кнопка мыши
                {
                    for (int i = 0; i < CARD_COUNT; i++) // Перебираем все карточки
                    {
                        if (!cardMatched[i] && cards[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) // Карточка ещё не угадана и курсор находится над карточкой
                        {
                            if (!cardRevealed[i]) // Если карточка закрыта
                            {
                                if (firstRevealed == -1) // Если это первая карточка в текущем ходе
                                {
                                    firstRevealed = i; // Запоминаем индекс 1ой карточки
                                    cardRevealed[i] = true; // Открываем её
                                }
                                else if (secondRevealed == -1 && i != firstRevealed) // Если это вторая карточка и она не совпадает с первой
                                {
                                    secondRevealed = i; // Запоминаем индекс 2ой карточки
                                    cardRevealed[i] = true; // Открываем её

                                    if (pairs[firstRevealed] == pairs[secondRevealed]) // Если цвета карточек совпадают
                                    {
                                        cardMatched[firstRevealed] = true; // Помечаем их как угаданные
                                        cardMatched[secondRevealed] = true;
                                        matchedPairs++; // Увеличиваем счётчик угаданных пар
                                        timeLeft += 2.0f; // Добавляем в таймер 2 секунды за найденную пару

                                        firstRevealed = -1; // Сбрасываем индексы найденных карточек
                                        secondRevealed = -1;

                                        if (matchedPairs == PAIRS_COUNT) // Если количество полученных пар равно количеству всех возможных пар (8)
                                            gameWon = true;
                                    }
                                    else // Если карточки не совпали
                                    {
                                        waitingForFlipBack = true;
                                        flipBackTime = 1.0f; // Задержка 1 секунда перед закрытием
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // Обновление таймера
        if (!gameWon && !gameLost && !waitingForFlipBack) // Если игрок выиграл, проиграл или происходит задержка перед закрытием карточек - таймер не будет обновляться
        {
            timeLeft -= gameClock.restart().asSeconds(); // gameClock.restart() запускает отсчёт времени и вычитает прошедшее время из timeLeft = 20 секунд
            if (timeLeft <= 0.f) // Если время закончилось
            {
                timeLeft = 0.f; // Фиксируем 0 чтобы не уходить в отрицательные числа
                gameLost = true;
            }
        }

        // Обновление таймера для переворота карточек
        if (waitingForFlipBack) // Если игрок открыл 2 карточки и они не совпали
        {
            flipBackTime -= gameClock.restart().asSeconds();
            if (flipBackTime <= 0.f) // Если время задержки истекло
            {
                cardRevealed[firstRevealed] = false; // Закрываем карточки
                cardRevealed[secondRevealed] = false;
                firstRevealed = -1; // "Забываем" выбранные карточки
                secondRevealed = -1;
                waitingForFlipBack = false; // Отключение задержки
            }
        }

        // Обновление текста таймера
        timerText.setString("Time left: " + std::to_string(static_cast<int>(timeLeft)) + " sec.");

        // Отрисовка фона
        window.clear(sf::Color(30, 30, 30));

        // Рисуем карточки
        for (int i = 0; i < CARD_COUNT; ++i) 
        {
            if (cardRevealed[i] || cardMatched[i]) // Если карточка временно открыта или уже угадана
                cards[i].setFillColor(pairs[i]);
            else // Если карточка закрыта
                cards[i].setFillColor(sf::Color(70, 70, 70)); // Серая рубашка
            window.draw(cards[i]);
        }

        // Рисуем таймер
        window.draw(timerText);

        // Рисуем сообщения о победе/поражении и кнопку Play Again
        if (gameWon || gameLost) 
        {
            window.draw(overlay);
            if (gameWon)
                window.draw(winText);
            else
                window.draw(loseText);
                
            window.draw(playAgainButton);
            window.draw(playAgainText);
        }

        window.display();
    }
}