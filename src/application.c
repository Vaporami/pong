#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "application.h"
#include "sprite_data.h"
#include "sprite.h"
#include "vector.h"

#define SPRITE_SET_PAD 0
#define SPRITE_SET_RPAD 1
#define SPRITE_SET_BALL 2

Application* Application_new(void) {
  const char* func_title = "Application_new()";

  const uint32_t  WIDTH   = 1024;
  const uint32_t  HEIGHT  = 576;
  const char*     TITLE   = "Pong";

  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Creating a new application's instance...", func_title);

  Application* app = (Application*)malloc(sizeof(Application));
  if (app == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : malloc() failed!", func_title);
    return NULL;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Space for application was allocated successfully!", func_title);

  app->window = SDL_CreateWindow(TITLE, WIDTH, HEIGHT, 0);
  if (app->window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return NULL;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
	      "%s : Window was created successfully with the name %s and size of %dx%d", func_title, TITLE, WIDTH, HEIGHT);

  app->width = WIDTH;
  app->height = HEIGHT;

  app->renderer = SDL_CreateRenderer(app->window, NULL);
  if (app->renderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return NULL;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_GPU,
	      "%s : Renderer was created successfully with the use of %s API", func_title, SDL_GetRendererName(app->renderer));

  app->keyboard = SDL_GetKeyboardState(NULL);

  Sprite_data** data_set = (Sprite_data**)malloc(3 * sizeof(Sprite_data*));
  data_set[0] = Sprite_data_new_from_bmp(app->renderer, "./data/bmps/pad.bmp", NULL);
  data_set[1] = Sprite_data_new_from_bmp(app->renderer, "./data/bmps/rpad.bmp", NULL);
  data_set[2] = Sprite_data_new_from_bmp(app->renderer, "./data/bmps/ball.bmp", NULL);

  app->sprite_data_set = data_set;

  Sprite** sprite_set = (Sprite**)malloc(3 * sizeof(Sprite*));

  sprite_set[SPRITE_SET_PAD] = Sprite_new(data_set[0], Box_new(NULL));
  sprite_set[SPRITE_SET_RPAD] = Sprite_new(data_set[1], Box_new(NULL));
  sprite_set[SPRITE_SET_BALL] = Sprite_new(data_set[2], Box_new(NULL));

  app->sprite_set = sprite_set;

  Vector pad_speed = { .x = 0.0f, .y = 500.0f };
  app->pad = Pad_new(sprite_set[SPRITE_SET_PAD], pad_speed);

  Vector rpad_speed = { .x = 0.0f, .y = 500.0f };
  app->rpad = Pad_new(sprite_set[SPRITE_SET_RPAD], rpad_speed);

  Vector ball_speed = { .x = 550.0f, .y = 450.0f };
  app->ball = Ball_new(sprite_set[SPRITE_SET_BALL], ball_speed);

  Vector pad_init_pos = { .x = 100.0f, .y = app->height / 2 };
  Pad_set_xy(app->pad, &(app->pad->box->center), pad_init_pos);

  Vector rpad_init_pos = { .x = app->width - 100.0f, .y = app->height / 2 };
  Pad_set_xy(app->rpad, &(app->rpad->box->center), rpad_init_pos);

  Vector ball_init_pos = { .x = app->width / 2, .y = app->height / 2 };
  Ball_set_xy(app->ball, &(app->ball->box->center), ball_init_pos);

  app->must_update_on_input  = false;
  app->must_move_pad_up      = false;
  app->must_move_pad_down    = false;

  app->delta_time = 0;

  app->running = true;


  SDL_ShowWindow(app->window);
  return app;
}

void Application_destroy(Application* app) {
  for (int i = 0; i < 3; i++) {
    free(app->sprite_set[i]);
    free(app->sprite_data_set[i]);
  }
  SDL_DestroyRenderer(app->renderer);
  SDL_DestroyWindow(app->window);
}

bool Application_input_handling(Application* app) {
  if (app->keyboard[SDL_SCANCODE_W]) {
    app->must_move_pad_up = true;
  } else {
    app->must_move_pad_up = false;
  }

  if (app->keyboard[SDL_SCANCODE_S]) {
    app->must_move_pad_down = true;
  } else {
    app->must_move_pad_down = false;
  }

  app->must_update_on_input = app->must_move_pad_up || app->must_move_pad_down;
  return app->must_update_on_input;
}

bool Application_close(Application* app) {
  const char* func_title = "Application_close()";
  app->running = false;
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : intended quit call, exiting...", func_title);
  return false;
}

bool Application_event_handling(Application* app) {

  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      Application_close(app);
    } else if (event.type == SDL_EVENT_KEY_DOWN) {
      if (event.key.scancode == SDL_SCANCODE_Q) {
	Application_close(app);
      }
    }
  }

  return true;
} 

bool Application_update_on_input(Application* app) {
  const char* func_title = "Application_update_on_input()";

  if (app->must_move_pad_up) {
    app->pad->speed = (Vector){ .x = 0.0f, .y = -500.0f };
    if (!Pad_move_dt(app->pad, app->pad->speed, app->delta_time)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : Pad_move_dt returned false!", func_title);
      return false;
    }
  }

  if (app->must_move_pad_down) {
    app->pad->speed = (Vector){ .x = 0.0f, .y = 500.0f };
    if (!Pad_move_dt(app->pad, app->pad->speed, app->delta_time)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : Pad_move_dt returned false!", func_title);
      return false;
    }
  }

  return true;
}

