#state to select level

import pygame
from gale.state import BaseState
from gale.text import render_text
from gale.input_handler import InputData

import settings

class LevelSelectionState(BaseState):
    def enter(self) -> None:
        pass

    def on_input(self, input_id: str, input_data: InputData) -> None:
        pass

    def update(self, dt: float) -> None:
        pass

    def render(self, surface: pygame.Surface) -> None:
        surface.blit(settings.TEXTURES["background"], (0, 0))



        # Dibuja el menú