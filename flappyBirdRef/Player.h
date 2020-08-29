#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "Obstacles.h"
#include "DrawableEntity.h"
#include "Logging.h"

/// <summary>
/// Handles all of the player logic
/// moves the sprite around and responds to player input such as space release
/// </summary>
class Player : public DrawableEntity
{
private:
	//the sprite
	sf::Sprite m_sprite;

	//name of the texture files
	const std::string& m_fileName;
	sf::Texture m_texture;

	//player position
	sf::Vector2f m_position;
	sf::Vector2f m_initialPos;
	//initially the size is used to scale down the texture to the desired size
	//later it is the size of the sprite in pixels
	sf::Vector2f m_size;
	sf::Vector2f m_velocity;
	float m_rotation;

	//window data
	sf::Vector2f m_windowSize;

	sf::VertexArray const* m_vao;
	int M_VAO_SIZE;
	const float* m_transform;

	//audio for jumping
	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;

public:
	//whether you win or lose
	static bool isDead;

public:
	Player(const std::string& texture_fileName, sf::Vector2f size, sf::Vector2f windowSize); //position if the centre by default
	Player(const std::string& texture_fileName, sf::Vector2f size, sf::Vector2f pos, sf::Vector2f windowSize);

	//if you want to access the players position for collision as an example
	inline const sf::Vector2f GetPosition() const { return m_position; }
	//get the sprite for drawing in the renderer
	inline const sf::Sprite GetSprite() const { return m_sprite; };

	void SetObstacleVao(VAO_RETURN vao_struct);

private:
	void Init(); //this will load the texture in and prepare the sprite overall for drawing onto the screen

public:
	// Inherited via DrawableEntity
	virtual void Update(sf::Time& deltaTime) override;

	virtual const sf::Drawable& GetDrawable() const override;

	virtual void Restart() override;

	//event handling
	virtual void HandleEvent(sf::Event& ev) override;
};

