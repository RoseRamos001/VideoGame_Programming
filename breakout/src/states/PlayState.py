"""
ISPPJ1 2024
Study Case: Breakout

Author: Alejandro Mujica
alejandro.j.mujic4@gmail.com

This file contains the class to define the Play state.
"""

import random

import pygame

from gale.factory import AbstractFactory
from gale.state import BaseState
from gale.input_handler import InputData
from gale.text import render_text
from src.Bullets import Bullet

import settings
import src.powerups


class PlayState(BaseState):
    def enter(self, **params: dict):
        self.level = params["level"]
        self.score = params["score"]
        self.lives = params["lives"]
        self.paddle = params["paddle"]
        self.balls = params["balls"]
        self.brickset = params["brickset"]
        self.live_factor = params["live_factor"]
        self.points_to_next_live = params["points_to_next_live"]
        self.points_to_next_grow_up = (
            self.score
            + settings.PADDLE_GROW_UP_POINTS * (self.paddle.size + 1) * self.level
        )
        self.powerups = params.get("powerups", [])

        self.bullets = [] #empty bullet list
        self.shoots_left = 0

        if not params.get("resume", False):
            self.balls[0].vx = random.randint(-80, 80)
            self.balls[0].vy = random.randint(-170, -100)
            settings.SOUNDS["paddle_hit"].play()

        self.powerups_abstract_factory = AbstractFactory("src.powerups")

    def update(self, dt: float) -> None:
        self.paddle.update(dt)

        for ball in self.balls:
            ball.update(dt)
            ball.solve_world_boundaries()

            # Check collision with the paddle
            if ball.collides(self.paddle) and not self.paddle.is_sticky:
                settings.SOUNDS["paddle_hit"].stop()
                settings.SOUNDS["paddle_hit"].play()
                ball.rebound(self.paddle)
                ball.push(self.paddle)
                
      
            #check collision w/ sticky paddle    
            if ball.collides(self.paddle) and self.paddle.is_sticky:
                ball.dif_left = ball.x - self.paddle.x
                ball.vx = 0
                ball.vy = 0
                ball.x = self.paddle.x + ball.dif_left
                ball.y = self.paddle.y - ball.height

                settings.SOUNDS["paddle_hit"].stop()
                settings.SOUNDS["paddle_hit"].play()
            
            if self.paddle.is_sticky and ball.vy == 0:
                ball.x = self.paddle.x + ball.dif_left
        
                

            # Check collision with brickset
            if not ball.collides(self.brickset):
                continue

            brick = self.brickset.get_colliding_brick(ball.get_collision_rect())

            if brick is None:
                continue
            
            
            if not ball.is_explosive:
                brick.hit()
                self.score += brick.score()
                ball.rebound(brick)
                
            if ball.is_explosive:
                ball.resized(ball.width + 10, ball.height + 10)
                brick.hit()
                self.score += brick.score()
                ball.is_explosive = False
            
            # Check earn life
            if self.score >= self.points_to_next_live:
                settings.SOUNDS["life"].play()
                self.lives = min(3, self.lives + 1)
                self.live_factor += 0.5
                self.points_to_next_live += settings.LIVE_POINTS_BASE * self.live_factor

            # Check growing up of the paddle
            if self.score >= self.points_to_next_grow_up:
                settings.SOUNDS["grow_up"].play()
                self.points_to_next_grow_up += (
                    settings.PADDLE_GROW_UP_POINTS * (self.paddle.size + 1) * self.level
                )
                self.paddle.inc_size()

            # Chance to generate two more balls
            if random.random() < 0.1:
                r = brick.get_collision_rect()
                self.powerups.append(
                    self.powerups_abstract_factory.get_factory("TwoMoreBall").create(
                        r.centerx - 8, r.centery - 8
                    )
                )
            #chance to generate the sticky paddle
            elif random.random() < 0.1:
                r = brick.get_collision_rect()
                self.powerups.append(
                    self.powerups_abstract_factory.get_factory("StickyPaddle").create(
                        r.centerx - 8, r.centery - 8
                    )
                )
                
            #chance to generate explosive balls
            elif random.random() < 0.1:
                r = brick.get_collision_rect()
                self.powerups.append(
                    self.powerups_abstract_factory.get_factory("ExplosiveBalls").create(
                        r.centerx - 8, r.centery - 8
                    )
                )

            #chance to generate dual cannon paddle
            elif random.random() < 0.1:
                r = brick.get_collision_rect()
                self.powerups.append(
                    self.powerups_abstract_factory.get_factory("DualCannon").create(
                        r.centerx - 8, r.centery - 8
                    )
                )        
                    
        # Removing all balls that are not in play
        self.balls = [ball for ball in self.balls if ball.active]

        self.brickset.update(dt)

        if not self.balls:
            self.lives -= 1
            if self.lives == 0:
                self.state_machine.change("game_over", score=self.score)
            else:
                self.paddle.dec_size()
                self.state_machine.change(
                    "serve",
                    level=self.level,
                    score=self.score,
                    lives=self.lives,
                    paddle=self.paddle,
                    brickset=self.brickset,
                    points_to_next_live=self.points_to_next_live,
                    live_factor=self.live_factor,
                )

        # Update powerups
        for powerup in self.powerups:
            powerup.update(dt)

            if powerup.collides(self.paddle):
                powerup.take(self)

        # Remove powerups that are not in play
        self.powerups = [p for p in self.powerups if p.active]
        
        #update cannon bullets
        for bullet in self.bullets:
            bullet.update(dt)
            if bullet.collides(self.brickset):
                brick = self.brickset.get_colliding_brick(bullet.get_collision_rect())
                if brick:
                    brick.hit()
                    self.score += brick.score()
                    bullet.active = False
        
        self.bullets = [b for b in self.bullets if b.active]
                

        # Check victorys
        if self.brickset.size == 1 and next(
            (True for _, b in self.brickset.bricks.items() if b.broken), False
        ):
            self.state_machine.change(
                "victory",
                lives=self.lives,
                level=self.level,
                score=self.score,
                paddle=self.paddle,
                balls=self.balls,
                points_to_next_live=self.points_to_next_live,
                live_factor=self.live_factor,
            )

    def render(self, surface: pygame.Surface) -> None:
        heart_x = settings.VIRTUAL_WIDTH - 120

        i = 0
        # Draw filled hearts
        while i < self.lives:
            surface.blit(
                settings.TEXTURES["hearts"], (heart_x, 5), settings.FRAMES["hearts"][0]
            )
            heart_x += 11
            i += 1

        # Draw empty hearts
        while i < 3:
            surface.blit(
                settings.TEXTURES["hearts"], (heart_x, 5), settings.FRAMES["hearts"][1]
            )
            heart_x += 11
            i += 1

        render_text(
            surface,
            f"Score: {self.score}",
            settings.FONTS["tiny"],
            settings.VIRTUAL_WIDTH - 80,
            5,
            (255, 255, 255),
        )

        self.brickset.render(surface)

        self.paddle.render(surface)

        for ball in self.balls:
            ball.render(surface)

        for powerup in self.powerups:
            powerup.render(surface)
        
        #bullets render
        for bullet in self.bullets:
            bullet.render(surface)

        if self.paddle.is_sticky:
            
            render_text(
            surface,
            f"Sticky Paddle",
            settings.FONTS["small"],
            settings.VIRTUAL_WIDTH / 2 - 60,
            settings.VIRTUAL_HEIGHT / 2 - 10,
            (255, 255, 255),
            )
            
            render_text(
            surface,
            f"Pulse enter to shoot the balls",
            settings.FONTS["tiny"],
            settings.VIRTUAL_WIDTH / 2 - 80,
            settings.VIRTUAL_HEIGHT / 2,
            (255, 255, 255),
            )
        
        if self.paddle.canons_enable:

            render_text(
            surface,
            "Dual Cannon",
            settings.FONTS["small"],
            20,  # Coordenada X para la esquina inferior izquierda
            settings.VIRTUAL_HEIGHT - 80,  # Coordenada Y ajustada para la primera línea
            (255, 255, 255),
            )

            render_text(
            surface,
            "Press F to shoot the bullets",
            settings.FONTS["tiny"],
            20,  # Coordenada X para la esquina inferior izquierda
            settings.VIRTUAL_HEIGHT - 60,  # Coordenada Y ajustada para la segunda línea
            (255, 255, 255),
            )

            render_text(
                surface,
                "(you have 3 shots)",
                settings.FONTS["tiny"],
                20,  # Coordenada X para la esquina inferior izquierda
                settings.VIRTUAL_HEIGHT - 40,  # Coordenada Y ajustada para la tercera línea
                (255, 255, 255),
                )

             

    def on_input(self, input_id: str, input_data: InputData) -> None:
        if input_id == "move_left":
            if input_data.pressed:
                self.paddle.vx = -settings.PADDLE_SPEED
            elif input_data.released and self.paddle.vx < 0:
                self.paddle.vx = 0
        elif input_id == "move_right":
            if input_data.pressed:
                self.paddle.vx = settings.PADDLE_SPEED
            elif input_data.released and self.paddle.vx > 0:
                self.paddle.vx = 0
        elif input_id == "pause" and input_data.pressed:
            self.state_machine.change(
                "pause",
                level=self.level,
                score=self.score,
                lives=self.lives,
                paddle=self.paddle,
                balls=self.balls,
                brickset=self.brickset,
                points_to_next_live=self.points_to_next_live,
                live_factor=self.live_factor,
                powerups=self.powerups,
            )

        #hit the balls if are stuck in the paddle
        elif input_id == "enter":
            for ball in self.balls:
                if ball.vy == 0:
                    ball.vx = random.randint(-80, 80)
                    ball.vy = random.randint(-170, -100)
                    self.paddle.is_sticky = False  


        #shoot the a pair of bullets
        elif input_id == "f" and input_data.pressed and self.paddle.canons_enable:
            left_bullet = Bullet(self.paddle.x, (self.paddle.y - settings.TEXTURES["cannon"].get_height()), True)
            right_bullet = Bullet(self.paddle.x + self.paddle.width, (self.paddle.y - settings.TEXTURES["cannon"].get_height()), False)
            self.bullets.append(left_bullet)
            self.bullets.append(right_bullet)
            self.shoots_left += 1
            if self.shoots_left >= 3:
                self.paddle.canons_enable = False



    
               


        