bool Application_update_on_events(Application* app) {
  return app->running;
}

bool Application_Ball_react_to_collisions(Application* app) {
  const char* func_title = "Application_Ball_move()";

  if (app == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : app appeared to be NULL!", func_title);
    return false;
  }

  Fpoint ball_left_center = {
    .x = app->ball->box->rect.x,
    .y = app->ball->box->rect.y + (app->ball->box->rect.h / 2)
  };

  Fpoint ball_right_center = {
    .x = app->ball->box->rect.x + app->ball->box->rect.w,
    .y = app->ball->box->rect.y + (app->ball->box->rect.h / 2)
  };

  Fpoint ball_upper_center = {
    .x = app->ball->box->rect.x + (app->ball->box->rect.w / 2),
    .y = app->ball->box->rect.y
  };

  Fpoint ball_lower_center = {
    .x = app->ball->box->rect.x + (app->ball->box->rect.w / 2),
    .y = app->ball->box->rect.y + app->ball->box->rect.h
  };

  Fpoint pad_right_upper_corner = {
    .x = app->pad->box->rect.x + app->pad->box->rect.w,
    .y = app->pad->box->rect.y
  };

  Fpoint pad_right_lower_corner = {
    .x = app->pad->box->rect.x + app->pad->box->rect.w,
    .y = app->pad->box->rect.y + app->pad->box->rect.h
  };

  Fpoint rpad_left_upper_corner = {
    .x = app->rpad->box->rect.x,
    .y = app->rpad->box->rect.y
  };

  Fpoint rpad_left_lower_corner = {
    .x = app->rpad->box->rect.x,
    .y = app->rpad->box->rect.y + app->pad->box->rect.h
  };

  bool ball_touch_pad_x = ball_left_center.x <= pad_right_upper_corner.x;
  bool ball_touch_pad_y = pad_right_upper_corner.y < ball_left_center.y && ball_left_center.y < pad_right_lower_corner.y;
  bool ball_touch_pad   = ball_touch_pad_x && ball_touch_pad_y;

  bool ball_touch_rpad_x = ball_right_center.x >= rpad_left_upper_corner.x;
  bool ball_touch_rpad_y = rpad_left_upper_corner.y < ball_right_center.y && ball_right_center.y < rpad_left_lower_corner.y;
  bool ball_touch_rpad   = ball_touch_rpad_x && ball_touch_rpad_y;

  bool ball_touch_win_ceiling = ball_upper_center.y <= 0;
  bool ball_touch_win_floor   = ball_lower_center.y >= app->height;

  if (ball_touch_pad && app->ball->speed.x < 0) {
    app->ball->speed.x *= -1;
  }

  if (ball_touch_rpad && app->ball->speed.x > 0) {
    app->ball->speed.x *= -1;
  }

  if (ball_touch_win_ceiling && app->ball->speed.y < 0) {
    app->ball->speed.y *= -1;
  }

  if (ball_touch_win_floor && app->ball->speed.y > 0) {
    app->ball->speed.y *= -1;
  }
}

bool Application_update(Application* app) {
  Application_Ball_react_to_collisions(app);
  Ball_move_dt(app->ball, app->ball->speed, app->delta_time);

  if (app->rpad->box->rect.y != app->ball->box->rect.y) {
    Pad_set_y(app->rpad, &(app->rpad->box->center), app->ball->box->center.y);
  }

  return true;
}

bool Application_render(Application* app) {
  const char* func_title = "Application_render()";

  if (!SDL_SetRenderDrawColor(app->renderer, 0x22, 0x80, 0x26, SDL_ALPHA_OPAQUE)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  if (!SDL_RenderClear(app->renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }



  if (!Pad_render(app->renderer, app->pad, true, true)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : Sprite_render() returned false", func_title);
    return false;
  }

  if (!Pad_render(app->renderer, app->rpad, true, true)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : Sprite_render() returned false", func_title);
    return false;
  }

  if (!Ball_render(app->renderer, app->ball, true, true)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : Sprite_render() returned false", func_title);
    return false;
  }



  if (!SDL_RenderPresent(app->renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  return true;
}

bool Application_main(Application* app) {
  const char* func_title = "Application_main()";

  uint64_t end_time = 0;
  uint64_t start_time = SDL_GetTicks();

  while(app->running) {
    Application_input_handling(app);

    if (!Application_event_handling(app)) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Application_event_handling() returned false", func_title);
      return false;
    }

    if (!Application_update_on_input(app)) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Application_update_on_input() returned false", func_title);
      return false;
    }

    if (!Application_update_on_events(app)) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Application_update_on_events() returned false", func_title);
      return false;
    }

    if (!Application_update(app)) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Application_update() returned false", func_title);
      return false;
    }

    if (!Application_render(app)) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Application_render() returned false", func_title);
      return false;
    }
    SDL_Delay(8);
    end_time = SDL_GetTicks();
    app->delta_time = end_time - start_time;
    start_time = SDL_GetTicks();
  }
  return true;
}
