#pragma once
#include "../../System.hpp"
#include <avr/eeprom.h>
#include <stdlib.h>

namespace SpecialStates
{
	class GameOver
	{
		public:
			static int8_t run(int8_t stateId, uint16_t score)
			{	
		
				if(stateId == -1)
					return -1;
				uint16_t best =  eeprom_read_word(&saves[stateId]);
				if( score > best ) 
				{
					best = score;
					eeprom_write_word(&saves[stateId],best);
				}
				while( keyLeft::isPressed() || keyRight::isPressed() || keyUp::isPressed() || keyDown::isPressed() || keyA::isPressed() /*|| keyMenu::isPressed() */ )
				{
				
				}
			
				_delay_ms(50);
			
				int8_t selected = 0;
				while(true)
				{
					if( keyLeft::isJustPressed() ) selected--;
					if( keyRight::isJustPressed() ) selected++;
				
					if(selected == -1) selected = 1;
					if(selected == 2) selected = 0;
				
					if( keyA::isJustPressed() )
					{
						if(selected == 0) return stateId;
						else return -1;
					}
				
					char strScore[10];
					char strBest[10];
					itoa( score, strScore, 10);
					itoa( best, strBest, 10);
				
					Display::clear(Display::Color::White);
					Display::drawBorder();
				
					Display::drawRectangle(0,0,84,11,Display::Color::Black);
					Display::drawText(84 /2 - 7*6 /2,2,_str("GAMEOVER"),true);
				
					Display::drawText(3,16,_str("YOUR: ")); Display::drawText(6*6,16,strScore);
					Display::drawText(3,26,_str("BEST: ")); Display::drawText(6*6,26,strBest);

					Display::drawRectangle(0,Display::Hight-11,Display::Width,11,Display::Color::Black);
				
					Display::drawBitmap(2,39,6, 8, Display::LeftArrow,  true  );
					Display::drawBitmap(84-5-2,39,6,8 , Display::RightArrow, true );
					if(selected == 0)
						Display::drawText(Display::Width/2-5*6/2,Display::Hight-9,_str("RETRY"),true );
					else
						Display::drawText(Display::Width/2-4*6/2,Display::Hight-9,  _str("BACK"),true );


					Display::display();
				}
			}
		
			static void clear(void)
			{
				eeprom_write_word(&GameOver::saves[0],0);
				eeprom_write_word(&GameOver::saves[1],0);
				eeprom_write_word(&GameOver::saves[2],0);
			}

		private:
			static uint16_t saves[3] EEMEM;
	};
}