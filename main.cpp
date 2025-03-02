#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float GLOBAL_ANIMATION_SPEED = 100.0f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Shoot Particles");
    std::vector<Particle> particles;
    sf::Clock clock;

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
                particles.emplace_back(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 10, event.mouseButton.x, event.mouseButton.y, GLOBAL_ANIMATION_SPEED);
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
        window.display();
    }

    return 0;
}
