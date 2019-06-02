#pragma once

#include "../../System.hpp"

namespace States
{
	class Game4096
	{
		private:
			static const uint8_t Frame_h = 12;
			static const uint8_t Frame_w = 21;
		
			static const uint8_t Frame[] PROGMEM;
			
			
			static const uint8_t Font_letterX = 4;
			static const uint8_t Font_letterY = 6;
			static const uint8_t Font[] PROGMEM;

			uint16_t board[4][4] = { 0 };
			bool invert = false;
		
			int8_t add(void);
		public:
			int8_t run(void);
	};
}