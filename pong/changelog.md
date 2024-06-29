# CHANGELOG
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [1.1.0] - 2024-06-29
### Added
- Basic AI implementation for the second player paddle.
- New variables in the `Pong` structure to calculate the ball's final position:
    - `float x_distance;` // x distance between the ball and the paddle
    - `float t;` // time it takes the ball to meet the paddle
    - `float final_y;` // calculation of the final position in y

### Changed
- The `update_pong` function was modified to add the AI logic.
