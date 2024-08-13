#include <src/Gamemodes/Gamemodes.hpp>
#include <src/Gamemodes/Normalmode.hpp>
#include <Settings.hpp>

    bool Normal::is_claping() const noexcept
    {
        return false;
    };
    void Normal::handle_input(const sf::Event& event, std::shared_ptr<Bird> bird) const noexcept
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            bird->jump();
        }
        
    };
    float Normal::log_gap_distance() noexcept
    {
        return Settings::LOGS_GAP;
    };
    float Normal::log_generation_time() noexcept
    {
        return Settings::TIME_TO_SPAWN_LOGS;
    };
    bool Normal::spawn_powerups() const noexcept
    {
        return false;
    }