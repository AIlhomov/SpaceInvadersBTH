#ifndef ENEMY_H
#define ENEMY_H

#include "Bullet.h"
#include "Entity.h"
#include <vector>
#include <random>

class Enemy : public Entity {
private:
    bool isAlive;
    float speed;
    int direction; // 1 for right, -1 for left

    std::vector<Bullet> bullets;
    float frameCounter;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

    int firingDelay;
public:
    bool getIsAlive() const;
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);

    Enemy(float x, float y, const sf::Texture& texture, int firingDelay);

    void move();
    void changeDirection();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    // Create and fire a bullet
    void fireBullet();

    // Update bullets' positions and check for collisions
    void updateBullets(float deltaTime);

    // Draw bullets on the window
    void drawBullets(sf::RenderWindow& window);

    const std::vector<Bullet>& getBullets() const;


    sf::FloatRect getBounds() const;


    //forced to add as Entity became abstract
    void updateMovement() override;

};





#endif