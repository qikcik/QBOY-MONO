#include "../Hardware/Registers.hpp"
#include <avr/pgmspace.h>
#include <util/delay.h>
#pragma once

using namespace Hardware;

#define _str(x) (char*)x

namespace Drivers
{
	class Display
	{
		public:
			Display() = delete;
		
			static const uint8_t Width = 84;
			static const uint8_t Hight = 48;
		
			enum Color {White = 0, Black=1};
		
			static void init(void);
			static void clear(bool color = 0);
			static void display(void);
			static void drawBorder();
		
			static bool getPoint(uint8_t x, uint8_t y);
			static void drawPoint(uint8_t x, uint8_t y, bool color);
			static void drawRectangle(uint8_t x, uint8_t y,uint8_t w,uint8_t h, bool color);
			static void drawBitmap(uint8_t x, uint8_t y,uint8_t w,uint8_t h, const uint8_t image[], bool invert = false);
			static void drawText(uint8_t x, uint8_t y,char* str, bool invert = false, const uint8_t font[] = DefaultFont,uint8_t letterX = 6,uint8_t letterY = 8);
		
		
			static const uint8_t LeftArrow[] PROGMEM;
			static const uint8_t RightArrow[] PROGMEM;
		private:
			static uint8_t buffor[Width*Hight/8];

		private:
	
			enum SendType {Command=0, Data=1};
			static void sendByte(uint8_t type, uint8_t data);
		
		private:
			// 0-9,:,A-Z
			static const uint8_t DefaultFont[] PROGMEM; 
		
		private:
			typedef Hardware::RegDef<Hardware::RegName::portB> Port;
			typedef Hardware::RegDef<Hardware::RegName::ddrB>  Ddr;
		
			static constexpr const uint8_t PinCLK = 5;
			static constexpr const uint8_t PinDIN = 3;
			static constexpr const uint8_t PinCE = 2;
			static constexpr const uint8_t PinDC = 1;
			static constexpr const uint8_t PinRST = 0;
	};
}
