#include "Renderer.h"
#include "Player.h"

//I know that I will need to render at least 3 things at a time (player, score, game over text)
Renderer::Renderer(sf::Vector2f windowSize)
	:m_entities(std::vector<DrawableEntity*>()), m_clock(sf::Clock()), m_deltaTime(sf::Time()), m_windowSize(windowSize),
	m_player("E:\\pawel\\yt\\flappyBirdRef\\flappyBirdRef\\res\\images\\bird.png", sf::Vector2f(.07f, .07f), windowSize), 
	m_obstacles("E:\\pawel\\yt\\flappyBirdRef\\flappyBirdRef\\res\\images\\obstacle.png", windowSize),
	m_score(ScoreTXT())
{
	//this will be used for collision detection in the player
	m_player.SetObstacleVao(m_obstacles.GetVao());

	m_entities.push_back(&m_player);
	m_entities.push_back(&m_obstacles);
	m_entities.push_back(&m_score);


	//prepare the game over text
	if (!m_font.loadFromFile("E:\\pawel\\yt\\flappyBirdRef\\flappyBirdRef\\res\\fonts\\ARIAL.woff"))
	{
		WARNING("Could not load the font");
	}

	m_renderText.setFont(m_font);
	m_renderText.setString("YOU SUCK!!!!");
	m_renderText.setCharacterSize(50);
	m_renderText.setFillColor(sf::Color(255, 0, 0, 255));
	m_renderText.setStyle(sf::Text::Bold);
	m_renderText.setPosition((m_windowSize.x / 2) - (m_renderText.getLocalBounds().width / 2), 
		(m_windowSize.y / 2) - (m_renderText.getLocalBounds().height / 2));

	//init the audio buffer
	if (!m_buffer.loadFromFile("E:\\pawel\\yt\\flappyBirdRef\\flappyBirdRef\\res\\audio\\DUDE.wav"))
	{
		//error
	}
}

void Renderer::EventDispatch(sf::Event& ev)
{
	for (DrawableEntity* e : m_entities)
	{
		e->HandleEvent(ev);
	}

	if (ev.type == sf::Event::KeyReleased && (ev.key.code == sf::Keyboard::Key::Space)
		&& Player::isDead)
	{
		//restart the game		
		for (DrawableEntity* e : m_entities)
		{
			e->Restart();
		}

		Player::isDead = false;
	}
}

void Renderer::draw(sf::RenderWindow* window)
{
	//get the deltaTime
	m_deltaTime = m_clock.getElapsedTime();
	m_clock.restart();

	//go through all the entities and call the update function with the deltaTime
	for (DrawableEntity* e : m_entities)
	{
		e->Update(m_deltaTime);
		window->draw(e->GetDrawable());
	}

	//what to do when the player dies
	if (Player::isDead)
	{
		//play a sound
		if (m_sound.getStatus() != sf::SoundSource::Status::Playing)
		{
			m_sound.setBuffer(m_buffer);
			m_sound.play();
		}
		

		//test text
		window->draw(m_renderText);
	}
}