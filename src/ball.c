#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL.h>

#include "ball.h"

Ball* Ball_new(Sprite* init_sprite, Vector init_speed) {
  const char* func_title = "Ball_new()";

  if (init_sprite == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : init_sprite appeared to be NULL!", func_title);
    return NULL;
  }

  Ball* ball = (Ball*)malloc(sizeof(Ball));

  ball->sprite   = init_sprite;
  ball->box      = Box_new(&(init_sprite->box->rect));
  ball->speed    = Vector_new_speed(init_speed);

  return ball;
}

bool Ball_destroy(Ball* ball) {
  const char* func_title = "Ball_destroy()";

  if (ball == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : ball appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_destroy(ball->sprite);
  result &= Box_destroy(ball->box);

  return result;
} 

bool Ball_render(SDL_Renderer* renderer, Ball* ball, bool render_sprite_box, bool render_box) {
  const char* func_title = "Ball_render()";

  if (ball == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : ball appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_render(renderer, ball->sprite, render_sprite_box);
  if (render_box) {
    result &= Box_render(renderer, ball->box);
  }
  return result;
}

bool Ball_move(Ball* ball, Vector diff) {
  const char* func_title = "Ball_move()";

  if (ball == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : ball appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_move(ball->sprite, diff);
  result &= Box_move(ball->box, diff);

  return result;
}

bool Ball_move_dt(Ball* ball, Vector speed, uint64_t delta_time) {
  const char* func_title = "Ball_move_dt()";

  if (ball == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : ball appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_move_dt(ball->sprite, speed, delta_time);
  result &= Box_move_dt(ball->box, speed, delta_time);

  return result;
}

bool Ball_set_x(Ball* ball, Fpoint* pivot, float x) {
  const char* func_title = "Ball_set_x()";

  if (ball == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : ball appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_set_x(ball->sprite, pivot, x);
  result &= Box_set_x(ball->box, pivot, x);

  return result;
}

bool Ball_set_y(Ball* ball, Fpoint* pivot, float y) {
  const char* func_title = "Ball_set_y()";

  if (ball == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : ball appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_set_y(ball->sprite, pivot, y);
  result &= Box_set_y(ball->box, pivot, y);

  return result;
}

bool Ball_set_xy(Ball* ball, Fpoint* pivot, Vector position) {
  const char* func_title = "Ball_set_xy()";

  if (ball == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : ball appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_set_xy(ball->sprite, pivot, position);
  result &= Box_set_xy(ball->box, pivot, position);

  return result;
}
