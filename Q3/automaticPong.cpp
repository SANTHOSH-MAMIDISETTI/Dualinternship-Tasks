#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

constexpr int WindowWidth = 800;
constexpr int WindowHeight = 600;
constexpr int PaddleWidth = 20;
constexpr int PaddleHeight = 100;
constexpr int BallRadius = 10;
constexpr float PaddleSpeed = 1.0;
constexpr float BallSpeed = 0.8;

class Paddle {
public:
  sf::RectangleShape shape;
  float speed;

  Paddle(float posX, float posY)
      : speed(PaddleSpeed) {
    shape.setPosition(posX, posY);
    shape.setSize(sf::Vector2f(PaddleWidth, PaddleHeight));
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(PaddleWidth / 2, PaddleHeight / 2);
  }

  void moveUp() {
    shape.move(0, -speed);
  }

  void moveDown() {
    shape.move(0, speed);
  }
};

class Ball {
public:
  sf::CircleShape shape;
  sf::Vector2f velocity;

  Ball(float posX, float posY)
      : velocity(-BallSpeed, -BallSpeed) {
    shape.setPosition(posX, posY);
    shape.setRadius(BallRadius);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(BallRadius, BallRadius);
  }

  void update() {
    shape.move(velocity);

    if (shape.getPosition().y - BallRadius < 0 || shape.getPosition().y + BallRadius > WindowHeight)
      velocity.y = -velocity.y;
  }

  void reset() {
    shape.setPosition(WindowWidth / 2, WindowHeight / 2);
    int randomDirectionX = rand() % 2 == 0 ? -1 : 1;
    int randomDirectionY = rand() % 2 == 0 ? -1 : 1;
    velocity = sf::Vector2f(BallSpeed * randomDirectionX, BallSpeed * randomDirectionY);
  }
};

bool checkCollision(const sf::RectangleShape& paddle, const sf::CircleShape& ball) {
  return paddle.getGlobalBounds().intersects(ball.getGlobalBounds());
}

// Calculate the estimated time of collision between the ball and paddle
float calculateEstimatedTimeOfCollision(const sf::RectangleShape& paddle, const Ball& ball) {
  float paddleY = paddle.getPosition().y;
  float ballY = ball.shape.getPosition().y;
  float ballVelocityY = ball.velocity.y;

  if (ballVelocityY == 0) {
    return -1;  // Ball is not moving vertically
  }

  if (ballVelocityY < 0 && ballY >= paddleY) {
    return -1;  // Ball is moving away from the paddle
  }

  if (ballVelocityY > 0 && ballY <= paddleY) {
    return -1;  // Ball is moving away from the paddle
  }

  float estimatedTime = abs((paddleY - ballY) / ballVelocityY);
  return estimatedTime;
}

// Adjust the AI paddle's speed based on the estimated time of collision
void adjustAIPaddleSpeed(Paddle& paddle, const float estimatedTime) {
  if (estimatedTime < 0) {
    paddle.speed = PaddleSpeed;  // Default speed
  } else if (estimatedTime < 0.2) {
    paddle.speed = PaddleSpeed * 1.5;  // Increase speed for quick intercept
  } else {
    paddle.speed = PaddleSpeed;  // Default speed
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "Pong Game");

  Paddle paddle1(WindowWidth - PaddleWidth, WindowHeight / 2);
  Paddle paddle2(PaddleWidth, WindowHeight / 2);
  Ball ball(WindowWidth / 2, WindowHeight / 2);

  int score1 = 0;  // Player 1 score
  int score2 = 0;  // Player 2 score

  bool automaticMode = false;
  bool isPaused = false;

  // Seed the random number generator
  srand(time(NULL));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::M) {
          // Toggle automatic mode
          automaticMode = !automaticMode;
        }
        if (event.key.code == sf::Keyboard::P) {
          // Toggle pause
          isPaused = !isPaused;
        }
      }
    }

    if (!isPaused) {
      if (!automaticMode) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle1.shape.getPosition().y - PaddleHeight / 2 > 0)
          paddle1.moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle1.shape.getPosition().y + PaddleHeight / 2 < WindowHeight)
          paddle1.moveDown();
      } else {
        // Automatic mode: Paddle 1 follows the ball
        float ballY = ball.shape.getPosition().y;
        float paddle1Y = paddle1.shape.getPosition().y;

        if (ballY < paddle1Y && paddle1.shape.getPosition().y - PaddleHeight / 2 > 0)
          paddle1.moveUp();
        if (ballY > paddle1Y && paddle1.shape.getPosition().y + PaddleHeight / 2 < WindowHeight)
          paddle1.moveDown();
      }

      // AI-controlled paddle 2
      float ballY = ball.shape.getPosition().y;
      float paddle2Y = paddle2.shape.getPosition().y;

      if (ballY < paddle2Y && paddle2.shape.getPosition().y - PaddleHeight / 2 > 0)
        paddle2.moveUp();
      if (ballY > paddle2Y && paddle2.shape.getPosition().y + PaddleHeight / 2 < WindowHeight)
        paddle2.moveDown();

      ball.update();

      if (checkCollision(paddle1.shape, ball.shape) || checkCollision(paddle2.shape, ball.shape)) {
        ball.velocity.x = -ball.velocity.x;

        // Adjust AI paddle speed based on the estimated time of collision
        float estimatedTime = calculateEstimatedTimeOfCollision(paddle2.shape, ball);
        adjustAIPaddleSpeed(paddle2, estimatedTime);
      }

      if (ball.shape.getPosition().x - BallRadius < 0) {
        // Player 2 scores a point
        score2++;
        ball.reset();
      } else if (ball.shape.getPosition().x + BallRadius > WindowWidth) {
        // Player 1 scores a point
        score1++;
        ball.reset();
      }

      // Check if either player reached 10 points
      if (score1 == 10 || score2 == 10) {
        // Display the winner
        string winner = (score1 == 10) ? "Player 1" : "Player 2";
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
          cout << "Failed to load font!" << endl;
          return 1;
        }

        sf::Text winnerText;
        winnerText.setFont(font);
        winnerText.setCharacterSize(50);
        winnerText.setFillColor(sf::Color::White);
        winnerText.setString("Winner: " + winner);
        winnerText.setPosition(WindowWidth / 2 - winnerText.getGlobalBounds().width / 2, WindowHeight / 2 - winnerText.getGlobalBounds().height / 2);

        while (window.isOpen()) {
          sf::Event event;
          while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
              window.close();
          }

          window.clear(sf::Color::Black);

          window.draw(paddle1.shape);
          window.draw(paddle2.shape);
          window.draw(ball.shape);
          window.draw(winnerText);

          window.display();
        }

        return 0;
      }
    }

    window.clear(sf::Color::Black);

    window.draw(paddle1.shape);
    window.draw(paddle2.shape);
    window.draw(ball.shape);

    // Display the scores at the bottom of the screen
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
      cout << "Failed to load font!" << endl;
      return 1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Player 1: " + to_string(score1) + "   Player 2: " + to_string(score2));
    scoreText.setPosition(WindowWidth / 2 - scoreText.getGlobalBounds().width / 2, WindowHeight - 50);

    window.draw(scoreText);

    window.display();
  }

  return 0;
}
