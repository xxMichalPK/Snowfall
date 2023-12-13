#include <SnowFlake.hpp>

SnowFlake::SnowFlake(sf::Vector2f position, float scale, sf::Texture& texture) : 
    m_PosX(position.x),
    m_PosY(position.y),
    m_Scale(scale),
    m_Texture(texture),
    m_Verticies(sf::PrimitiveType::Triangles, 6)
{
    m_RenderStates.texture = &texture;

    // Set the shape coordinates
    m_Verticies[0].position = sf::Vector2f(m_PosX, m_PosY);
    m_Verticies[1].position = sf::Vector2f(m_PosX, m_PosY + DEFAULT_FLAKE_RADIUS * 2 * m_Scale);
    m_Verticies[2].position = sf::Vector2f(m_PosX + DEFAULT_FLAKE_RADIUS * 2 * m_Scale, m_PosY + DEFAULT_FLAKE_RADIUS * 2 * m_Scale);
    m_Verticies[3].position = sf::Vector2f(m_PosX + DEFAULT_FLAKE_RADIUS * 2 * m_Scale, m_PosY + DEFAULT_FLAKE_RADIUS * 2 * m_Scale);
    m_Verticies[4].position = sf::Vector2f(m_PosX + DEFAULT_FLAKE_RADIUS * 2 * m_Scale, m_PosY);
    m_Verticies[5].position = sf::Vector2f(m_PosX, m_PosY);

    // Set the texture coordinates
    m_Verticies[0].texCoords = sf::Vector2f(0.f, 0.f);
    m_Verticies[1].texCoords = sf::Vector2f(0.f, texture.getSize().y);
    m_Verticies[2].texCoords = sf::Vector2f(texture.getSize().x, texture.getSize().y);
    m_Verticies[3].texCoords = sf::Vector2f(texture.getSize().x, texture.getSize().y);
    m_Verticies[4].texCoords = sf::Vector2f(texture.getSize().x, 0.f);
    m_Verticies[5].texCoords = sf::Vector2f(0.f, 0.f);
}

void SnowFlake::setPosition(sf::Vector2f position) {
    m_PosX = position.x;
    m_PosY = position.y;
    update();
}

void SnowFlake::update() {
    // Set the shape coordinates
    m_Verticies[0].position = sf::Vector2f(m_PosX, m_PosY);
    m_Verticies[1].position = sf::Vector2f(m_PosX, m_PosY + DEFAULT_FLAKE_RADIUS * 2 * m_Scale);
    m_Verticies[2].position = sf::Vector2f(m_PosX + DEFAULT_FLAKE_RADIUS * 2 * m_Scale, m_PosY + DEFAULT_FLAKE_RADIUS * 2 * m_Scale);
    m_Verticies[3].position = sf::Vector2f(m_PosX + DEFAULT_FLAKE_RADIUS * 2 * m_Scale, m_PosY + DEFAULT_FLAKE_RADIUS * 2 * m_Scale);
    m_Verticies[4].position = sf::Vector2f(m_PosX + DEFAULT_FLAKE_RADIUS * 2 * m_Scale, m_PosY);
    m_Verticies[5].position = sf::Vector2f(m_PosX, m_PosY);
}

void SnowFlake::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    target.draw(m_Verticies, m_RenderStates);
}

SnowFlake::~SnowFlake() {}