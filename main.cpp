#include <raylib.h>
#include <string>

int main() {
  InitWindow(800, 600, "Pong"); //Sets up a window
  SetWindowState(FLAG_VSYNC_HINT); //Sets up VSYNC to remove ghosting

  class Ball {
    public:
      float x, y;
      float velocityX, velocityY;
      float radius;

      void Draw() {
        DrawCircle((int) x, (int) y, (int) radius, WHITE);
      }

      Ball(float xval, float yval, float xveloc, float yveloc, float ballrad) {
        x = xval;
        y = yval;
        velocityX = xveloc;
        velocityY = yveloc;
        radius = ballrad;
      }
  };

  Ball *ball = new Ball(
    GetScreenWidth() / 2.0f,
    GetScreenHeight() / 2.0f,
    100.0f,
    300.0f,
    5.0f
  );


  while (!WindowShouldClose()) { //While the window is open
    ball->x += ball->velocityX * GetFrameTime(); //Move the ball based on velocity
    ball->y += ball->velocityY * GetFrameTime();

    if (ball->y < 0) {
      ball->y = 0;
      ball->velocityY *= -1;
    }
    if (ball->y > GetScreenHeight()) {
      ball->y = GetScreenHeight(); //Stops ball from getting stuck
      ball->velocityY *= -1; //Invert ball velocity on y axis
    }

    BeginDrawing();
      ClearBackground(BLACK); //Set background to black
      
      ball->Draw();//Draw ball
      DrawRectangle(50, GetScreenHeight() / 2 - 50, 10, 100, WHITE); //Draw left paddle
      DrawRectangle(GetScreenWidth() - 50 - 10, GetScreenHeight() / 2 - 50, 10, 100, WHITE); //Draw right paddle

      DrawFPS(10, 10); //Show FPS
    EndDrawing();
  }
  
  CloseWindow();
  delete ball;

  return 0;
}