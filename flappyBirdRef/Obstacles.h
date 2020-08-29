#pragma once
#include <string>
#include <cmath>

#include "DrawableEntity.h"
#include "Logging.h"
#include "Obstacle.h"
#include "ScoreTXT.h"

struct VAO_RETURN
{
	sf::VertexArray const* vao;
	const int VAO_SIZE;
	const float* transform;
};

/// <summary>
/// simple batch renderer (all the obstacles will be rendered in a single draw call)
/// Also responsible for moving all the obstacles to the left at once 
/// (esentially treating all the objects like 1 sprite)
/// </summary>
class Obstacles : public DrawableEntity, public Obstacle
{
private:
	//use Obstacle instead
	//Obstacle m_obstacle;

	sf::Vector2f m_windowSize;

	const int M_SPACING = 400;

	int lastCreatePos;
	int lastDeletePos;

	float m_transform;
public:
	Obstacles(const std::string& fileName, sf::Vector2f windowSize);

	//the speed at which the obstacles move to the left
	static float m_speed;

	//return the vertexArray so that you can do collision detection
	inline VAO_RETURN GetVao() const { return { &m_vao, M_VAO_SIZE, &m_transform }; };

private:

	// Inherited via DrawableEntity
	virtual void Update(sf::Time& deltaTime) override;
	virtual const sf::Drawable& GetDrawable() const override;
	virtual void Restart() override;
};

