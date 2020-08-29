#include "Obstacles.h"
#include "Player.h"

float Obstacles::m_speed = 200.0f;

Obstacles::Obstacles(const std::string& fileName, sf::Vector2f windowSize)
	:Obstacle(fileName, 250, 100, 100, windowSize), m_windowSize(windowSize),
	lastCreatePos(windowSize.x + M_SPACING), lastDeletePos(100), m_transform(0.0f)
{
}

void Obstacles::Update(sf::Time& deltaTime)
{
	//move the obstacles to the left by the speed
	//this has to be done on the 
	if (!Player::isDead)
	{
		this->setPosition(this->getPosition().x - (m_speed * deltaTime.asSeconds()), 0);

		m_transform = this->getPosition().x;

		//create a new obstacle
		int currPos = (int)(std::abs(this->getPosition().x) + m_windowSize.x);

		if (lastCreatePos == currPos)
		{
			this->createObstacle(lastCreatePos);
			lastCreatePos += M_SPACING;
		}

		currPos = (int)(std::abs(this->getPosition().x) - m_windowSize.x);
		//deleting the obstacles
		if (currPos - lastDeletePos > M_SPACING)
		{
			lastDeletePos += M_SPACING;
			this->popObstacle();
			ScoreTXT::m_score += 1;
		}
	}
}

const sf::Drawable& Obstacles::GetDrawable() const
{
	return *this;
}

void Obstacles::Restart()
{
	//clear the VAO
	for (int i = 0; i < M_VAO_SIZE; i++)
	{
		m_vao[i] = sf::Vertex();
	}

	//reset the position
	this->setPosition(0, 0);
	lastCreatePos = m_windowSize.x + M_SPACING;
	lastDeletePos = 100;

	//reset the score
	ScoreTXT::m_score = 0;
}
