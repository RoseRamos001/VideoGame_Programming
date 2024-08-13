// PowerUp.hpp
#pragma once

#include <SFML/Graphics.hpp>

class PowerUp
{
public:
    PowerUp(float _x, float _y) noexcept;

    void update(float dt) noexcept;
    
    void render(sf::RenderTarget& target)  noexcept;
    
    sf::FloatRect get_collision_rect() const noexcept;
    
    bool is_active() const noexcept;
        
    void activate() noexcept;   
    
    void reset(float _x, float _y) noexcept;


private:
    float x;
    float y;
    float width;
    float height;
    sf::Sprite sprite;
    bool active{false};
    float timer{0.f};

};
