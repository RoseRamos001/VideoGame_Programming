#pragma once
#include <src/Gamemodes/Gamemodes.hpp>
#include <src/Bird.hpp>
#include <src/World.hpp>
#include <src/PowerUp.hpp>
#include <src/Factory.hpp>

class Hard : public Gamemodes
{
private:

public:
    bool is_claping() const noexcept override;
    void handle_input(const sf::Event&, std::shared_ptr<Bird>) const noexcept override;
    float log_gap_distance() noexcept override;
    float log_generation_time() noexcept override;
    bool spawn_powerups() const noexcept override;
};