#include "../Display.hpp"

using namespace Drivers;

uint8_t Display::buffor[Display::Width*Display::Hight/8] = { 0 };

void Display::sendByte(uint8_t type, uint8_t data)
{
	Port::setFalse( bitValue(PinCE) );
	
	if(type == SendType::Data)
		Port::setTrue( bitValue(PinDC) );
	if(type == SendType::Command)
		Port::setFalse( bitValue(PinDC) );
	
	SPDR = data;
	while(!(SPSR & (1<<SPIF))); // wait for data send
	
	Port::setTrue( bitValue(PinCE) );
}

void Display::init(void)
{
	Port::setFalse( bitValue(PinRST) );
	
	Ddr::setTrue( bitValue(PinRST) | bitValue(PinCLK) | bitValue(PinDIN) | bitValue(PinDC) | bitValue(PinCE) );
	
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); // spi configuration
	
	_delay_ms(15); // time for display to receive RST(true) and else
	
	Port::setTrue( bitValue(PinRST) | bitValue(PinCE) );
	
	sendByte(SendType::Command, 0x21); // Function set - extended instruction set
	sendByte(SendType::Command, 0x13); // Bias - 1:48
	sendByte(SendType::Command, 0x06); // Temperature Control
	sendByte(SendType::Command, 0xa5); // Set Vop
	sendByte(SendType::Command, 0x20); // Function set - basic instruction set, horizontal addressing
	sendByte(SendType::Command, 0x0C); // Display control - normal mode
} 

void Display::display(void)
{
	sendByte(SendType::Command, 0x40);
	sendByte(SendType::Command, 0x80);
	
	for (uint16_t i = 0 ; i < (Width * Hight / 8) ; i++)
	sendByte(SendType::Data, buffor[i]);
}

void Display::clear(bool color)
{
	  for (uint16_t i = 0 ; i < (Width * Hight / 8) ; i++)
		buffor[i] = color ? 0xFF : 0x00;
}

bool Display::getPoint(uint8_t x, uint8_t y)
{
	return ((buffor[(y/8)*84+x] >> y%8) & 0b000000001) == 0b00000001;
}

void Display::drawPoint(uint8_t x, uint8_t y, bool color)
{
	if(color)	
		buffor[(y/8)*84+x] |= 1 << y%8;
	else
		buffor[(y/8)*84+x] &= ~(1 << y%8);
}
void Display::drawRectangle(uint8_t x, uint8_t y,uint8_t w,uint8_t h, bool color)
{
	for(uint8_t lx = x; lx != x+w; lx++)
	{
		for(uint8_t ly = y; ly != y+h; ly++)
		{
			drawPoint(lx,ly,color);
		}
	}
}

void Display::drawBitmap(uint8_t x, uint8_t y,uint8_t w,uint8_t h, const uint8_t image[], bool invert)
{
	for(uint8_t ly = 0; ly < h; ly++)
	{
		for(uint8_t lx = 0; lx < w; lx++)
		{
			uint8_t img = pgm_read_byte(&image[(ly/8)*w+lx]);
			if(invert) img = ~img;
			drawPoint(lx+x,ly+y,  (img >> (ly%8)) & 0b000000001 );
		}
	}
}

const uint8_t Display::DefaultFont[] PROGMEM = 
{
	#include "../../Assets/Font(char6x8).bitmap"
};

const uint8_t Display::LeftArrow[] PROGMEM = {
	#include "../../Assets/IconLeftArrow(6x8).bitmap"
};
const uint8_t Display::RightArrow[] PROGMEM = {
	#include "../../Assets/IconRightArrow(6x8).bitmap"
};


void Display::drawText(uint8_t x, uint8_t y,char* str, bool invert,const uint8_t font[],uint8_t letterX,uint8_t letterY)
{
	for(uint8_t i = 0; str[i] != '\0';i++)
	{
		uint8_t offset = str[i] - '0';
		if(str[i] >= 'A') offset = str[i] - 'A' + 11;
		
		if(str[i] == 32) offset = 37;

		for(uint8_t ly = 0; ly < letterY; ly++)
		{
			for(uint8_t lx = 0; lx < letterX; lx++)
			{
				uint8_t img = pgm_read_byte(&font[(lx+offset*letterX)]);
				if(invert) img = ~img;
				drawPoint(i*letterX+lx+x,ly+y,  (img >> (ly%8)) & 0b000000001 );
			}
		}
	}
}

void Display::drawBorder()
{
	Display::drawRectangle(0,0,Display::Width,1,Display::Color::Black);
	Display::drawRectangle(0,47,Display::Width,1,Display::Color::Black);
	Display::drawRectangle(0,0,1,48,Display::Color::Black);
	Display::drawRectangle(83,0,1,48,Display::Color::Black);
}