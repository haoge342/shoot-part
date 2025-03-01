#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shoot Particles");
    std::vector<Particle> particles;
    sf::Clock clock;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed){
                particles.emplace_back(event.mouseButton.x, event.mouseButton.y, 400, 300);
            }
        }

        float dt = clock.restart().asSeconds();
        for (auto& particle : particles){
            particle.update(dt, window);
        }

        window.clear();
        for (auto& particle : particles){
            window.draw(particle.shape);
        }
        window.display();
    }

    return 0;
}
