#ifndef __SNOWFLAKE_HPP__
#define __SNOWFLAKE_HPP__

#include <SFML/Graphics.hpp>

#define DEFAULT_FLAKE_RADIUS 10

class SnowFlake : public sf::Drawable {
    private:
        float m_PosX = 0;
        float m_PosY = 0;
        float m_VelocityX = 0.f;
        float m_VelocityY = 1.f;

        sf::Texture m_Texture;
        sf::RenderStates m_RenderStates;
        sf::VertexArray m_Verticies;
        float m_Scale = 1;
    
    public:
        SnowFlake(sf::Vector2f position, float scale, sf::Texture& texture);
        ~SnowFlake();

        float& getX() { return m_PosX; }
        float& getY() { return m_PosY; }
        sf::Vector2f getPosition() { return sf::Vector2f(m_PosX, m_PosY); }
        void setPosition(sf::Vector2f position);
        void setVelocityX(float velocity) { m_VelocityX = velocity; }
        void setVelocityY(float velocity) { m_VelocityY = velocity; }
        sf::Vector2f getVelocity() { return sf::Vector2f(m_VelocityX, m_VelocityY); }

        float& getScale() { return m_Scale; }
    
    private:
        void update();
    
    protected:
        void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};

#endif