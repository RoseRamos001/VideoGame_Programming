import pygame
from typing import Any
import settings

class Bullet:
    def __init__(self, x: int, y: int, dir: bool) -> None:
        self.x = x       
        self.y = y    
        self.vy = -settings.BULLET_SPEED
        self.vx = 0

        self.texture = settings.TEXTURES["bullet"]
        self.width = self.texture.get_width()
        self.height = self.texture.get_height()
        
        self.active = True

    def get_collision_rect(self) -> pygame.Rect:
        return pygame.Rect(self.x, self.y, self.width, self.height)
    
    def collides(self, another: Any) -> bool:
        return self.get_collision_rect().colliderect(another.get_collision_rect())
    
    def update(self, dt: float) -> None:
       
        if self.active:
            self.vy = - settings.BULLET_SPEED
            self.y += self.vy * dt
        

        # Desactivar la bala si sale de la pantalla
        if self.y < 0 or self.y > settings.VIRTUAL_HEIGHT:
            self.active = False
    
    def render(self, surface: pygame.Surface) -> None:
    
            surface.blit(self.texture, (self.x, self.y))
 
