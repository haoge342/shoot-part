#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class Particle {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Particle(float x, float y, float targetX, float targetY);

    void update(float dt, sf::RenderWindow& window);
};

#endif