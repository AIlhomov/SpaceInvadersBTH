#include "Enemy.h"

bool Enemy::getIsAlive() const
{
    return isAlive;
}

sf::Vector2f Enemy::getPosition() const
{
    return rectShape.getPosition();
}

void Enemy::setPosition(float x, float y)
{
    rectShape.setPosition(x, y);
}

Enemy::Enemy(float x, float y, const sf::Texture& texture, int firingDelay)
    : isAlive(true), speed(0.02f), frameCounter(0), gen(rd()), dis(100, 300), firingDelay(firingDelay)
{
    rectShape.setSize(sf::Vector2f(40.0f, 40.0f));
    rectShape.setPosition(x, y);
    rectShape.setTexture(&texture, true);
    rectShape.setFillColor(sf::Color(255, 12, 213));
    direction = 1; //Start moving right
}

void Enemy::move()
{
    if (this != nullptr) rectShape.move(speed * direction, 0.f);
}

void Enemy::changeDirection()
{
    direction *= -1; //Reverse
    rectShape.move(0.f, 20.f); //Move down
}

void Enemy::update(float deltaTime)
{
    if (this != nullptr) {
        move(); //Move the enemy


        //ADD SHOOTING HERE:
        // Increment the frame count for each enemy
        frameCounter += deltaTime;

        // Fire a bullet every slower frames
        //if (frameCounter >= slowerFrameRate * 500) {
        //    fireBullet();
        //    frameCounter = 0;  // Reset the frame count
        //}

        if (frameCounter >= firingDelay) {
            fireBullet();
            frameCounter = 0;  // Reset the frame count
        }

        // Update bullets
        float bulletSpeedDown = 5.f; // Bullets move down
        updateBullets(bulletSpeedDown);
    }
}

void Enemy::draw(sf::RenderWindow& window)
{
    if (this != nullptr && isAlive) {
        window.draw(rectShape);
        drawBullets(window);

    }


}

void Enemy::fireBullet()
{
    float fireSpeed = 0.02f;
    float bulletDamage = 1.f;
    Bullet bullet(rectShape.getPosition().x + rectShape.getSize().x / 2.f, rectShape.getPosition().y + rectShape.getSize().y, fireSpeed, bulletDamage);
    bullets.push_back(bullet);
}

void Enemy::updateBullets(float deltaTime)
{
    // Update each bullet's position
    for (auto& bullet : bullets) {
        bullet.update(deltaTime);
    }

    // Remove inactive bullets (out of bounds)
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& bullet) { return !bullet.isActive(); }),
        bullets.end());
}

void Enemy::drawBullets(sf::RenderWindow& window)
{
    for (const auto& bullet : bullets) {
        bullet.draw(window);
    }
}

const std::vector<Bullet>& Enemy::getBullets() const
{
    return bullets;
}

sf::FloatRect Enemy::getBounds() const
{
    return this->rectShape.getGlobalBounds();
}


// had to add something, can change later...
void Enemy::updateMovement()
{
    Entity::updateMovement();
}
