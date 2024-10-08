/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class World.
*/

#include <Settings.hpp>
#include <src/World.hpp>

World::World(bool _generate_logs) noexcept
    : generate_logs{_generate_logs}, background{Settings::textures["background"]}, ground{Settings::textures["ground"]},
      logs{}, rng{std::default_random_engine{}()}
{
    ground.setPosition(0, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);
    std::uniform_int_distribution<int> dist(0, 80);
    last_log_y = -Settings::LOG_HEIGHT + dist(rng) + 20;
    time_to_spawn_logs = Settings::TIME_TO_SPAWN_LOGS;
    time_to_spawn_powerups = Settings::TIME_TO_SPAWN_POWERUPS;
    powerup_spawn_timer = 0;
    
}

void World::reset(bool _generate_logs) noexcept
{
    generate_logs = _generate_logs;
    for (auto log_pair: logs)
    {
        log_factory.remove(log_pair);
    }
    logs.clear();
}

bool World::collides(const sf::FloatRect& rect) const noexcept
{
    if (rect.top + rect.height >= Settings::VIRTUAL_HEIGHT)
    {
        return true;
    }
    
    for (auto log_pair: logs)
    {
        if (log_pair->collides(rect))
        {
            return true;
        }
    }

    return false;
}

bool World::update_scored(const sf::FloatRect& rect) noexcept
{
    for (auto log_pair: logs)
    {
        if (log_pair->update_scored(rect))
        {
            return true;
        }
    }

    return false;
}

void World::update(float dt) noexcept
{
    if (generate_logs)
    {
        logs_spawn_timer += dt;

        if (logs_spawn_timer >= time_to_spawn_logs)
        {
            logs_spawn_timer = 0.f;

            std::uniform_int_distribution<int> dist{-20, 20};
            float y = std::max(-Settings::LOG_HEIGHT + 10, std::min(last_log_y + dist(rng), Settings::VIRTUAL_HEIGHT + 90 - Settings::LOG_HEIGHT));

            last_log_y = y;

            logs.push_back(log_factory.create(Settings::VIRTUAL_WIDTH, y, Settings::gamemode->is_claping()));
            time_to_spawn_logs = Settings::gamemode->log_generation_time();
        }     
    }

    if (Settings::gamemode != nullptr && Settings::gamemode->spawn_powerups() && powerup == nullptr){
        powerup_spawn_timer += dt;
        if (powerup_spawn_timer >= Settings::TIME_TO_SPAWN_POWERUPS)
            {
                powerup_spawn_timer = 0;
                powerup = PowerUp_factory.create(Settings::VIRTUAL_WIDTH, Settings::VIRTUAL_HEIGHT/2);
            }
    }

    background_x += -Settings::BACK_SCROLL_SPEED * dt;

    if (background_x <= -Settings::BACKGROUND_LOOPING_POINT)
    {
        background_x = 0;
    }

    background.setPosition(background_x, 0);

    ground_x += -Settings::MAIN_SCROLL_SPEED * dt;

    if (ground_x <= -Settings::VIRTUAL_WIDTH)
    {
        ground_x = 0;
    }

    ground.setPosition(ground_x, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);

    for (auto it = logs.begin(); it != logs.end(); )
    {
        if ((*it)->is_out_of_game())
        {
            auto log_pair = *it;
            log_factory.remove(log_pair);
            it = logs.erase(it);
            
        }
        else
        {
            (*it)->update(dt);
            ++it;
        }
    }
    if (powerup != nullptr)
    {
        powerup->update(dt);
        if (!powerup->is_in_game())
        {
            powerup = nullptr;
        }

        
    }
    
}

void World::render(sf::RenderTarget& target) const noexcept
{
    target.draw(background);

    for (const auto& log_pair: logs)
    {
        log_pair->render(target);
    }

    target.draw(ground);
    if (powerup != nullptr)
    {
        powerup->render(target);
    }
    
}
std::shared_ptr<PowerUp> World::get_powerup()
{
    return powerup;
}