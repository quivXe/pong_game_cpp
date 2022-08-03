using namespace sf;

extern float getRandNum();
extern float getRandNum(int, int);
extern const int WINDOW_WIDTH, WINDOW_HEIGHT;
extern struct Player leftPlayer, rightPlayer;

class Ball
{
    float posx, posy, velX, velY;
    const float r = 10;
    const Color color = Color(255, 0, 126);
    const float speed = 10;

    float getVel2FromPrimedVel1(float vel1) { return 1 - pow(abs(vel1), 2); }
    Vector2f distanceFromPaddle(Paddle paddle) { return paddle.getPos() - getPos(); }

    void set_random_vel()
    {
        // making sure, overall velocity is always the same
        velX = getRandNum(400, 700); // between these to prevent from bouncing off up and bottom only
        velX /= 1000;
        velY = getVel2FromPrimedVel1(velX);
        velX = pow(velX, 2);

        // adding more directions
        float randomForNegative = getRandNum();
        if (randomForNegative < 0.25) { velX *= -1; velY *= -1;}
        else if (randomForNegative < 0.50) { velX *= 1; velY *= -1;}
        else if (randomForNegative < 0.75) { velX *= -1; velY *= 1;}
        // else: leave it as it is (velX *= 1; velY *= 1;).
    }
    void move() { shapeObject.move(Vector2f(speed * velX, speed * velY)); }

    void collisionDetection()
    {
        // BOUNCING OFF THE TOP AND BOTTOM
        if ( getPos().y - r < 0 || getPos().y + r > WINDOW_HEIGHT ) { velY *= -1; }

        // BOUNCING OFF THE PADDLES
        if ((getPos().x - r <= leftPlayer.paddle.getPos().x + leftPlayer.paddle.width/2) &&
            (getPos().x - r >= leftPlayer.paddle.getPos().x + leftPlayer.paddle.width/2 - speed - 1) &&
            (getPos().y + r >= leftPlayer.paddle.getPos().y - leftPlayer.paddle.height/2) &&
            (getPos().y - r <= leftPlayer.paddle.getPos().y + leftPlayer.paddle.height/2))
            {
                velX *= -1;

            }
        if ((getPos().x + r >= rightPlayer.paddle.getPos().x - rightPlayer.paddle.width/2) &&
            (getPos().x + r <= rightPlayer.paddle.getPos().x - rightPlayer.paddle.width/2 + speed + 1) &&
            (getPos().y + r >= rightPlayer.paddle.getPos().y - rightPlayer.paddle.height/2) &&
            (getPos().y - r <= rightPlayer.paddle.getPos().y + rightPlayer.paddle.height/2))
            {
                velX *= -1;
                return;

            }

        // OFF SCREEN
        if (getPos().x + r < 0)
        {
            rightPlayer.addPoint();
            respawn();
        }
        if (getPos().x - r > WINDOW_WIDTH)
        {
            leftPlayer.addPoint();
            respawn();
        }
    }


public:
    CircleShape shapeObject;

    Ball()
    {
        respawn();
        shapeObject.setRadius(r);
        shapeObject.setOrigin(Vector2f(r, r));
        shapeObject.setFillColor(color);
    }

    Vector2f getPos() { return shapeObject.getPosition(); }

    void respawn()
    {
        shapeObject.setPosition(Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));
        set_random_vel();
    }

    void update()
    {
        collisionDetection();
        move();
    }
};

