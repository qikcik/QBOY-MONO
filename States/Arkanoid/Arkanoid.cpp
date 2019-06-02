#include "Arkanoid.hpp"
#include "../Special/GameOver.hpp"
#include "../Special/Pause.hpp"

using namespace States;

int8_t Arkanoid::run(void)
{	
	int timer = 0;
	uint8_t speed = 150;
	
	Bricks[0] = 255;			
	
	while(true)
	{	
		PAUSE_ONMENUBUTTON();
		
		timer++;
		
			
		if( keyLeft::isPressed() && paddle.x > 2 )
			paddle.x-=2;
		if( keyRight::isPressed() && paddle.x < Display::Width-paddle.width-2 )
			paddle.x+=2;
		
		
		// logic up / down
		

		if(ball.y  >  Display::Hight-paddle.height-ball.radius)
		{
			if(timer > speed )
			{
				if(Bricks[brickRow-1] != 0)
					return SpecialStates::GameOver::run(STATEID_ARKANOID,score);
					
				for(int8_t i =brickRow-1; i > 0 ; i-- )
				{
					Bricks[i] = Bricks[i-1];
				}
				Bricks[0] = rand()%256;	
				timer = 0;
			}
		}
		if( ball.y  > Display::Hight -2 )
			return SpecialStates::GameOver::run(STATEID_ARKANOID,score);
		
		Display::clear();
		
		for(int8_t i =0; i < brickRow ; i++)
			for(int8_t j =0; j < 8 ; j++)
			{
				if(( (Bricks[i] >> j) & 0b00000001) == 0b00000001)
				{
					Display::drawRectangle( brickmargin+brickWidth*j, brickmargin+brickHight*i,brickWidth,brickHight,Display::Color::Black); // Draw Paddle
				}
			}
		
		Display::drawRectangle(paddle.x,Display::Hight-paddle.height,paddle.width,paddle.height,Display::Color::Black); // Draw Paddle
		

		
		Display::drawRectangle(0,0,Display::Width,1,Display::Color::Black); 
		Display::drawRectangle(0,0,1,48,Display::Color::Black); 
		Display::drawRectangle(83,0,1,48,Display::Color::Black); 
		
		// update ball
		ball.x += ball.vx;
		ball.y += ball.vy;
		
		bool leftTop = Display::getPoint(ball.x-1,ball.y-1) == true;
		bool rightTop = Display::getPoint(ball.x+1,ball.y-1) == true;
		bool leftBottom = Display::getPoint(ball.x-1,ball.y+1) == true;
		bool rightBotom =  Display::getPoint(ball.x+1,ball.y+1) == true;
		
		if(leftTop) colision(ball.x-1,ball.y-1);
		if(rightTop) colision(ball.x+1,ball.y-1);
		if(leftBottom) colision(ball.x-1,ball.y+1);
		if(rightBotom) colision(ball.x+1,ball.y+1);

		if( leftTop || rightTop || leftBottom || rightBotom ) 
		{	
			if( leftTop && rightTop && leftBottom && rightBotom )
			{
				return SpecialStates::GameOver::run(STATEID_ARKANOID,score);
			}
			else if( (leftBottom && leftTop && rightTop)    ||
				(leftTop && rightTop && rightBotom )   ||
				(rightTop && rightBotom && leftBottom) ||
				(rightBotom && leftBottom && leftTop)   ) 
			{ 
				ball.vx = -ball.vx; ball.vy = -ball.vy; 
			}
			else if( leftTop && rightTop ) ball.vy = -ball.vy;
			else if( leftBottom && rightBotom ) ball.vy = -ball.vy;
			else if( leftTop && leftBottom ) ball.vx = -ball.vx;
			else if( rightTop && rightBotom ) ball.vx = -ball.vx;
			
			else if( leftTop) { ball.vx = 1; ball.vy = 1; }
			else if( leftBottom) { ball.vx = 1; ball.vy = -1; }
			else if( rightBotom) { ball.vx = -1; ball.vy = -1; }
			else if( rightTop) { ball.vx = -1; ball.vy = 1; }
		}
		
		Display::drawRectangle(ball.x-1,ball.y-1,ball.radius,ball.radius,Display::Color::Black); // Draw Ball
		
		Display::display();
		_delay_ms(6);
	}
	
	return STATEID_MENU;
}

void Arkanoid::colision(int8_t x, int8_t y)
{
	if(y-2 > 0 && (y-2)/4 < brickRow && x-2 > 0 && (x-2)/10 < 8  )
	{
		if(( (Bricks[(y-2)/4] >> (x-2)/10) & 0b00000001) == 0b00000001)
		{
			score++;
			Bricks[(y-2)/4] &= ~( 1 << (x-2)/10 );
		}
	}
}