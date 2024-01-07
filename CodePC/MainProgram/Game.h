#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Balloon.h"
#include "Obstacle.h"
#include "Enemy.h"
#include <vector>
#include <random>
#include "Bullet.h"

#include <memory>

#include "Menu.h"

class Game
{
private:
	static const int WIDTH = 900;
	static const int HEIGHT = 600;

	int GameScore = 0;
	std::string scoreFilePath = " ../Images/gameScore.txt";
	std::vector<std::unique_ptr<Enemy>> enemies; 
	sf::Texture enemyTexture;

private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;

	Obstacle obstacle;
	Character character;
	Bullet bullet;
	
	std::unique_ptr<Balloon>(balloon);

	//Menu menu; //added

	void handleEvents();
	void update();
	void render();

	void updateEnemies();
	void updateBullets();
	void gameOverScreen();
	void registerScore(int ScoreToAppend);
	std::string readScore() const;

public:
	Game();
	void run(); 
	
};

