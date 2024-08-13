#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>
#include <src/states/PauseState.hpp>


PauseState::PauseState(StateMachine* sm) noexcept
    : BaseState{sm}
{

}

void PauseState::enter(std::shared_ptr<World> paused_world, std::shared_ptr<Bird> paused_bird, int score) noexcept
{
    this->paused_world = paused_world;
    this->paused_bird = paused_bird;
    this->score = score;
}

void PauseState::handle_inputs(const sf::Event& event) noexcept
{
     if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        state_machine->change_state("playing", paused_world, paused_bird, score);

    }
}

void PauseState::render(sf::RenderTarget& target) const noexcept
{
    paused_world->render(target);
    
    paused_bird->render(target);

    
    render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 3, "Paused...", Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White, true);
}