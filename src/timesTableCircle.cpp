#include <raylib.h>
#include <math.h>

Vector2 PointOnCircle(float angle, float cx, float cy, float r) {
    return { cx + r * cosf(angle), cy + r * sinf(angle) };
}

float EaseInOut(float t) {
    if (t < 0.5f) return 4.0f * t * t * t;
    return 1.0f - powf(-2.0f * t + 2.0f, 3.0f) / 2.0f;
}

float Clamp01(float v) {
    if (v < 0.0f) return 0.0f;
    if (v > 1.0f) return 1.0f;
    return v;
}

enum Phase { DRAWING, HOLDING, FADING };

int main() {
    // Initialization
    const int videoWidth = 1080;
    const int videoHeight = 1920;
    const int windowWidth = 540;
    const int windowHeight = 960;

    InitWindow(windowWidth, windowHeight, "Times Table Circle");
    SetTargetFPS(60);

    RenderTexture2D target = LoadRenderTexture(videoWidth, videoHeight);

    // Variables
    Color background = { 12, 12, 20, 255 };
    float centerX = videoWidth / 2.0f;
    float centerY = videoHeight / 2.0f;
    float radius = 480.0f;

    int points = 120;
    int multiplier = 2;
    const int minMultiplier = 2;
    const int maxMultiplier = 7;

    const float drawTime = 3.0f;  // seconds to draw all lines
    const float holdTime = 0.8f;  // pause on the finished pattern
    const float fadeTime = 0.5f;  // fade out before next pattern

    Phase phase = DRAWING;
    float timer = 0.0f;
    float progress = 0.0f;
    float fade = 1.0f;
    float hueShift = 0.0f;

    while (!WindowShouldClose()) {
        // Update
        float dt = GetFrameTime();
        timer += dt;
        hueShift += 25.0f * dt;

        if (phase == DRAWING) {
            progress = EaseInOut(Clamp01(timer / drawTime)) * points;
            if (timer >= drawTime) {
                progress = (float)points;
                phase = HOLDING;
                timer = 0.0f;
            }
        } else if (phase == HOLDING) {
            if (timer >= holdTime) {
                phase = FADING;
                timer = 0.0f;
            }
        } else {
            fade = 1.0f - Clamp01(timer / fadeTime);
            if (timer >= fadeTime) {
                multiplier++;
                if (multiplier > maxMultiplier) multiplier = minMultiplier;
                phase = DRAWING;
                timer = 0.0f;
                progress = 0.0f;
                fade = 1.0f;
            }
        }

        int finishedLines = (int)progress;
        float t = progress - finishedLines;
        float step = 2.0f * PI / points;

        // Draw into the 1080x1920 texture
        BeginTextureMode(target);
        ClearBackground(background);

        BeginBlendMode(BLEND_ADDITIVE);

        DrawCircleLines((int)centerX, (int)centerY, radius, Fade(WHITE, 0.25f * fade));

        // Finished lines (rainbow, glowing where they overlap)
        for (int i = 0; i < finishedLines && i < points; i++) {
            float hue = fmodf(360.0f * i / points + hueShift, 360.0f);
            Color c = Fade(ColorFromHSV(hue, 0.75f, 1.0f), 0.45f * fade);

            Vector2 start = PointOnCircle(i * step, centerX, centerY, radius);
            Vector2 end = PointOnCircle(i * multiplier * step, centerX, centerY, radius);
            DrawLineEx(start, end, 2.0f, c);
        }

        // Current line growing from start to end, with a bright head
        if (finishedLines < points) {
            int i = finishedLines;
            float hue = fmodf(360.0f * i / points + hueShift, 360.0f);
            Color c = ColorFromHSV(hue, 0.6f, 1.0f);

            Vector2 start = PointOnCircle(i * step, centerX, centerY, radius);
            Vector2 end = PointOnCircle(i * multiplier * step, centerX, centerY, radius);
            Vector2 head = { start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t };

            DrawLineEx(start, head, 3.0f, c);
            DrawCircleV(head, 14.0f, Fade(c, 0.5f));
            DrawCircleV(head, 6.0f, WHITE);
            DrawCircleV(start, 8.0f, c);
        }

        EndBlendMode();

        // Points on the circle
        for (int i = 0; i < points; i++) {
            Vector2 p = PointOnCircle(i * step, centerX, centerY, radius);
            DrawCircleV(p, 3.0f, Fade(WHITE, 0.6f * fade));
        }

        // Text
       const char* line1 = "Just multiplication. That's it.";
        const char* line2 = "Wait for the pattern...";
        int w1 = MeasureText(line1, 52);
        int w2 = MeasureText(line2, 52);
        DrawText(line1, (videoWidth - w1) / 2, 200, 52, Fade(WHITE, 0.95f));
        DrawText(line2, (videoWidth - w2) / 2, 275, 52, Fade(WHITE, 0.6f));

        const char* label = TextFormat("x %d", multiplier);
        int labelWidth = MeasureText(label, 140);
        DrawText(label, (videoWidth - labelWidth) / 2, 1500, 140, Fade(WHITE, fade));

        EndTextureMode();

        // Show the texture scaled into the preview window
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(
            target.texture,
            { 0.0f, 0.0f, (float)videoWidth, -(float)videoHeight },
            { 0.0f, 0.0f, (float)windowWidth, (float)windowHeight },
            { 0.0f, 0.0f }, 0.0f, WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();
    return 0;
}