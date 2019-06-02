#include "flappyBird.hpp"
#include "../Special/GameOver.hpp"
#include "../Special/Pause.hpp"

using namespace States;

const uint8_t flappyBird::imgBird[] PROGMEM = {
	#include "assets/bird.ass"
};
	
const uint8_t flappyBird::imgTop[] PROGMEM = {
	#include "assets/top.ass"
};
	
const uint8_t flappyBird::imgNormal[] PROGMEM = {
	#include "assets/Normal.ass"
};

int8_t flappyBird::run(void)
{

	
	Player player;
	Pipe pipe;
	
	while(true)
	{
		PAUSE_ONMENUBUTTON();
		
		pipe.x --;
		if(pipe.x == 0 )
		{
			pipe.y = ( rand() % (Display::Hight-pipe.gateSize - imgTop_h));
			pipe.x = 84-15;
			player.score++;
			pipe.gateSize = 25 - player.score/10;
			if(pipe.gateSize == 20) pipe.gateSize = 20;
		}
		
		if( keyA::isPressed() )
		{
			if(player.gravity > 0.1) player.gravity = 0.1;
			player.gravity -= 0.35;
		}
		
		player.gravity += 0.15;
		if(player.gravity >= 1.5) player.gravity = 1.5;
		if(player.gravity <= -1) player.gravity = -1;
		player.y += player.gravity;
		
		if(player.y < 0) player.y = 0;
		if(player.y > 38) player.y = 38;
		
		if(player.x > pipe.x-imgTop_w+1)
		{
			if(player.y < pipe.y + imgTop_h || player.y > pipe.y + pipe.gateSize - imgTop_h*2)
			{
				return SpecialStates::GameOver::run(STATEID_FLAPPYBIRD,player.score);
			}	
		}
		
		
		
		Display::clear(Display::Color::White);
		
		Display::drawBitmap(player.x,player.y,imgBird_w,imgBird_h,imgBird);
		Display::drawBitmap(pipe.x,pipe.y,imgTop_w,imgTop_h,imgTop);
		Display::drawBitmap(pipe.x,pipe.y+pipe.gateSize,imgTop_w,imgTop_h,imgTop);
		for(int i =0;i < 48; i++)
		{
			if( i < pipe.y || i > pipe.y + pipe.gateSize + imgTop_h-1  )
			Display::drawBitmap(pipe.x,i,imgNormal_w,imgNormal_h,imgNormal);
		}
		Display::display();
		
		_delay_ms(10);
	}
	
	return -1;
}