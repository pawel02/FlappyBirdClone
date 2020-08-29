#include "Player.h"
#include <iostream>
#include <filesystem>

bool Player::isDead = false;

Player::Player(const std::string& texture_fileName, sf::Vector2f size, sf::Vector2f windowSize)
	:m_sprite(sf::Sprite()), m_fileName(texture_fileName), m_position({ 200, windowSize.y / 2 }),
	m_initialPos({ 200, windowSize.y / 2 }), m_size(size),
	m_velocity(0.0f, 0.0f), m_rotation(0.0f), m_windowSize(windowSize)
{
	Init();
}



Player::Player(const std::string& texture_fileName, sf::Vector2f size, sf::Vector2f pos, sf::Vector2f windowSize)
	:m_sprite(sf::Sprite()), m_fileName(texture_fileName), m_position(pos), m_initialPos(pos), m_size(size), m_velocity(0.0f, 0.0f),
	m_rotation(0.0f), m_windowSize(windowSize)
{
	Init();
}

void Player::SetObstacleVao(VAO_RETURN vao_struct)
{
	m_vao = vao_struct.vao;
	M_VAO_SIZE = vao_struct.VAO_SIZE;
	m_transform = vao_struct.transform;
}

void Player::Init()
{
	//load the texture 
	if (!m_texture.loadFromFile(m_fileName))
	{
		namespace fs = std::filesystem;
		std::cout << "Current path is " << fs::current_path() << '\n';
		WARNING("There was an error in loading the texture from the file. Please make sure that the file path is valid");
	}

	m_texture.setSmooth(true);
	m_texture.setRepeated(false);

	//initializing the sprite
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(m_size);
	m_sprite.setPosition(m_position);

	//initially the size is used to scale down the texture to the desired size
	//later it is the size of the sprite in pixels
	m_size.x = m_sprite.getLocalBounds().width * m_size.x;
	m_size.y = m_sprite.getLocalBounds().height * m_size.y;

	//initialize the sound buffer
	if (!m_buffer.loadFromFile("E:\\pawel\\yt\\flappyBirdRef\\flappyBirdRef\\res\\audio\\bounce.wav"))
	{
		//error
	}
}

void Player::Update(sf::Time& deltaTime)
{
	//gravity for the player
	m_velocity.y += (0.4 * (deltaTime.asSeconds()));
	//move the player to the new position using the current velocity
	m_position.y += m_velocity.y * (deltaTime.asSeconds());
	m_position.y += m_velocity.y;

	//player hit the ground
	if (m_position.y > m_windowSize.y - m_size.y)
	{
		isDead = true;
		m_position.y = m_windowSize.y - m_size.y;
	}

	m_sprite.setPosition(m_position);

	//set the rotation
	m_rotation += m_velocity.y * 0.5f;
	if (m_rotation > 20.0f)
		m_rotation = 20.0f;
	if (m_rotation < -20.0f)
		m_rotation = -20.0f;

	m_sprite.setOrigin(m_size.x / 2, m_size.y / 2);
	m_sprite.setRotation(m_rotation);

	//do some collision detection

	for (int i = 0; i < 8; i += 4)
	{
		sf::FloatRect myRect = sf::FloatRect(
			(float)(*m_vao)[i].position.x + *m_transform,
			(float)(*m_vao)[i].position.y,

			(*m_vao)[i + 2].position.x + *m_transform,
			(*m_vao)[i + 2].position.y
		);

		if (m_sprite.getGlobalBounds().intersects(myRect))
		{
			isDead = true;
		}
	}
}

const sf::Drawable& Player::GetDrawable() const
{
	return m_sprite;
}

void Player::HandleEvent(sf::Event& ev)
{
	//Space bar was pressed
	if (ev.type == sf::Event::KeyReleased && (ev.key.code == sf::Keyboard::Key::Space)
		&& !isDead)
	{
		m_velocity.y = -0.1f;
		m_sound.setBuffer(m_buffer);
		m_sound.play();
	}
}

void Player::Restart()
{
	m_sprite.setPosition(m_initialPos);
	m_position = m_initialPos;
	m_velocity = { 0.0f, 0.0f };
}