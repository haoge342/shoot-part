#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.hpp"
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float GLOBAL_ANIMATION_SPEED = 100.0f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Shoot Particles");
    std::vector<Particle> particles;
    std::vector<sf::Vertex> lineVertices;
    
    
    sf::Clock clock;

    //#region loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                const float SHRINK_FACTOR = 0.5f;
                float lengthFromMouseToStart = std::sqrt((WINDOW_WIDTH / 2 - event.mouseButton.x) * (WINDOW_WIDTH / 2 - event.mouseButton.x) + (WINDOW_HEIGHT - 10 - event.mouseButton.y) * (WINDOW_HEIGHT - 10 - event.mouseButton.y));
                
                if (lengthFromMouseToStart < 100) continue;

                particles.emplace_back(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 10, event.mouseButton.x, event.mouseButton.y, std::sqrt(lengthFromMouseToStart) * SHRINK_FACTOR, GLOBAL_ANIMATION_SPEED);
            }

            if (event.type == sf::Event::MouseMoved)
            {
                if (lineVertices.size() > 0)
                {
                    lineVertices.pop_back();
                    lineVertices.pop_back();
                }

                auto lineStart = sf::Vertex(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 10), sf::Color::White);
                auto lineEnd = sf::Vertex(sf::Vector2f(event.mouseMove.x, event.mouseMove.y), sf::Color::White);
                lineVertices.push_back(lineStart);
                lineVertices.push_back(lineEnd);
            }
        }

        float dt = clock.restart().asSeconds();

        for (auto &particle : particles)
        {
            particle.update(dt, window, particles);
        }

        window.clear();
        for (auto &particle : particles)
        {
            window.draw(particle.shape);
        }

        if (!lineVertices.empty())
        {
            window.draw(&lineVertices[0], lineVertices.size(), sf::Lines);
        }

        window.display();
    }
    //#endregion

    return 0;
}
