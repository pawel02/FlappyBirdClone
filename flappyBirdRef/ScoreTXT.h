#pragma once
#include <SFML/Graphics.hpp>

#include <string>

#include "DrawableEntity.h"
#include "Logging.h"

class ScoreTXT : public DrawableEntity
{
private:
	sf::Font m_font;
	sf::Text m_renderText;

	std::string m_text;
public:
	ScoreTXT();

	static int m_score;

public:
	// Inherited via DrawableEntity
	virtual void Update(sf::Time& deltaTime) override;

	virtual const sf::Drawable& GetDrawable() const override;
};

