"""
ISPPJ1 2024
Study Case: Breakout

Author: Alejandro Mujica
alejandro.j.mujic4@gmail.com

This file contains the class Paddle.
"""

import pygame

import settings
from src.Bullets import Bullet


class Paddle:
    def __init__(self, x: int, y: int) -> None:
        self.x = x
        self.y = y
        self.width = 64
        self.height = 16
        self.is_sticky = False
        self.canons_enable = False

        # By default, the blue paddle
        self.skin = 0

        # By default, the 64-pixels-width paddle.
        self.size = 1

        self.texture = settings.TEXTURES["spritesheet"]
        self.frames = settings.FRAMES["paddles"]

        # The paddle only move horizontally
        self.vx = 0

    def resize(self, size: int) -> None:
        self.size = size
        self.width = (self.size + 1) * 32

    def dec_size(self):
        self.resize(max(0, self.size - 1))

    def inc_size(self):
        self.resize(min(3, self.size + 1))

    def get_collision_rect(self) -> pygame.Rect:
        return pygame.Rect(self.x, self.y, self.width, self.height)

    def update(self, dt: float) -> None:
        next_x = self.x + self.vx * dt

        if self.vx < 0:
            self.x = max(0, next_x)
        else:
            self.x = min(settings.VIRTUAL_WIDTH - self.width, next_x)
          

    def render(self, surface: pygame.Surface) -> None:
        surface.blit(self.texture, (self.x, self.y), self.frames[self.skin][self.size])
        if self.canons_enable:
            self.render_cannon(surface)


    def render_cannon(self, surface: pygame.Surface) -> None:

        left_cannon_x = self.x  
        right_cannon_x = self.x + self.width - settings.TEXTURES["cannon"].get_width()
        cannon_y = self.y

        surface.blit(settings.TEXTURES["cannon"], (left_cannon_x, cannon_y))  # Cañon izquierdo
        surface.blit(settings.TEXTURES["cannon"], (right_cannon_x, cannon_y))  # Cañon derecho

    
