#include <src/Gamemodes/Gamemodes.hpp>
#include <src/Gamemodes/Hardmode.hpp>
#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>

    bool Hard::is_claping() const noexcept
    {
        int value = 0;
        value = std::rand() % 11;
        if (value % 5 == 0){
            return true;
        }
        return false;
    };
    void Hard::handle_input(const sf::Event& event, std::shared_ptr<Bird> bird) const noexcept
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            bird->jump();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                bird->set_vx(-Settings::BIRD_HORIZONTAL_SPEED);  //Chage bird vx to the left
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                bird->set_vx(Settings::BIRD_HORIZONTAL_SPEED);  //Change bird vx to the right
            }
    }
    };

    float Hard::log_gap_distance() noexcept
    {
        int value = 0;
        value = std::rand() % 11;
        if (value % 2 == 0)
        {
            return Settings::LOGS_GAP - 10;
        }
        return Settings::LOGS_GAP;
    };
    float Hard::log_generation_time() noexcept
    {
        int value = 0;
        value = std::rand() % 11;
        if (value % 3 == 0)
        {
            return Settings::TIME_TO_SPAWN_LOGS;
        }
        else if (value % 3 == 1)
        {
            return Settings::TIME_TO_SPAWN_LOGS + 1;
        }
        else
        {
            return Settings::TIME_TO_SPAWN_LOGS - 0.5 ; 
        }
    };

    bool Hard::spawn_powerups() const noexcept 
    {
        return true;
    };