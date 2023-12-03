#include <raylib.h>
#include <string>

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

    Rectangle GetRect() {
      return Rectangle {x - width / 2, y - height / 2, width, height};
    }

    void Draw() {
      DrawRectangleRec(GetRect(), WHITE);
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
  const char* winnerText = nullptr;
  int leftScore = 0;
  int rightScore = 0;

  InitWindow(800, 600, "Pong"); //Sets up a window
  SetWindowState(FLAG_VSYNC_HINT); //Sets up VSYNC to remove ghosting

  Ball *ball = new Ball( //Create ball object
    GetScreenWidth() / 2.0f, //X pos
    GetScreenHeight() / 2.0f, //Y pos
    300.0f, //X velocity
    100.0f, //Y velocity
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
    if (ball->y < 0) { //Collisions for top of screen
      ball->y = 0;
      ball->velocityY *= -1;
    }
    if (ball->y > GetScreenHeight()) { //Collisions for bottom of screen
      ball->y = GetScreenHeight(); //Stops ball from getting stuck
      ball->velocityY *= -1; //Invert ball velocity on y axis
    }
    if (CheckCollisionCircleRec(Vector2{ball->x, ball->y}, ball->radius, rightPaddle->GetRect())) { //Right paddle collisions
      if (ball->velocityX > 0) {
        ball->velocityX *= -1.05f;
        ball->velocityY = (ball->y - rightPaddle->y) / (rightPaddle->height / 2) * -ball->velocityX; //Makes the ball bounce more realistically
        rightScore++;
      }
    }
    if (CheckCollisionCircleRec(Vector2{ball->x, ball->y}, ball->radius, leftPaddle->GetRect())) { //Left paddle collisions
      if (ball->velocityX < 0) {
        ball->velocityX *= -1.05f;
        ball->velocityY = (ball->y - leftPaddle->y) / (leftPaddle->height / 2) * ball->velocityX; //Makes the ball bounce more realistically
        leftScore++;
      }
    }

    //User input
    if (IsKeyDown(KEY_W)) {
      if (leftPaddle->y > 1) {
        leftPaddle->y -= leftPaddle->velocity * GetFrameTime();
      }
    }
    if (IsKeyDown(KEY_S)) {
      if (leftPaddle->y < GetScreenHeight()) {
        leftPaddle->y += leftPaddle->velocity * GetFrameTime();  
      }
    }
    if (IsKeyDown(KEY_UP)) {
      if (rightPaddle->y > 1) {
        rightPaddle->y -= rightPaddle->velocity * GetFrameTime();
      }
    }
    if (IsKeyDown(KEY_DOWN)) {
      if (rightPaddle->y < GetScreenHeight()) {
        rightPaddle->y += rightPaddle->velocity * GetFrameTime();
      }
    }

    //Winner state and restarting the game
    if (ball->x < 0) {
      winnerText = "Right Player Wins!";
    }
    if (ball->x > GetScreenWidth()) {
      winnerText = "Left Player Wins!";
    }
    if (winnerText && IsKeyPressed(KEY_SPACE)) { //Reset game after space key is pressed
      ball->x = GetScreenWidth() / 2;
      ball->y = GetScreenHeight() / 2;
      ball->velocityX = 300.0f;
      ball->velocityY = 100.0f;

      leftPaddle->x = 50;
      leftPaddle->y = GetScreenHeight() / 2;
      rightPaddle->x = GetScreenWidth() - 50;
      rightPaddle->y = GetScreenHeight() / 2;

      winnerText = nullptr;
      leftScore = 0;
      rightScore = 0;
    }

    //Rendering
    BeginDrawing();
      ClearBackground(BLACK); //Set background to black

      DrawRectangle(GetScreenWidth() / 2 - 1, 0, 2, GetScreenHeight(), WHITE);

      ball->Draw();//Draw ball
      leftPaddle->Draw();//Draw left paddle
      rightPaddle->Draw();//Draw right paddle

      DrawText(TextFormat("%i", leftScore), GetScreenWidth() / 4, 10, 30, WHITE); //Draw the left side score
      DrawText(TextFormat("%i", rightScore), GetScreenWidth() - (GetScreenWidth() / 4), 10, 30, WHITE); //Draw the right side score

      if (winnerText) { //Once there is a winner, display winnerText
        int textWidth = MeasureText(winnerText, 60);
        DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 -30, 60, YELLOW);
      }

    EndDrawing();
  }
  
  CloseWindow();
  delete ball;
  delete leftPaddle;
  delete rightPaddle;

  return 0;
}