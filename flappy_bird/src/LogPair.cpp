/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class LogPair.
*/

#include <Settings.hpp>
#include <src/LogPair.hpp>

LogPair::LogPair(float _x, float _y, bool _claping) noexcept
    : x{_x}, y{_y}, claping{_claping},
      top{x, y + Settings::LOG_HEIGHT, true},
      bottom{x, y + Settings::LOGS_GAP + Settings::LOG_HEIGHT, false}
{

}

bool LogPair::collides(const sf::FloatRect& rect) const noexcept
{
    return top.get_collision_rect().intersects(rect) || bottom.get_collision_rect().intersects(rect);
}

void LogPair::update(float dt) noexcept
{
    float dy;
    float top_y = top.get_y();
    float bot_y = bottom.get_y();
    x += -Settings::MAIN_SCROLL_SPEED * dt;
    dy = Settings::CLAPPING_SPEED * dt;

    if (claping)
    {
        if (top.get_collision_rect().intersects(bottom.get_collision_rect()))
        {
            sign *= -1;
        }
        if (bottom.get_y() - top.get_y() >= Settings::LOGS_GAP * 2)
        {
            sign *= -1;
        } 
        top_y += dy * sign;
        bot_y -= dy * sign;
    }
    
    top.update(x, top_y);
    bottom.update(x, bot_y);

}

void LogPair::render(sf::RenderTarget& target) const noexcept
{
    top.render(target);
    bottom.render(target);
}

bool LogPair::is_out_of_game() const noexcept
{
    return x < -Settings::LOG_WIDTH;
}

bool LogPair::update_scored(const sf::FloatRect& rect) noexcept
{
    if (scored)
    {
        return false;
    }

    if (rect.left > x + Settings::LOG_WIDTH)
    {
        scored = true;
        return true;
    }

    return false;
}

void LogPair::reset(float _x, float _y, bool _claping) noexcept
{
    x = _x;
    y = _y;
    scored = false;
    claping = _claping;
}