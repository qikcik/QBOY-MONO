#pragma once
#include "../System.hpp"
#include "Special/gameOver.hpp"

namespace States
{
	class MainMenu
	{
		public:
			static int8_t run(void)
			{	
			
				int8_t selected = 0;
				int8_t menu = 0;
				while (true)
				{
				
					if( keyUp::isJustPressed() ) selected--;
					if( keyDown::isJustPressed() ) selected++;
	
					if( keyLeft::isJustPressed() )
					{
						menu--;
						selected = 0;
					}
					if( keyRight::isJustPressed() )
					{
						menu++;
						selected = 0;
					}
	
					if( keyA::isJustPressed() )
					{
						if(selected == 0 && menu == 1) Light::toogle();
						if(selected == 1 && menu == 1) SpecialStates::GameOver::clear();
						if(menu == 0) return selected;
					}
	
					if(menu == -1) menu = 1;
					if(menu == 3) menu = 0;
	
					if(menu == 0 && selected == -1) selected = 2;
					if(menu == 1 && selected == -1) selected = 1;
					if(menu == 1 && selected == 2) selected = 0;
					if(menu == 0 && selected == 3) selected = 0;
	
					Display::clear();
					Display::drawBorder();
	
					Display::drawRectangle(0,Display::Hight-11,Display::Width,11,Display::Color::Black);
	
					Display::drawBitmap(2,39,6, 8, Display::LeftArrow,  true  );
					Display::drawBitmap(84-5-2,39,6,8 , Display::RightArrow, true );
	
					Display::drawBitmap(2,5+(10*selected),6,8, Display::RightArrow );
	
					if(menu == 0)
					{
						Display::drawText( Display::Width/2-5*6/2,Display::Hight-9, _str("GAMES") ,true);
						Display::drawText( 10,5,_str("4096"));
						Display::drawText( 10,15,_str("FLAPPY BIRD"));
						Display::drawText( 10,25,_str("ARKANOID"));
					}
					else
					{
						Display::drawText( Display::Width/2-8*6/2,Display::Hight-9, _str("SETTINGS") ,true);
						Display::drawText( 10,5,_str("TOGGLE LIGHT"));
						Display::drawText( 10,15,_str("CLEAR SCORE"));
					}
	
					Display::display();
				}
			
			}
		
		private:
			
	};
}