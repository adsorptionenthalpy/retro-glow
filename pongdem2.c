/*  PongDemo v1 - C Version DOS BGI
 Author: Adam Androulidakis
 PONG recreation device test requires VGA HI 640x480 256 COLORS
 Compiled with Borland Turbo C 2.01 tested in DOSBOX .74 MAC OSX 10.7.5
 Ball increases in speed when player scores. Other player is then served a faster ball.
 This buggy demo is for use in a future programming tutorial series for C to 8086 ASM conversion,
 and watching experts argue over social media over common programming practices.
 
 Features for future implementation:
 Ball randomization
 Improved clip detection
 Flicker-free screen clearing
 Game menu (Value passing functions)
 Resolution menu w/ element scaling (structures)
 Data structure such as binary tree or list
 Faster draw algorithms (demonstrated recursion)
 Keyboard hooking (utilizing interrupts for improved input)
 */
 
#include <graphics.h>
#include <dos.h>
 
#define MAXBALLSPEED 8
#define PING 400
#define LOSE 300
#define BALLSIZE 3
#define FLICKERRATE 4
#define PADDLESPEED 15
 
/* VISUAL ELEMENTS */
#define CENTERX 320
#define CENTERY 240
#define BALLSTARTX 320
#define BALLSTARTY 240
#define TOPLIMIT 55
#define BOTTOMLIMIT 380
#define TOPBOUNDS 43
#define BOTTOMBOUNDS 440
#define P1BOUNDS 4
#define P2BOUNDS 24
 
/* KEY VALUES */
#define ESCAPEKEY 1
#define P1UP 72
#define P1DOWN 80
#define P2UP 17
#define P2DOWN 31
 
int initialize();
void game();
char getkey(void);
 
int main()
{
    if (initialize())
    {
        game();
        /*end*/
        closegraph();
    }
    return 0;
 
}
 
 
int initialize()
{
    /*Initialize graphics driver, 640x480 256 Colors*/
    initgraph(VGA, 2, "C\\TC\\BGI");
    return 1;
}
void game()
{
    unsigned int msg[26];
    unsigned int speed = 0;
    unsigned int play = 1;
    unsigned int ch, score1 = 0, score2 = 0;
    int xadj = -2, yadj = 1;
    unsigned int clearslow = 1;
    unsigned int ballx = BALLSTARTX;
    unsigned int bally = BALLSTARTY;
 
    int p1x = 20, p1y = 200, p2x = 600, p2y = 200;
 
    do
    {
        /* draw the court, paddles and ball */
        line (20, TOPBOUNDS, 620, TOPBOUNDS); /*Top court (top bounds)*/
 
        line (CENTERX, TOPBOUNDS, CENTERX, BOTTOMBOUNDS); /*Center court*/
        line (20, BOTTOMBOUNDS, 620, BOTTOMBOUNDS);
 
        bar(p1x, p1y, p1x + 20, p1y + 40);
        bar(p2x, p2y, p2x + 20, p2y + 40);
 
        /* Draw the game display */
        outtextxy(304,5, "PONG");
 
        sprintf(msg, "P1 SCORE: %d", score1);
        outtextxy(150,5, msg);
 
        sprintf(msg, "P2 SCORE: %d", score2);
        outtextxy(400,5, msg);
 
        circle (ballx, bally, BALLSIZE);
 
        sprintf(msg,"%d", inp(0x60));
        outtextxy(1,1,msg);
 
        /* Get key status*/
            ch = inp(0x60);
            if(ch == ESCAPEKEY)
            {
                /* Pressing escape key to leave the game */
                play=0;
                sound(330);
                delay(1);
                nosound();
            }
            if (ch == P1UP && p1y >= TOPLIMIT)
                p1y = p1y - PADDLESPEED;
            if (ch == P1DOWN && p1y <= BOTTOMLIMIT)
                p1y = p1y + PADDLESPEED;
            if (ch == P2UP && p2y >= TOPLIMIT)
                p2y = p2y - PADDLESPEED;
            if (ch == P2DOWN && p2y <= BOTTOMLIMIT)
                p2y = p2y + PADDLESPEED;
 
        ballx = ballx + xadj;
        bally = bally + yadj;
        /* This stops the sound playing from last loop iteration*/
        nosound();
        /****/
 
        /*If ball hits the bottom of the court*/
        if (bally >= BOTTOMBOUNDS )
        {
            sound(PING);
            yadj = yadj * -1;
        }
        /*If ball hits the top of the court*/
        if (bally <= TOPBOUNDS)
        {
            sound(PING);
            yadj = yadj * -1;
        }
        /*If ball hits the player 1 paddle*/
        if (ballx <= p1x + 26 && bally >= p1y && bally <= p1y + 40)
        {
            sound(PING);
            xadj = xadj * -1;
        }
        /*If ball hits the player 2 paddle*/
        if (ballx >= p2x - 3 && bally >= p2y && bally <= p2y + 40)
        {
            sound(PING);
            xadj = xadj * -1;
        }
 
        /*If ball passes player 1 paddle*/
        if (ballx < p1x - P1BOUNDS)
        {
            sound(LOSE);
            score2++;
            ballx = BALLSTARTX, bally = BALLSTARTY;
 
            /*Change direction, increase value*/
            xadj = xadj * -1;
            xadj = xadj + 2;
            yadj = yadj * -1;
            yadj = yadj + 2;
        }
 
        /*If ball passes player 2 paddle*/
        if (ballx > p2x + P2BOUNDS)
        {
            sound(LOSE);
            score1++;
            ballx = BALLSTARTX, bally = BALLSTARTY;
 
            /*Change direction, increase value*/
            xadj = xadj * -1;
            xadj = xadj - 2;
            yadj = yadj * -1;
            yadj = yadj - 2;
        }
 
        /* Slows down the rate which cleardevice is called */
        if (clearslow >= FLICKERRATE)
        {   cleardevice();
            clearslow = 1;
        }
        clearslow++;
 
        if (yadj < -MAXBALLSPEED)
            yadj = -MAXBALLSPEED;
        if (yadj > MAXBALLSPEED)
            yadj = MAXBALLSPEED;
        if (xadj < -MAXBALLSPEED)
            xadj = -MAXBALLSPEED;
        if (yadj > MAXBALLSPEED)
            xadj = MAXBALLSPEED;
 
    }
    while(play==1); /*Loop while escape key has not been pressed*/
 }
