#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class Particle {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float animationSpeed;

    Particle(float x, float y, float targetX, float targetY, float globalAnimationSpeed);

    void update(float dt, sf::RenderWindow& window, std::vector<Particle>& particles);
    bool checkCollision(Particle& other);
    void resolveCollision(Particle& other);
};

#endif