 #include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::A,
    Keyboard::Z,
    Keyboard::Up,
    Keyboard::Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];

Vector2f ballVelocity;
bool server = false;

void Load() {

    for (auto& p : paddles) {
        p.setSize(paddleSize - Vector2f(3, 3));
        p.setOrigin(paddleSize / 2.f);
    }

    ball.setRadius(ballRadius / 2);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);

    ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

    Reset();
}

void Reset() {

    paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition(gameWidth - 30 + paddleSize.x / 2, gameHeight / 2);

    ball.setPosition(gameWidth / 2, gameHeight / 2);
}

void Update(RenderWindow& window) {

    static Clock clock;
    float dt = clock.restart().asSeconds();

    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

    float direction = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }
    paddles[0].move(0, direction * paddleSpeed * dt);

    ball.move(ballVelocity * dt);

    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
    if (by > gameHeight) {

        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, -10);
    }
    else if (by < 0) {

        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, 10);
    }
    else if (bx > gameWidth) {

        Reset();
    }
    else if (bx < 0) {

        Reset();
    }
    else if (bx < paddleSize.x &&
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) && 
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
        ) {

    }
    else if (bx < paddleSize.y &&
        by > paddles[1].getPosition().y - (paddleSize.y * 0.5) && 
        by < paddles[1].getPosition().y + (paddleSize)){

    }
        
}

void Render(RenderWindow& window) {

    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}

