from typing import TypeVar
from gale.factory import Factory

import settings
from src.Ball import Ball
from src.Paddle import Paddle
from src.powerups.PowerUp import PowerUp


class StickyPaddle(PowerUp):
    """
    Power-up to catch an throw the balls.
    """

    def __init__(self, x: int, y: int) -> None:
        super().__init__(x, y, 0)
        # self.ball_factory = Factory(Ball)

    def take(self, play_state: TypeVar("PlayState")) -> None:
      
        play_state.paddle.is_sticky = True
        
        self.active = False

            
                