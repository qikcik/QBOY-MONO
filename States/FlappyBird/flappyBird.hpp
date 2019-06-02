#pragma once

#include "../../System.hpp"

#include <stdlib.h>

namespace States
{
	class flappyBird
	{
		public:
		int8_t run(void);
		
		
		private:
		static const uint8_t imgBird_h = 10;
		static const uint8_t imgBird_w = 15;
		static const uint8_t imgBird[] PROGMEM;
		
		static const uint8_t imgTop_h = 4;
		static const uint8_t imgTop_w = 15;
		static const uint8_t imgTop[] PROGMEM;
		
		static const uint8_t imgNormal_h = 1;
		static const uint8_t imgNormal_w = 15;
		static const uint8_t imgNormal[] PROGMEM;
		
		struct Player
		{
			double y = 15;
			const int8_t x = 16;
			double gravity = 0;
			uint16_t score = 0;
		};
		
		struct Pipe
		{
			int8_t x = 84-15;
			int8_t y = 10;
			int8_t gateSize = 25;
		};
	};
}