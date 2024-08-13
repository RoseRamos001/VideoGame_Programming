#pragma once

#include <src/Bird.hpp>
#include <src/World.hpp>
#include <src/states/BaseState.hpp>

class PauseState : public BaseState
{

public:
    PauseState(StateMachine* sm) noexcept;

    void enter(std::shared_ptr<World> paused_world, std::shared_ptr<Bird> paused_bird, int score) noexcept;

    void handle_inputs(const sf::Event& event) noexcept;
    
    void render(sf::RenderTarget& target) const noexcept;

private:

    std::shared_ptr<Bird> paused_bird;

    std::shared_ptr<World> paused_world;

    int score{0};
};