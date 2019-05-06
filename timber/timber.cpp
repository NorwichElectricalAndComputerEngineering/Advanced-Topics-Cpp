// treeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include <sstream>

using namespace sf;

VideoMode vm(1920, 1080);
Time gameTimeTotal;

//create and open window for the game
RenderWindow window(vm, "Timber", Style::Fullscreen);
int score = 0;
bool paused = true;

float timeRemaining;
RectangleShape timeBar;
float timeBarStartWidth = 400;
float timeBarHeight = 80;
float timeBarWidthPerSecond;
bool beeActive = false;
float beeSpeed = 0.0f;
bool cloud1Active = false;
bool cloud2Active = false;
bool cloud3Active = false;
std::string levelName;
std::string playerName;
float cloud1Speed = 0.0f;
float cloud2Speed = 0.0f;
float cloud3Speed = 0.0f;
Font font;
sf::Text messageText;
sf::Text scoreText;
Sprite spriteBackground, player, tree, bee, cloud1, cloud2, cloud3;
void moveBeeAndClouds();

int main()
{
	//set resolution and create video mode object
	timeRemaining = 6.0f;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	messageText.setFont(font);
	scoreText.setFont(font);
	
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	messageText.setCharacterSize(100);
	scoreText.setCharacterSize(75);

	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(-(textRect.left + 1900/ 4.5f), -(1080 / 2.0f));
	scoreText.setOrigin(20, 20);
	Texture textureBackground, playerTexture, treeTexture, beeTexture, cloudTexture;
	textureBackground.loadFromFile("graphics/background.png");
	playerTexture.loadFromFile("graphics/player.png");
	player.setPosition(500, 500);
	player.setTexture(playerTexture);
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);
	treeTexture.loadFromFile("graphics/tree.png");
	beeTexture.loadFromFile("graphics/bee.png");
	cloudTexture.loadFromFile("graphics/cloud.png");
	bee.setTexture(beeTexture);
	cloud1.setTexture(cloudTexture);
	cloud2.setTexture(cloudTexture);
	cloud3.setTexture(cloudTexture);

	tree.setTexture(treeTexture);
	tree.setPosition(810, 0);
	bee.setPosition(0, 800);
	cloud1.setPosition(0, 0);
	cloud2.setPosition(0, 250);
	cloud3.setPosition(0, 500);

	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;	

	/*game loop*/
	while (window.isOpen()) {
		Clock clock;
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			paused = false;
			score = 0;
			timeRemaining = 5;
		}
		if (Keyboard::isKeyPressed(Keyboard::P)) {
			paused = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			player.setPosition(player.getPosition().x, player.getPosition().y - 1);
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			player.setPosition(player.getPosition().x, player.getPosition().y + 1);
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			player.setPosition(player.getPosition().x-1, player.getPosition().y);
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			player.setPosition(player.getPosition().x + 1, player.getPosition().y);
		}
		//draw the scene//

		window.clear();

			window.draw(spriteBackground);
			window.draw(cloud1);
			window.draw(cloud2);
			window.draw(cloud3);

			window.draw(tree);
			window.draw(player);
			window.draw(bee);
	
			if (!paused) {
				moveBeeAndClouds();
				std::stringstream ss;
				ss << "Score: " << score;
				scoreText.setString(ss.str());
				window.draw(scoreText);
				}
			else {
				messageText.setString("Press Enter to Start");
				scoreText.setString("Score: 0");
				window.draw(messageText);
				window.draw(scoreText);
			}
			window.draw(timeBar);
			window.display();
	}

	return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
void moveBeeAndClouds() {
	Clock clock;
	//regenerate screen
	Time dt = clock.restart();
	timeRemaining -= dt.asSeconds()*1000;
	if (timeRemaining < 0.0f) {
		timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
		paused = true;
		beeActive = false;
		cloud1Active = false;
		cloud2Active = false;
		cloud3Active = false;
	}
	timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
	//std::cout << timeRemaining<<"\n";

	if (!beeActive) {
		srand((int)time(0));
		beeSpeed = rand() % 200 + 200;

		srand((int)time(0));
		float height = rand() % 500 + 500;
		bee.setPosition(2000, height);
		beeActive = true;
	}
	else {
		bee.setPosition(bee.getPosition().x - beeSpeed * 1000* dt.asSeconds(), bee.getPosition().y);
		if (bee.getPosition().x < -100) {
			beeActive = false;
		}
	}

	if (!cloud1Active) {
		srand((int)time(0) * 10);
		cloud1Speed = (rand() % 200);
		float height = (rand() % 150);
		cloud1.setPosition(-200, height);
		cloud1Active = true;
	}
	else {
		cloud1.setPosition(cloud1.getPosition().x + (cloud1Speed * 100 * dt.asSeconds()), cloud1.getPosition().y);
		if (cloud1.getPosition().x > 1920) {
			cloud1Active = false;
		}
	}
	if (!cloud2Active) {
		srand((int)time(0) * 20);
		cloud2Speed = (rand() % 200);
		float height = (rand() % 150);
		cloud2.setPosition(-200, height);
		cloud2Active = true;
	}
	else {
		cloud2.setPosition(cloud2.getPosition().x + (cloud2Speed * 100 * dt.asSeconds()), cloud2.getPosition().y);
		if (cloud2.getPosition().x > 1920) {
			cloud2Active = false;
		}
	}if (!cloud3Active) {
		srand((int)time(0) * 30);
		cloud3Speed = (rand() % 200);
		float height = (rand() % 150);
		cloud3.setPosition(-200, height);
		cloud3Active = true;
	}
	else {
		cloud3.setPosition(cloud3.getPosition().x + (cloud3Speed * 100 * dt.asSeconds()), cloud3.getPosition().y);
		if (cloud3.getPosition().x > 1920) {
			cloud3Active = false;
		}
	}
}

