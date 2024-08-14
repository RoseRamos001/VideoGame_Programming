// PowerUp.cpp
#include <src/PowerUp.hpp>
#include <Settings.hpp>

PowerUp::PowerUp(float _x, float _y) noexcept
    : x{_x}, y{_y}, width{32}, height{32}, sprite{Settings::textures["star"]}
{
    
    sprite.setPosition(x, y);
  
}

void PowerUp::update(float dt) noexcept
{

    if (active)
    {
        timer -= dt;
    
        if (timer <= 0.f)
        {
    
            active = false;
            in_game = false;

        }
    
    }
    else
    {
        this->x -= Settings::MAIN_SCROLL_SPEED * dt;
        sprite.setPosition(x,y);
        
        if (this->x < -this->width)
        {
            in_game = false;
        }
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
    active = false;
    timer = Settings::POWER_UP_DURATION;
    in_game = true;
}

void PowerUp::render(sf::RenderTarget& target)  noexcept
{
    if (!active)
    {
        target.draw(sprite);
    }
}

bool PowerUp::is_in_game() const noexcept
{
    return in_game;
}
