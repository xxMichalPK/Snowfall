#include <SFML/Graphics.hpp>
#include <SnowFlake.hpp>
#include <cmath>
#include <vector>

#define DESPAWN_RADIUS 100
#define MAX_FLAKE_COUNT 2000
#define SPAWN_COUNT 10
#define VELOCITY_MULTIPLIER 0.05f

std::vector<SnowFlake*> flakes;

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(768, 480)), L"Snowfall v0.0.1", sf::Style::Default, settings);
    window.setFramerateLimit(120);
    srand(time(NULL));

    sf::Image icon;
    if (icon.loadFromFile("resources/icon.png"))
        window.setIcon(icon);
    
    // Load all 3 snow flake textures
    sf::Texture flakeTexture1, flakeTexture2, flakeTexture3;
    if (!flakeTexture1.loadFromFile("resources/flake1.png")) {
        sf::err() << "Failed to load snow flake image\n";
        return 1;
    }
    if (!flakeTexture2.loadFromFile("resources/flake2.png")) {
        sf::err() << "Failed to load snow flake image\n";
        return 1;
    }
    if (!flakeTexture3.loadFromFile("resources/flake3.png")) {
        sf::err() << "Failed to load snow flake image\n";
        return 1;
    }

    // Main application loop
    bool dragging = false;
    sf::Vector2f mouseStart, mouseEnd;
    float newXVelocity = 0.f, newYVelocity = 1.f;

    sf::RectangleShape arrowBase(sf::Vector2f(0, 2));
    arrowBase.setFillColor(sf::Color::Red);
    arrowBase.setOrigin(arrowBase.getGlobalBounds().getSize() / 2.f);

    sf::ConvexShape arrowHead(3);
    arrowHead.setPoint(0, sf::Vector2f(0.f, 0.f));
    arrowHead.setPoint(1, sf::Vector2f(0.f, 15.f));
    arrowHead.setPoint(2, sf::Vector2f(7.5f, 7.5f));
    arrowHead.setFillColor(sf::Color::Red);
    arrowHead.setOrigin(arrowHead.getGlobalBounds().getSize() / 2.f);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }

            if (event.type == sf::Event::Resized) {
                window.setView(sf::View(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(event.size.width, event.size.height))));
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    mouseStart = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    arrowBase.setPosition(mouseStart);
                    arrowHead.setPosition(mouseStart);
                    dragging = true;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    mouseEnd = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    newXVelocity = (mouseEnd.x - mouseStart.x) * VELOCITY_MULTIPLIER;
                    newYVelocity = (mouseEnd.y - mouseStart.y) * VELOCITY_MULTIPLIER;
                    if (!newXVelocity && !newYVelocity) newYVelocity = 0.3f;
                    for (SnowFlake* flake : flakes) {
                        flake->setVelocityX(newXVelocity);
                        flake->setVelocityY(newYVelocity);
                    }
                    arrowBase.setSize(sf::Vector2f(0.f, arrowBase.getSize().y));
                    dragging = false;
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                if (!dragging) continue;
                float dx = event.mouseMove.x - mouseStart.x;
                float dy = event.mouseMove.y - mouseStart.y;

                float arrowLength = sqrtf(powf(dx, 2) + powf(dy, 2));
                float rotation = atan2f(dy, dx);
                arrowBase.setSize(sf::Vector2f(arrowLength, arrowBase.getSize().y));
                arrowBase.setRotation(sf::radians(rotation));

                arrowHead.setPosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                arrowHead.setRotation(sf::radians(rotation));
            }
        }

        // If we are below the maximum flake count, spawn a new one, one at a time
        for (size_t i = 0; i < SPAWN_COUNT && flakes.size() < MAX_FLAKE_COUNT; i++) {
            float scale = 10.f / ((rand() % 15) + 10.f);
            float posX = (rand() % (window.getSize().x + 2 * DESPAWN_RADIUS)) - DESPAWN_RADIUS;
            float posY = (rand() % (window.getSize().y + 2 * DESPAWN_RADIUS)) - DESPAWN_RADIUS;
            int chosenTexture = rand() % 3;
            sf::Texture* texturePointer = NULL;
            switch (chosenTexture) {
                case 0:
                    texturePointer = &flakeTexture1;
                    break;
                case 1:
                    texturePointer = &flakeTexture2;
                    break;
                case 2:
                    texturePointer = &flakeTexture3;
                    break;
                default:
                    texturePointer = &flakeTexture1;
            }

            flakes.push_back(
                new SnowFlake(sf::Vector2f(posX, posY), scale, *texturePointer)
            );
            flakes.back()->setVelocityX(newXVelocity);
            flakes.back()->setVelocityY(newYVelocity);
        }

        window.clear(sf::Color::Black);

        for (size_t i = 0; i < flakes.size(); i++) {
            if (flakes[i]->getY() > window.getSize().y + DESPAWN_RADIUS || flakes[i]->getY() < -DESPAWN_RADIUS ||
                flakes[i]->getX() > window.getSize().x + DESPAWN_RADIUS || flakes[i]->getX() < -DESPAWN_RADIUS)
            {
                delete flakes[i];
                flakes.erase(flakes.begin() + i);
                continue;
            }

            float xAdd = flakes[i]->getVelocity().x * flakes[i]->getScale();
            float yAdd = flakes[i]->getVelocity().y * flakes[i]->getScale();
            flakes[i]->setPosition(sf::Vector2f(flakes[i]->getX() + xAdd, flakes[i]->getY() + yAdd));
            window.draw(*(flakes[i]));
        }

        if (dragging) {
            window.draw(arrowBase);
            window.draw(arrowHead);
        }

        window.display();
    }

    return 0;
}

void createFlake(sf::Vector2f position) {

}