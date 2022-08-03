using namespace sf;

extern Font FONT;

class TextToDisplay
{
    const Color color = Color(200, 200, 200);
    const int textSize = 35;
    int x, y;
    void updateOrigin()
    {
        float xOffset = textObject.getGlobalBounds().width / 2;
        textObject.setOrigin(xOffset, 0);
    }
public:
    Text textObject;
    TextToDisplay(float x, float y)
    {
        textObject.setCharacterSize(textSize);
        textObject.setFillColor(color);
        textObject.setFont(FONT);
        textObject.setPosition(Vector2f(x, y));
        updateText("0");
    }
    void updateText(std::string text)
    {
        textObject.setString(text);
        updateOrigin();
    }
    void updateText(int num)
    {
        updateText(std::to_string(num));
    }
};

