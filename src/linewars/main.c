#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>


#define WINDOW_TITLE "Line Wars"
#define VIRTUAL_WIDTH 1280
#define VIRTUAL_HEIGHT 720

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

    Texture2D soldierSpriteSheet = LoadTexture(IMG "soldier_spritesheet.png");

    Camera2D camera = {0};
    camera.target = (Vector2){ VIRTUAL_WIDTH/2.0f, VIRTUAL_HEIGHT/2.0f };
    camera.offset = (Vector2){ monitorWidth/2.0f, monitorHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while(WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(WHITE);
        
        BeginMode2D(camera);
        // virtual space 
        EndMode2D();

        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadTexture(soldierSpriteSheet);
    CloseWindow();

    return EXIT_SUCCESS;
}


