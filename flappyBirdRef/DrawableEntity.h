#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/// <summary>
/// virtual class containing everything needed for drawing an entity
/// </summary>
class DrawableEntity
{
public:
	virtual void Update(sf::Time& deltaTime) = 0;
	virtual const sf::Drawable& GetDrawable() const = 0;
	
	virtual void Restart() {};

	virtual void HandleEvent(sf::Event& ev) {};
};

