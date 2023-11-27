#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

enum class GameState { MainMenu, Difficulty, Help, ConfirmExit, ScenarioSelect };

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "PacMan");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Nie udalo sie zaladowac czcionki!" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Text grajText, pomocText, wyjdzText, difficultyText, helpText, confirmExitText, confirmExitYesText, confirmExitNoText;
    grajText.setFont(font);
    grajText.setString("Graj");
    grajText.setCharacterSize(30);
    grajText.setPosition(360, 200);

    pomocText.setFont(font);
    pomocText.setString("Pomoc");
    pomocText.setCharacterSize(30);
    pomocText.setPosition(340, 300);

    wyjdzText.setFont(font);
    wyjdzText.setString("Wyjdz");
    wyjdzText.setCharacterSize(30);
    wyjdzText.setPosition(340, 400);

    difficultyText.setFont(font);
    difficultyText.setString("Wybierz poziom trudnosci: \n1. Łatwy\n2. Średni\n3. Trudny");
    difficultyText.setCharacterSize(24);
    difficultyText.setPosition(250, 200);

    helpText.setFont(font);
    helpText.setString("Kierujemy zolta kulka(Pacman'em) pozerajac biale malutkie kulki. \n Poruszajac sie po labiryncie, nalezy unikac duszkow");
    helpText.setCharacterSize(24);
    helpText.setPosition(80, 200);

    confirmExitText.setFont(font);
    confirmExitText.setString("Czy na pewno chcesz opuscic gre?");
    confirmExitText.setCharacterSize(24);
    confirmExitText.setPosition(250, 200);

    confirmExitYesText.setFont(font);
    confirmExitYesText.setString("Tak");
    confirmExitYesText.setCharacterSize(30);
    confirmExitYesText.setPosition(360, 200);

    confirmExitNoText.setFont(font);
    confirmExitNoText.setString("Nie");
    confirmExitNoText.setCharacterSize(30);
    confirmExitNoText.setPosition(360, 300);

    sf::Text scenario1Text, scenario2Text;
    scenario1Text.setFont(font);
    scenario1Text.setString("Scenariusz 1");
    scenario1Text.setCharacterSize(24);
    scenario1Text.setPosition(300, 200);

    scenario2Text.setFont(font);
    scenario2Text.setString("Scenariusz 2");
    scenario2Text.setCharacterSize(24);
    scenario2Text.setPosition(300, 300);

    GameState currentState = GameState::MainMenu;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                switch (currentState) {
                case GameState::MainMenu:
                    if (grajText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        currentState = GameState::Difficulty;
                    }
                    else if (pomocText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        currentState = GameState::Help;
                    }
                    else if (wyjdzText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        currentState = GameState::ConfirmExit;
                    }
                    break;

                case GameState::Difficulty:
                    if (difficultyText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        currentState = GameState::ScenarioSelect;
                    }
                    break;

                case GameState::ScenarioSelect:
                    if (scenario1Text.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {                      
                        currentState = GameState::MainMenu;
                    }
                    else if (scenario2Text.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        currentState = GameState::MainMenu;
                    }
                    break;

                case GameState::Help:
                    currentState = GameState::MainMenu;
                    break;

                case GameState::ConfirmExit:
                    if (confirmExitYesText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        window.close(); 
                    }
                    else if (confirmExitNoText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        currentState = GameState::MainMenu; 
                    }
                    break;
                }
            }
        }

        window.clear();

        if (currentState == GameState::MainMenu) {
            window.draw(grajText);
            window.draw(pomocText);
            window.draw(wyjdzText);
        }
        else if (currentState == GameState::Difficulty) {
            window.draw(difficultyText);
        }
        else if (currentState == GameState::Help) {
            window.draw(helpText);
        }
        else if (currentState == GameState::ConfirmExit) {
            window.draw(confirmExitText);
            window.draw(confirmExitYesText);
            window.draw(confirmExitNoText);
        }
        else if (currentState == GameState::ScenarioSelect) {
            window.draw(scenario1Text);
            window.draw(scenario2Text);
        }

        window.display();
    }

    return 0;
}
