/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class Log.
*/

#include <Settings.hpp>
#include <src/Log.hpp>

Log::Log(float _x, float _y, bool _inverted) noexcept
    : x{_x}, y{_y}, inverted{_inverted}, sprite{Settings::textures["Log"]}
{
    if (inverted)
    {
        sprite.rotate(180.f);
    }
}

float Log::get_y() const noexcept
{
    return y;
}
sf::FloatRect Log::get_collision_rect() const noexcept
{
    if (!inverted)
    {
        return sf::FloatRect{x, y, Settings::LOG_WIDTH, Settings::LOG_HEIGHT};
    }

    return sf::FloatRect{x - Settings::LOG_WIDTH, y - Settings::LOG_HEIGHT, Settings::LOG_WIDTH, Settings::LOG_HEIGHT};
}

void Log::update(float _x, float _y) noexcept
{
    x = _x;
    y = _y;
    if (inverted)
    {
        x += Settings::LOG_WIDTH;
    }

    sprite.setPosition(x, y);
}

void Log::render(sf::RenderTarget& target) const noexcept
{
    target.draw(sprite);
}
