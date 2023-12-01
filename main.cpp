#include <raylib.h>
#include <string>

int main() {
  InitWindow(800, 600, "Pong"); //Sets up a window
  SetWindowState(FLAG_VSYNC_HINT); //Sets up VSYNC to remove ghosting

  while (!WindowShouldClose()) { //While the window is open
    BeginDrawing();
      ClearBackground(BLACK); //Set background to black
      
      DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 5, WHITE); //Draw ball
      DrawRectangle(50, GetScreenHeight() / 2 - 50, 10, 100, WHITE); //Draw left paddle
      DrawRectangle(GetScreenWidth() - 50 - 10, GetScreenHeight() / 2 - 50, 10, 100, WHITE); //Draw right paddle

      DrawFPS(10, 10); //Show FPS
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}