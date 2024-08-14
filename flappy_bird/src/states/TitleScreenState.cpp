/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class TitleScreenState.
*/

#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>
#include <src/states/TitleScreenState.hpp>
#include <src/Gamemodes/Hardmode.hpp>
#include <src/Gamemodes/Normalmode.hpp>

TitleScreenState::TitleScreenState(StateMachine* sm) noexcept
    : BaseState{sm}, world{std::make_shared<World>(false)}, game_mode_option{0}
{

}

void TitleScreenState::handle_inputs(const sf::Event& event) noexcept
{
if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            game_mode_option = 0;
        }
        
        if (event.key.code == sf::Keyboard::Down)
        {
            game_mode_option = 1;
        }
        
        if (event.key.code == sf::Keyboard::Enter)
        {
            if (game_mode_option == 0)
            {
                Settings::gamemode = std::make_shared<Normal>();
                state_machine->change_state("count_down", world);
            }
            else if (game_mode_option == 1)
            {
                Settings::gamemode = std::make_shared<Hard>();   
                state_machine->change_state("count_down", world);
            }
        }
    }
}

void TitleScreenState::update(float dt) noexcept
{
    world->update(dt);
}

void TitleScreenState::render(sf::RenderTarget& target) const noexcept 
{
    world->render(target);

    render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 3, "Flappy Bird", Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White, true);
    
        
    if (game_mode_option == 0)
    {

        render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 3 + 50, "Easy mode", Settings::BIG_TEXT_SIZE, "flappy", sf::Color::Red, true);
        
        render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 3 + 100, "Hard mode", Settings::MEDIUM_TEXT_SIZE, "flappy", sf::Color::White, true);
    
    }

    if(game_mode_option == 1)
    {

        render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 3 + 50, "Easy mode", Settings::MEDIUM_TEXT_SIZE, "flappy", sf::Color::White, true);
        
        render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 3 + 100, "Hard mode", Settings::BIG_TEXT_SIZE, "flappy", sf::Color::Red, true);
    }

    render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 3+150, "press enter to select...", Settings::MEDIUM_TEXT_SIZE, "flappy", sf::Color::White, true);
}