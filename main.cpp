#include <raylib.h>

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

class Paddle {
  public:
    float x, y;
    float velocity;
    float width, height;

    void Draw() {
      DrawRectangle(x - width / 2, y - height / 2, width, height, WHITE);
    }

    Paddle(float xval, float yval, float veloc, float w, float h) {
      x = xval;
      y = yval;
      velocity = veloc;
      width = w;
      height = h;
    }
};

int main() {
  InitWindow(800, 600, "Pong"); //Sets up a window
  SetWindowState(FLAG_VSYNC_HINT); //Sets up VSYNC to remove ghosting

  Ball *ball = new Ball( //Create ball object
    GetScreenWidth() / 2.0f, //X pos
    GetScreenHeight() / 2.0f, //Y pos
    100.0f, //X velocity
    400.0f, //Y velocity
    5.0f //Radius
  );

  Paddle *leftPaddle = new Paddle( //Create leftPaddle object
    50, //X pos
    GetScreenHeight() / 2, //Y pos
    500, //Velocity
    10, //Width
    100
  );

  Paddle *rightPaddle = new Paddle( //Create rightPaddle object
    GetScreenWidth() - 50, //X pos
    GetScreenHeight() / 2, //Y pos
    500, //Velocity
    10, //Width
    100
  );


  while (!WindowShouldClose()) { //While the window is open
    ball->x += ball->velocityX * GetFrameTime(); //Move the ball based on velocity
    ball->y += ball->velocityY * GetFrameTime();

    //Collisions
    if (ball->y < 0) {
      ball->y = 0;
      ball->velocityY *= -1;
    }
    if (ball->y > GetScreenHeight()) {
      ball->y = GetScreenHeight(); //Stops ball from getting stuck
      ball->velocityY *= -1; //Invert ball velocity on y axis
    }

    //User input
    if (IsKeyDown(KEY_W)) {
      leftPaddle->y -= leftPaddle->velocity * GetFrameTime();
    }
    if (IsKeyDown(KEY_S)) {
      leftPaddle->y += leftPaddle->velocity * GetFrameTime();  
    }
    if (IsKeyDown(KEY_UP)) {
      rightPaddle->y -= rightPaddle->velocity * GetFrameTime();
    }
    if (IsKeyDown(KEY_DOWN)) {
      rightPaddle->y += rightPaddle->velocity * GetFrameTime();
    }

    //Rendering
    BeginDrawing();
      ClearBackground(BLACK); //Set background to black
      
      ball->Draw();//Draw ball
      leftPaddle->Draw();//Draw left paddle
      rightPaddle->Draw();//Draw right paddle

      DrawFPS(10, 10); //Show FPS
    EndDrawing();
  }
  
  CloseWindow();
  delete ball;
  delete leftPaddle;
  delete rightPaddle;

  return 0;
}