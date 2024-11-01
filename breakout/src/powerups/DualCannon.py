from typing import TypeVar
from gale.factory import Factory

import settings
from src.Ball import Ball
from src.Paddle import Paddle
from src.Bullets import Bullet
from src.powerups.PowerUp import PowerUp

class DualCannon(PowerUp):
    """
    A powerup that allows the paddle to shoot two bullets at once.

    """
    def __init__(self, x: int, y: int) -> None:
     super().__init__(x, y, 9)  

    def take(self, play_state: TypeVar("PlayState")) -> None:
       
        play_state.paddle.canons_enable = True
        self.active = False
        play_state.shoots_left = 0
