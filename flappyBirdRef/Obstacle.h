#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

#include "Logging.h"
/// <summary>
/// This will create all the obstacles with the required transform 
/// </summary>
class Obstacle : public sf::Drawable, public sf::Transformable
{

private:
	const std::string& m_fileName;

	int m_gap;           //minimum gap between top and bottom
	int m_obstacleWidth; //How wide the obstacles are
	int m_minHeight;     //the minium height of the obstacle from the top / bottom

	sf::Texture m_texture;
	sf::Transform m_transform;

protected:
	//array storing all of the vertex points for the obstacles
	sf::VertexArray m_vao;
	const int M_VAO_SIZE = 8 * 6;

	sf::Vector2f m_windowSize;

public:
	Obstacle(const std::string& fileName, int gap, int obstacleWidth,
		int minHeight, sf::Vector2f windowSize);

	//this will destroy the top and the bottom of the first obstacle in the array
	//and then creating a new one at the end of the list
	void popObstacle();

	//This will return two quads for the top and bottom obstacle
	//using the xOffset as the starting point
	void createObstacle(float xOffset);

	//inherited
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

