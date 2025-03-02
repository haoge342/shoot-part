#include "particle.hpp"
#include <cmath>
#include <cstdlib>

// MARK: constructor
Particle::Particle(float x, float y, float targetX, float targetY, float initialSpeed, float globalAnimationSpeed) {
    shape.setRadius(5);
    shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    shape.setPosition(x, y);

    animationSpeed = globalAnimationSpeed;

    // calculate the direction to the target
    sf::Vector2f direction(targetX - x, targetY - y);
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if(length != 0) {
        direction /= length;
    }

    velocity = direction * animationSpeed * initialSpeed;
}

// MARK: collision detection
bool Particle::checkCollision(Particle& other){
    float dx = shape.getPosition().x - other.shape.getPosition().x;
    float dy = shape.getPosition().y - other.shape.getPosition().y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if(distance < shape.getRadius() + other.shape.getRadius()) {
        // collision detected
        return true;
    }

    return false;
}

// MARK:  collision resolution
void Particle::resolveCollision(Particle& other) {
    sf::Vector2f delta = shape.getPosition() - other.shape.getPosition();
    
    float d = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (d > shape.getRadius() + other.shape.getRadius()) return; // too far

    if (d == 0) return; // avoid division by zero

    sf::Vector2f normal = delta / d;
    sf::Vector2f relativeVelocity = velocity - other.velocity;
    float speed = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

    if (speed > 0) return; // moving away

    float restitution = 0.7f;
    float impulse = ((1.0f + restitution) * speed) / 2.0f;

    if (std::abs(impulse) < 0.1f) return; // avoid tiny impulses

    velocity -= impulse * normal;
    other.velocity += impulse * normal;
}

void Particle::update(float dt, sf::RenderWindow& window, std::vector<Particle>& particles) {
    velocity.y += 9.8f * dt * animationSpeed; // gravity
    shape.move(velocity * dt);

    const float DAMPING_FACTOR = 0.6f;
    const float GROUND_FRICTION = 1.0f - 0.001f; // plz set it from 0.990 to 0.999

    // collision w/ window
    sf::Vector2u windowSize = window.getSize();

    if (shape.getPosition().x <= 0) {
        shape.setPosition(1, shape.getPosition().y);
        velocity.x = -velocity.x * DAMPING_FACTOR;
    }

    if (shape.getPosition().x + shape.getRadius() * 2 >= windowSize.x) {
        shape.setPosition(windowSize.x - shape.getRadius() * 2 - 1, shape.getPosition().y);
        velocity.x = -velocity.x * DAMPING_FACTOR;
    }

    if (shape.getPosition().y <= 0) {
        shape.setPosition(shape.getPosition().x, 1);
        velocity.y = -velocity.y * DAMPING_FACTOR;
    }

    // MARK: ground
    if (shape.getPosition().y + shape.getRadius() * 2 >= windowSize.y) {
        shape.setPosition(shape.getPosition().x, windowSize.y - shape.getRadius() * 2);

        // prevenet infinite bouncing
        if (std::abs(velocity.y) < 1.0f) {
            velocity.y = 0;
        }else{
            velocity.y = -velocity.y * DAMPING_FACTOR;
        }

        // ground friction
        velocity.x *= GROUND_FRICTION;
    }

    // collision w/ other particles
    for(Particle& other: particles) {
        if(&other == this) continue;

        if(checkCollision(other)){
            resolveCollision(other);
        }
    }
}