/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class PlayingBaseState.
*/

#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>
#include <src/states/PlayingState.hpp>
#include <src/Gamemodes/Gamemodes.hpp>
#include <src/Gamemodes/Normalmode.hpp>
#include <src/Gamemodes/Hardmode.hpp>

PlayingState::PlayingState(StateMachine* sm) noexcept
    : BaseState{sm}
{

}

void PlayingState::enter(std::shared_ptr<World> _world, std::shared_ptr<Bird> _bird, int score) noexcept
{
    world = _world;
    
    if (_bird == nullptr)
    {
        bird = std::make_shared<Bird>(
            Settings::VIRTUAL_WIDTH / 2 - Settings::BIRD_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 2 - Settings::BIRD_HEIGHT / 2,
            Settings::BIRD_WIDTH, Settings::BIRD_HEIGHT
        );
    }
    else
    {
        bird = _bird;
    }
}

void PlayingState::handle_inputs(const sf::Event& event) noexcept
{
    Settings::gamemode->handle_input(event, bird);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        state_machine->change_state("pause_state", get_world(), get_bird(), get_score());
    }
}


void PlayingState::update(float dt) noexcept
{
    bird->update(dt);
    world->update(dt);

    auto powerup = world->get_powerup();

    if (powerup != nullptr)
    {
        if (bird->get_collision_rect().intersects(powerup->get_collision_rect()))
        {
            powerup->activate();
        }
    }

    bool should_collide = powerup == nullptr || !powerup->is_active();
    std::cout<<std::boolalpha<<should_collide<<std::endl;
    if (should_collide && world->collides(bird->get_collision_rect()))
    {
        Settings::sounds["explosion"].play();
        Settings::sounds["hurt"].play();
        state_machine->change_state("count_down", world, bird);
        return;
    }

    if (world->update_scored(bird->get_collision_rect()))
    {
        ++score;
        Settings::sounds["score"].play();
    }
}

void PlayingState::render(sf::RenderTarget& target) const noexcept
{
    world->render(target);
    bird->render(target);
    render_text(target, 20, 10, "Score: " + std::to_string(score), Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White);
}

std::shared_ptr<World> PlayingState::get_world() const noexcept
{
    return world;
}

std::shared_ptr<Bird> PlayingState::get_bird() const noexcept
{
    return bird;
}

int PlayingState::get_score() const noexcept
{
    return score;
}