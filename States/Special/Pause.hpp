#pragma once
#include "../../System.hpp"
#include <avr/eeprom.h>


#define  PAUSE_ONMENUBUTTON() \
if( keySuper::isJustPressed() ) { if( SpecialStates::Pause::run() ) return STATEID_MENU; }

namespace SpecialStates
{
	class Pause
	{
		public:
		static int8_t run(void)
		{
			while( keyLeft::isPressed() || keyRight::isPressed() || keyUp::isPressed() || keyDown::isPressed() || keyA::isPressed()  )
			{
				
			}
			
			_delay_ms(50);
			
			int8_t selected = 1;
			while(true)
			{
				if( keyLeft::isJustPressed() ) selected--;
				if( keyRight::isJustPressed() ) selected++;
				
				if(selected == -1) selected = 2;
				if(selected == 3) selected = 0;
				
				if( keyA::isJustPressed() )
				{
					if(selected == 1) return false;
					if(selected == 2) return true;
					if(selected == 0) Light::toogle();
				}

				Display::clear(Display::Color::White);
				Display::drawBorder();
						
				Display::drawBitmap(Display::Width/2-image_w/2,Display::Hight/2-image_h/2,image_w,image_h,image);

				Display::drawRectangle(0,Display::Hight-11,Display::Width,11,Display::Color::Black);
				Display::drawBitmap(2,39,6, 8, Display::LeftArrow,  true  );
				Display::drawBitmap(84-5-2,39,6,8 , Display::RightArrow, true );
				if(selected == 0) Display::drawText(Display::Width/2-12*6/5,Display::Hight-9,  _str("LIGHT"),true );
				if(selected == 1) Display::drawText(Display::Width/2-8*6/2,Display::Hight-9,_str("CONTINUE"),true );
				if(selected == 2) Display::drawText(Display::Width/2-9*6/2,Display::Hight-9,  _str("BACK MENU"),true );
				
				Display::drawRectangle(0,0,84,11,Display::Color::Black);
				Display::drawText(84 /2 - 6*5 /2,2,(char*)"PAUSE",true);


				Display::display();
			}
		}
		
		private:
		static const uint8_t image_h = 16;
		static const uint8_t image_w = 16;
		static const uint8_t image[] PROGMEM;
	};
}