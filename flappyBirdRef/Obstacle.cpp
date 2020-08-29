#include "Obstacle.h"
#include "Obstacles.h"
Obstacle::Obstacle(const std::string& fileName, int gap, int obstacleWidth,
	int minHeight, sf::Vector2f windowSize)
	:m_fileName(fileName), m_gap(gap),m_obstacleWidth(obstacleWidth),m_minHeight(minHeight),
	m_windowSize(windowSize)
{
	srand((unsigned)time(0));

	//define the vertecies
	m_vao = sf::VertexArray(sf::Quads, M_VAO_SIZE);
	
	//create the texture
	if (!m_texture.loadFromFile(m_fileName))
	{
		WARNING("There was an error in loading the texture from the file. Please make sure that the file path is valid");
	}
	m_texture.setSmooth(true);
	m_texture.setRepeated(false);

	m_transform.translate(0,0);
}

void Obstacle::popObstacle()
{
	//move all the elements 1 position forwards
 	for (int i = 8; i < M_VAO_SIZE; i++)
	{
		m_vao[(i - 8)] = m_vao[i];
		m_vao[i] = sf::Vertex();
	}
}


//look at what I have done in the batch renderer for ref as well as
//https://www.sfml-dev.org/tutorials/2.1/graphics-vertex-array.php
void Obstacle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_vao, states);
}

void Obstacle::createObstacle(float xOffset)
{
	//based on the xOffset
	//find where the gap will be based on the vars
	//create the vertecies accordigly
	
	float randY = rand() % (((int)m_windowSize.y - m_minHeight - m_gap) - m_minHeight + 1) + m_minHeight;

	//need 8 vertecies (4 for each quad)
	std::vector<sf::Vertex> vertecies = std::vector<sf::Vertex>(8);

	//fill in the vertecies
	//top quad
	vertecies[0].position = sf::Vector2f(xOffset, 0);                      //top left
	vertecies[1].position = sf::Vector2f(xOffset + m_obstacleWidth, 0);    //top right
	vertecies[2].position = sf::Vector2f(xOffset + m_obstacleWidth, randY);//bottom right
	vertecies[3].position = sf::Vector2f(xOffset, randY);                  //bottom left

	//calc the % of the quad on to the screen (to make sure that you are not stretching the texture weirdly)
	float perc = randY / m_windowSize.y;
	float texHeight = 512 * perc;

	vertecies[0].texCoords = sf::Vector2f(0, texHeight);
	vertecies[1].texCoords = sf::Vector2f(89, texHeight);
	vertecies[2].texCoords = sf::Vector2f(89, 0);
	vertecies[3].texCoords = sf::Vector2f(0, 0);

	//bottom quad
	vertecies[4].position = sf::Vector2f(xOffset, randY + m_gap);
	vertecies[5].position = sf::Vector2f(xOffset + m_obstacleWidth, randY + m_gap);
	vertecies[6].position = sf::Vector2f(xOffset + m_obstacleWidth, m_windowSize.y);
	vertecies[7].position = sf::Vector2f(xOffset, m_windowSize.y);

	perc = (m_windowSize.y - (randY + m_gap)) / m_windowSize.y;
	texHeight = 512 * perc;

	vertecies[4].texCoords = sf::Vector2f(0, 0);
	vertecies[5].texCoords = sf::Vector2f(89, 0);
	vertecies[6].texCoords = sf::Vector2f(89, texHeight);
	vertecies[7].texCoords = sf::Vector2f(0, texHeight);

	//start writing when you find empty vertecies
	for (int i = 0; i < M_VAO_SIZE; i+=8)
	{
		if (m_vao[i].position.x == 0.0f)
		{
			m_vao[i] = vertecies[0];
			m_vao[i + 1] = vertecies[1];
			m_vao[i + 2] = vertecies[2];
			m_vao[i + 3] = vertecies[3];

			m_vao[i + 4] = vertecies[4];
			m_vao[i + 5] = vertecies[5];
			m_vao[i + 6] = vertecies[6];
			m_vao[i + 7] = vertecies[7];

			break;
		}
		
	}
}
