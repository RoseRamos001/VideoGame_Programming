#pragma once

#include <src/states/PlayingState.hpp>

class Gamemodes
{
private:
public:
    virtual ~Gamemodes() {};

    virtual bool is_claping() const noexcept = 0;
    virtual void handle_input(const sf::Event&, std::shared_ptr<Bird>) const noexcept = 0;
    virtual float log_gap_distance() noexcept = 0;
    virtual float log_generation_time() noexcept = 0;
    virtual bool spawn_powerups() const noexcept = 0;
};
