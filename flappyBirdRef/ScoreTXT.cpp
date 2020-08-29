#include "ScoreTXT.h"

int ScoreTXT::m_score = 0;

ScoreTXT::ScoreTXT()
{
    m_text = "Score: " + std::to_string(m_score);

    //test text
    m_font;
    if (!m_font.loadFromFile("E:\\pawel\\yt\\flappyBirdRef\\flappyBirdRef\\res\\fonts\\ARIAL.woff"))
    {
        WARNING("Could not load the font");
    }
    m_renderText.setFont(m_font);
    m_renderText.setString(m_text);
    m_renderText.setCharacterSize(24);
    m_renderText.setFillColor(sf::Color(140, 114, 114, 255));
    m_renderText.setStyle(sf::Text::Bold);
}

void ScoreTXT::Update(sf::Time& deltaTime)
{
    if (std::to_string(m_score) != m_text.substr(7, m_text.size()))
    {
        m_text = "Score: " + std::to_string(m_score);
        m_renderText.setString(m_text);
    }
}

const sf::Drawable& ScoreTXT::GetDrawable() const
{
	// TODO: insert return statement here
    return m_renderText;
}