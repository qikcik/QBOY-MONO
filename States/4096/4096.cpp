#include "4096.hpp"
#include <stdlib.h>
#include "../Special/gameOver.hpp"
#include "../Special/Pause.hpp"

using namespace States;

const uint8_t Game4096::Frame[] PROGMEM = {
	#include "assets/Frame(21x12).bitmap"
};
const uint8_t Game4096::Font[] PROGMEM = {
	#include "assets/Font(4x6).bitmap"
};

int8_t Game4096::run(void)
{
	add();
	while(true)
	{
		PAUSE_ONMENUBUTTON();
		
		if( keyUp::isJustPressed() )
		{
			for (int8_t i = 0; i < 4 ; i++)
			for (int8_t x = 0; x < 4 ; x++)
			for (int8_t y = 1; y < 4 ; y++)
			{
				if(board[x][y-1] == board[x][y] && board[x][y] != 4096)
				{
					board[x][y-1] = board[x][y] *2;
					board[x][y] = 0;
				}
				if(board[x][y-1] == 0)
				{
					board[x][y-1] = board[x][y];
					board[x][y] = 0;
				}
			}
			int8_t state= add(); if( state != STATEID_CONTINUE ) return state;
		}
		if( keyDown::isJustPressed() )
		{
			for (int8_t i = 0; i < 4 ; i++)
			for (int8_t x = 0; x < 4 ; x++)
			for (int8_t y = 2; y >= 0 ; y--)
			{
				if(board[x][y+1] == board[x][y] && board[x][y] != 4096)
				{
					board[x][y+1] = board[x][y] *2;
					board[x][y] = 0;
				}
				if(board[x][y+1] == 0)
				{
					board[x][y+1] = board[x][y];
					board[x][y] = 0;
				}
			}
			int8_t state= add(); if(state != STATEID_CONTINUE ) return state;
		}
		if( keyLeft::isJustPressed() )
		{
			for (int8_t i = 0; i < 4 ; i++)
			for (int8_t y = 0; y < 4 ; y++)
			for (int8_t x = 3; x > 0 ; x--)
			{
				if(board[x-1][y] == board[x][y] && board[x][y] != 4096)
				{
					board[x-1][y] = board[x][y] *2;
					board[x][y] = 0;
				}
				if(board[x-1][y] == 0)
				{
					board[x-1][y] = board[x][y];
					board[x][y] = 0;
				}
			}
			int8_t state= add(); if(state != STATEID_CONTINUE ) return state;
		}
		if( keyRight::isJustPressed() )
		{
			for (int8_t i = 0; i < 4 ; i++)
			for (int8_t y = 0; y < 4 ; y++)
			for (int8_t x = 2; x >= 0 ; x--)
			{
				if(board[x+1][y] == board[x][y] && board[x][y] != 4096 )
				{
					board[x+1][y] = board[x][y] *2;
					board[x][y] = 0;
				}
				if(board[x+1][y] == 0)
				{
					board[x+1][y] = board[x][y];
					board[x][y] = 0;
				}
			}
			int8_t state= add(); if(state != STATEID_CONTINUE ) return state;
		}
		
		Display::clear(Display::Color::White);

		for (uint8_t x = 0; x != 4 ; x++)
		for (uint8_t y = 0; y != 4 ; y++)
		{
			if( board[x][y] != 0)
			{
				char str[5];
				itoa( board[x][y], str, 10);
				
				uint8_t offset = Frame_w/2 - Font_letterX/2;
				if(board[x][y] >= 10) offset = Frame_w/2 - Font_letterX;
				if(board[x][y] >= 100) offset = Frame_w/2 - Font_letterX/2*3;
				if(board[x][y] >= 1000) offset = Frame_w/2 - Font_letterX*2;
				
				Display::drawBitmap(x*Frame_w,y*Frame_h,Frame_w,Frame_h,Frame,invert);
				Display::drawText(x*Frame_w+offset+1,(y*Frame_h+Frame_h/2-3),str,invert,Font,Font_letterX,Font_letterY);
			}
		}
		Display::display();
	}
	
	return -1;
}

int8_t Game4096::add(void)
{
	uint8_t is = 0;
	for (int8_t y = 0; y < 4 ; y++)
	for (int8_t x = 0; x < 4 ; x++)
	if(board[x][y] == 0) is++;
	
	invert = false;
	if(is == 1) invert = true;
	
	
	if(is != 0)
	{
		while(true)
		{
			uint8_t x = rand() % 4;
			uint8_t y = rand() % 4;
			if(board[x][y] == 0)
			{
				board[x][y] = 1;
				break;
			}
		}
		return STATEID_CONTINUE;
	}
	
	uint16_t score = 0;
	for (int8_t y = 0; y < 4 ; y++)
		for (int8_t x = 0; x < 4 ; x++)
			score += board[x][y];
			
	return SpecialStates::GameOver::run(STATEID_4096,score);
}