from typing import TypeVar
from gale.factory import Factory

import settings
from src.Ball import Ball
from src.Paddle import Paddle
from src.powerups.PowerUp import PowerUp


class ExplosiveBalls(PowerUp):
    """
    Power-up to catch an throw the balls.
    """

    def __init__(self, x: int, y: int) -> None:
        super().__init__(x, y, 7)
        # self.ball_factory = Factory(Ball)

    def take(self, play_state: TypeVar("PlayState")) -> None:
        
        for ball in play_state.balls:
            ball.is_explosive = True
        
        self.active = False

            
                