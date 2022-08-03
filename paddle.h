using namespace sf;

extern const int WINDOW_WIDTH, WINDOW_HEIGHT;

enum DirectionsY
{
    UP = -1,
    DOWN = 1,
};

class Paddle
{
private:
    float posx, posy;
    const Color color = Color(122, 0, 255);
    const float speed = 6;

public:
    const float width = 25, height = 200;

    RectangleShape shapeObject;
    Paddle(float x, float y)
    {
        shapeObject.setSize(Vector2f(width, height));
        shapeObject.setOrigin(Vector2f(width/2, height/2));
        shapeObject.setPosition(Vector2f(x, y));
        shapeObject.setFillColor(color);
    }

    Vector2f getPos() { return shapeObject.getPosition(); }

    void move(int direction)
    {
        // PREVENT FROM GOING OUT OF SCREEN
        if ( direction == UP && getPos().y - height/2 < 0 ) return;
        if ( direction == DOWN && getPos().y + height/2 > WINDOW_HEIGHT ) return;

        shapeObject.move(Vector2f(0.f, (speed * direction)));
    }
};

