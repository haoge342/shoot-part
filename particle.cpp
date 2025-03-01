#include "particle.hpp"
#include <cmath>
#include <cstdlib>

Particle::Particle(float x, float y, float targetX, float targetY) {
    shape.setRadius(5);
    shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    shape.setPosition(x, y);

    // calculate the direction to the target
    sf::Vector2f direction(targetX - x, targetY - y);
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if(length != 0) {
        direction /= length;
    }

    float speed = 200.0f;
    velocity = direction * speed;
}

void Particle::update(float dt, sf::RenderWindow& window) {
    velocity.y += 9.8f * dt; // gravity
    shape.move(velocity * dt);

    // collision
    sf::Vector2u windowSize = window.getSize();

    if(shape.getPosition().x <= 0 || shape.getPosition().x + shape.getRadius() * 2 >= windowSize.x) {
        velocity.x = -velocity.x * 0.8f; // bounce and lose some energy
    }

    if(shape.getPosition().y <= 0 || shape.getPosition().y + shape.getRadius() * 2 >= windowSize.y) {
        velocity.y = -velocity.y * 0.6f; // bounce and lose some energy
    }
}