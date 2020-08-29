#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <iostream>

#include "Logging.h"
#include "DrawableEntity.h"
#include "Player.h"
#include "Obstacles.h"
#include "ScoreTXT.h"
/// <summary>
/// Wrapper for drawing everything onto the screen
/// </summary>
class Renderer
{
private:
	std::vector<DrawableEntity*> m_entities;

	//used for calculating the deltaTime
	sf::Clock m_clock;
	sf::Time m_deltaTime;

	sf::Vector2f m_windowSize;

	//all entities being rendered
	Player m_player;
	Obstacles m_obstacles;
	ScoreTXT m_score;

	//for game over 
	sf::Text m_renderText;
	sf::Font m_font;

	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;

public:
	//this will initialize all the entities
	Renderer(sf::Vector2f windowSize);

	void EventDispatch(sf::Event& ev);
	void draw(sf::RenderWindow* window);
};

