//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle
#define PADDLEHEIGHT 10
#define PADDLEWIDTH 70

// gap between bricks
#define GAP 5

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    // add ball to window
    add(window, ball);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    // add paddle to window
    add(window, paddle);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
    // add label to window
    add(window, label);
    

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // ball velocity
    double velocity_x = drand48() * 2 + 1;
    double velocity_y = drand48() * 2 + 1;
    
    bool ballMove = false;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
        GEvent event2 = getNextEvent(MOUSE_EVENT);
        
        // if we heard one
        if (event != NULL)
        {   
            // if the event was moved
            if (getEventType(event) == MOUSE_CLICKED)
            {
                ballMove = true;
            }
        }
        // if we heard one
        if (event != NULL)
        {
            // if the event was moved
            if (getEventType(event) == MOUSE_MOVED && ballMove == true)
            {
                
                double y = getY(paddle);
                // ensure paddle doesn't go out of window
                if (getX(event) <= 0)
                {
                    setLocation(paddle, 0, y);    
                }
                else if (getX(event) + PADDLEWIDTH >= WIDTH)
                {
                    setLocation(paddle, WIDTH - PADDLEWIDTH, y);
                }
                else
                {
                    // ensure paddle x position follows cursor
                    double x = getX(event);
                    setLocation(paddle, x, y);
                }
            }
        }
        if (ballMove == true)
        {
            move(ball, velocity_x, velocity_y);
            // when ball hits the left edge
            if (getX(ball) <= 0)
            {
                velocity_x *= -1;
            }
            // when ball hits the right edge
            else if (getX(ball) + getWidth(ball) >= getWidth(window))
            {
                velocity_x *= -1;
            }
            // when ball hits the top edge
            else if (getY(ball) <= 0)
            {
                velocity_y *= -1;
            }
            // when ball hit the bottom edge
            else if (getY(ball) >= getHeight(window))
            {
                lives -= 1;
                ballMove = false;
                setLocation(ball, WIDTH / 2, HEIGHT / 2);
            }
            pause(10);
        }
        GObject object = detectCollision(window, ball);
        if (object != NULL)
        {
            if (object == paddle)
            {
                velocity_y *= -1;
            }
            else if (strcmp(getType(object), "GRect") == 0)
            {
                velocity_y *= -1;
                removeGWindow(window, object);
                points += 1;
                updateScoreboard(window, label, points);
            }
        }
        // when no more live or all bricks are broken
        if (lives == 0 || points == ROWS * COLS)
        {
            break;
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // calculate brick's width to fit COLUMN number of bricks in window
    int brickwidth = (getWidth(window) - GAP * (COLS + 1)) / COLS;
    // calculate brick's height to fit ROW number of bricks in a fix height
    int brickheight = (100 - GAP * (ROWS + 1)) / ROWS;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect((GAP * (j + 1))+ (brickwidth * j), 50 + (GAP * (i + 1)) + (brickheight * i), brickwidth, brickheight);
            // set brick's color
            switch (i % 5)
            {
                case 0:
                {
                    setColor(brick, "RED");
                    break;
                }
                case 1:
                {
                    setColor(brick, "ORANGE");
                    break;
                }
                case 2:
                {
                    setColor(brick, "YELLOW");
                    break;
                }
                case 3:
                {
                    setColor(brick, "GREEN");
                    break;
                }
                case 4:
                {
                    setColor(brick, "CYAN");
                    break;
                }
            }
            
            setFilled(brick, true);
            // add brick to window
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(0 + WIDTH / 2, 0 + HEIGHT / 2, RADIUS, RADIUS);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect rectangle = newGRect(WIDTH / 2 - PADDLEWIDTH / 2, HEIGHT - 30, PADDLEWIDTH, PADDLEHEIGHT);
    setColor(rectangle, "BLACK");
    setFilled(rectangle, true);
    return rectangle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-18");
    setLocation(label, getWidth(window) / 2, getHeight(window) / 2 - 30);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
