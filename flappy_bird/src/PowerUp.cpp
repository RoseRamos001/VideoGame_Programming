// PowerUp.cpp
#include <src/PowerUp.hpp>
#include <Settings.hpp>

PowerUp::PowerUp(float _x, float _y) noexcept
    : x{_x}, y{_y}, sprite{Settings::textures["star"]}
{
    sprite.setPosition(x, y);
  
}


void PowerUp::update(float dt) noexcept
{
    if (!active) return;
   
    timer -= dt;
    
    if (timer <= Settings::POWER_UP_DURATION)
    {
    
        active = false;

    }
    
}

sf::FloatRect PowerUp::get_collision_rect() const noexcept
{
    return sf::FloatRect{x, y, width, height};
}

bool PowerUp::is_active() const noexcept
{
    return active;
}

void PowerUp::activate() noexcept
{ 
    timer = Settings::POWER_UP_DURATION;
    active = true;   
}

void PowerUp::reset(float _x, float _y) noexcept
{
    x = _x;
    y = _y;
    sprite.setPosition(x, y);
    active = true;
    timer = Settings::POWER_UP_DURATION;
}

void PowerUp::render(sf::RenderTarget& target)  noexcept
{
    
    target.draw(sprite);
}