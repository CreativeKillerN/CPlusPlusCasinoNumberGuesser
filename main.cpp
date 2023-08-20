#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

const int windowSize = 300;
const int gridSize = windowSize / 3;

int main() {
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Tic Tac Toe");
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape background(sf::Vector2f(windowSize, windowSize));
    sf::Color colorTop(0, 128, 128);
    sf::Color colorBottom(0, 64, 64);
    background.setFillColor(colorTop);
    background.setOutlineThickness(0);
    background.setPosition(0, 0);

    sf::RectangleShape lines[4];
    for (int i = 0; i < 4; ++i) {
        lines[i].setSize(sf::Vector2f(windowSize, 5));
        lines[i].setFillColor(sf::Color::Black);
    }
    lines[0].setPosition(gridSize, 0);
    lines[1].setPosition(2 * gridSize, 0);
    lines[2].setRotation(90);
    lines[2].setPosition(0, gridSize);
    lines[3].setRotation(90);
    lines[3].setPosition(0, 2 * gridSize);

    sf::CircleShape oShape(gridSize / 2 - 10);
    oShape.setFillColor(sf::Color::Transparent);
    oShape.setOutlineColor(sf::Color::Blue);
    oShape.setOutlineThickness(10);

    sf::RectangleShape xShape(sf::Vector2f(gridSize - 20, gridSize - 20));
    xShape.setFillColor(sf::Color::Transparent);
    xShape.setOutlineColor(sf::Color::Red);
    xShape.setOutlineThickness(10);

    char board[3][3] = { { ' ', ' ', ' ' }, { ' ', ' ', ' ' }, { ' ', ' ', ' ' } };
    bool playerTurn = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (playerTurn) {
                    int row = event.mouseButton.y / gridSize;
                    int col = event.mouseButton.x / gridSize;
                    if (board[row][col] == ' ') {
                        board[row][col] = 'X';
                        playerTurn = false;
                    }
                }
            }
        }

        if (!playerTurn) {
            // Basic AI making random moves
            while (true) {
                int row = rand() % 3;
                int col = rand() % 3;
                if (board[row][col] == ' ') {
                    board[row][col] = 'O';
                    playerTurn = true;
                    break;
                }
            }
        }

        window.clear();
        window.draw(background);
        for (int i = 0; i < 4; ++i) {
            window.draw(lines[i]);
        }

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (board[row][col] == 'X') {
                    xShape.setPosition(col * gridSize + 10, row * gridSize + 10);
                    window.draw(xShape);
                } else if (board[row][col] == 'O') {
                    oShape.setPosition(col * gridSize + 10, row * gridSize + 10);
                    window.draw(oShape);
                }
            }
        }

        window.display();
    }

    return 0;
}
