#include <raylib.h>

int main(){
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Times Table Circle ");
    SetTargetFPS(60);

    // Variables
    Color BackgroundCharcoal = { 40, 40, 40, 255 };
    Vector2 smallPoints = {89, 90};
    int centerXPos = GetScreenWidth() / 2;
    int centerYPos = GetScreenHeight() / 2;
    Color circleColor = WHITE;
    float radius = 350.0f;
    int points = 10;

    while(!WindowShouldClose()){
        // Update

        BeginDrawing();
            ClearBackground(BackgroundCharcoal);

            // DrawCircleV(center, radius, circleColor);
            DrawCircleLines(centerXPos, centerYPos, radius, WHITE);
            DrawCircleV(smallPoints, 20, BLACK);
            

        
        EndDrawing();
    }

    CloseWindow();
    return 0;
    
}
