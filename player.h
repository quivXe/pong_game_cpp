extern const int WINDOW_WIDTH, WINDOW_HEIGHT;

struct Player
{
    Paddle paddle;
    TextToDisplay pointsToDisplay;
    int points = 0;
    void addPoint()
    {
       points ++;
       pointsToDisplay.updateText(points);
    }
};

