#include <raylib.h>

void wallCollision(Vector2 &pos, float &fallOneSpeed, float ballRadius){
    if(pos.x >= GetScreenWidth() - ballRadius)      
    pos.x = GetScreenWidth() - ballRadius;
            
    // Left
    if(pos.x <= ballRadius)
    pos.x = 0 + ballRadius;

    // Down
    if(pos.y >= GetScreenHeight() - ballRadius) {
        pos.y = GetScreenHeight() - ballRadius;
        fallOneSpeed *= -0.8f;
    }

    // Up
    if( pos.y <= ballRadius)
    pos.y = 0 + ballRadius; 
}
    
void fallSpeed(Vector2 &pos, float gravity, float &speed){
    speed += gravity;
    pos.y += speed;
}

int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "PIXEL");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Middle position for shapes
    Vector2 ballOnePosition = { GetScreenWidth() / 1.0f, GetScreenHeight() /2.0f };
    Vector2 ballTwoPosition = { GetScreenWidth() / 2.0f, GetScreenHeight() /3.0f };
    Vector2 ballThreePosition = { GetScreenWidth() / 3.0f, GetScreenHeight() /4.0f };
    Vector2 ballFourPosition = { GetScreenWidth() / 4.0f, GetScreenHeight() / 2.0f };
    Vector2 ballFivePosition = { GetScreenWidth() / 5.0f, GetScreenHeight() / 3.0f };

    Vector2 ballOneSpeed = { 20.0f, 30.0f};
    Vector2 ballTwoSpeed = { 20.0f, 30.0f};
    Vector2 ballThreeSpeed = { 20.0f, 30.0f};
    Vector2 ballFourSpeed = { 20.0f, 30.0f};
    Vector2 ballFIveSpeed = { 20.0f, 30.0f};

    float fallOneSpeed = 0.0f;
    float fallTwoSpeed = 0.0f;
    float fallThreeSpeed = 0.0f;
    float fallFourSpeed = 0.0f;
    float fallFiveSpeed = 0.0f;


    float gravity = 0.8f;
    int ballRadius = 20;
    Color charcoal = { 40, 40, 40, 255 };
    Color ballColor = MAROON;
       

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {       
        // Update
        // Controls for Keys
        if(IsKeyDown(KEY_RIGHT)) ballOnePosition.x += ballOneSpeed.x;
        if(IsKeyDown(KEY_LEFT)) ballOnePosition.x -= ballOneSpeed.x;
        if(IsKeyDown(KEY_UP)) ballOnePosition.y -= ballOneSpeed.y;
        if(IsKeyDown(KEY_DOWN)) ballOnePosition.y += ballOneSpeed.y;

        // Gravity
        fallSpeed(ballOnePosition, gravity, fallOneSpeed);
        fallSpeed(ballTwoPosition, gravity, fallTwoSpeed);
        fallSpeed(ballThreePosition, gravity, fallThreeSpeed);
        fallSpeed(ballFourPosition, gravity, fallFourSpeed);
        fallSpeed(ballFivePosition, gravity, fallFiveSpeed);

   
        
        // Collision with walls 
        wallCollision(ballOnePosition, fallOneSpeed, ballRadius);
        wallCollision(ballTwoPosition, fallTwoSpeed, ballRadius);
        wallCollision(ballThreePosition, fallThreeSpeed, ballRadius);
        wallCollision(ballFourPosition, fallFourSpeed, ballRadius);
        wallCollision(ballFivePosition, fallFiveSpeed, ballRadius);
           

        // Draw
        BeginDrawing();
            ClearBackground(charcoal);
            // DrawRectangle(ballOnePosition.x, ballOnePosition.y, 60, 60, MAROON);
            DrawCircleV(ballOnePosition, ballRadius, ballColor);
            DrawCircleV(ballTwoPosition, ballRadius, ballColor);            
            DrawCircleV(ballThreePosition, ballRadius, ballColor);            
            DrawCircleV(ballFourPosition, ballRadius, ballColor);            
            DrawCircleV(ballFivePosition, ballRadius, ballColor);            

        EndDrawing();
    }


    // De-Initialization
    CloseWindow();        // Close window and OpenGL context
    

    return 0;
}