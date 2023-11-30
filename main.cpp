#include <raylib.h>
#include <string>

int main() {
  InitWindow(800, 600, "Pong");
  SetWindowState(FLAG_VSYNC_HINT);

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(BLACK);
      
      DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 5, WHITE);
      DrawRectangle(50, GetScreenHeight() / 2 - 50, 10, 100, WHITE);
      DrawRectangle(GetScreenWidth() - 50 - 10, GetScreenHeight() / 2 - 50, 10, 100, WHITE);
      

      DrawFPS(10, 10);
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}