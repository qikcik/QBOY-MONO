#pragma once

#include "../../System.hpp"

#include <stdlib.h>

#define State_Arkanoid_BrickRow 10

namespace States
{
	class Arkanoid
	{
		public:
		int8_t run(void);
		
		
		private:
		struct
		{
			const int8_t radius = 3;
			double x = Display::Width / 2;
			double y = Display::Hight - 10;
			
			int8_t vx = 1;
			int8_t vy = -1;
		} ball;
		
		struct
		{
			const int8_t height = 4;
			const int8_t width = 20;
			int8_t x = Display::Width/2;
		} paddle;
		
		const int8_t brickWidth = 10;
		const int8_t brickHight = 4;
		const int8_t brickmargin = 2;
		const int8_t brickRow = State_Arkanoid_BrickRow;
		
		int16_t score = 0;
		
		uint8_t Bricks[State_Arkanoid_BrickRow];

		void colision(int8_t x, int8_t y);

	};
}