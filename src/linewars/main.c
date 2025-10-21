#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>


#include "linewars/soldier.h"


typedef struct GameManager_Context GameManager_Context;


typedef struct GameState {
    struct GameState * (*callback)(struct GameState *, GameManager_Context *);
} GameState;


typedef enum {
    GameState_ID_Menu
    , GameState_ID_GameControl
} GameState_ID;



struct GameManager_Context {
    GameState ** state_stack;

    int monitorWidth;
    int monitorHeight;
    
    float frame_time;
    
    Soldier soldier;
};


typedef struct {
    GameManager_Context * context;
    GameState * state;
} GameManager;


GameManager game_manager(GameState * init_state, GameManager_Context * context) {
    return (GameManager) {
        .context = context
        , .state = init_state
    };
}


void game_manager_execute(GameManager * self) {
    self->context->frame_time = GetFrameTime();
    self->state = self->state->callback(self->state, self->context);
}


typedef struct {
    GameState super;
} GameState_Menu;


static GameState * game_state_menu_callback(
        GameState_Menu * self, GameManager_Context * context) {
    DrawText("Press Space to start", 300, 300, 50, GRAY);

    if(IsKeyPressed(KEY_SPACE) == true) {
        return context->state_stack[GameState_ID_GameControl];
    } else {
        return context->state_stack[GameState_ID_Menu];
    }
}


GameState_Menu game_state_menu() {
    return (GameState_Menu) {
        .super = {
            .callback = (GameState *(*)(GameState*, GameManager_Context*)) game_state_menu_callback
        }
    };
}


typedef struct {
    GameState super;
    Camera2D camera;
} GameState_GameControl;


#define VIRTUAL_WIDTH 1280
#define VIRTUAL_HEIGHT 720


static GameState * game_state_game_control_callback(
        GameState_GameControl * self, GameManager_Context * context) {

    BeginMode2D(self->camera);
    // virtual space 
    EndMode2D();
    return context->state_stack[GameState_ID_GameControl];
}


GameState_GameControl game_state_game_control(int monitorWidth, int monitorHeight) {
    return (GameState_GameControl) {
        .super = {
            .callback = (GameState *(*)(GameState*, GameManager_Context*)) game_state_game_control_callback
        }
        , .camera = {
            .target = (Vector2){ VIRTUAL_WIDTH/2.0f, VIRTUAL_HEIGHT/2.0f }
            , .offset = (Vector2){ monitorWidth/2.0f, monitorHeight/2.0f }
            , .rotation = 0.0f
            , .zoom = 1.0f
        }
    };
}


static GameState_Menu state_menu;
static GameState_GameControl state_game_control;


static GameManager_Context context;
static GameManager manager;


static GameState * game_state_stack[] = {
    &state_menu.super
    , &state_game_control.super
};


#define WINDOW_TITLE "Line Wars"

#define IMG "assets/img/"


int main(void) {
    InitWindow(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_TITLE);

    int display = GetCurrentMonitor();
    int monitorWidth = GetMonitorWidth(display);
    int monitorHeight = GetMonitorHeight(display);
    SetWindowSize(monitorWidth, monitorHeight);

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    SetTargetFPS(144);
    ToggleFullscreen();

    Texture2D soldier_walk_texture = LoadTexture(IMG "Soldier_1/Walk.png");

    state_menu = game_state_menu();
    state_game_control = game_state_game_control(monitorWidth, monitorHeight);

    context = (GameManager_Context) {
        .state_stack = game_state_stack
        , .monitorWidth = monitorWidth
        , .monitorHeight = monitorHeight
        , .soldier = soldier((Vector2){300, 300}, soldier_walk_texture)
    };

    manager = game_manager(&state_menu.super, &context);

    while(WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(WHITE);
        game_manager_execute(&manager);
        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadTexture(soldier_walk_texture);
    CloseWindow();

    return EXIT_SUCCESS;
}


