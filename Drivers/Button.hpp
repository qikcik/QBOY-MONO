#pragma once
#include "../Hardware/Registers.hpp"
#include <avr/pgmspace.h>
#include <util/delay.h>


#define _input_button_staticPrepare( T ) \
template<> bool T::mem = false; \

namespace Drivers
{
	enum ButtonType {GND,VCC};
	template<ButtonType type, RegName port,RegName ddr,RegName pin, uint8_t n>
	class Button
	{
		public:
			static inline constexpr void init(void)
			{
				RegDef<ddr>::setFalse( bitValue(n) );
				
				if constexpr (type == ButtonType::GND)
					RegDef<port>::setTrue( bitValue(n) );	
				if constexpr (type == ButtonType::VCC)
					RegDef<port>::setFalse( bitValue(n) );
					
				mem = false;
			}
			
			static inline constexpr bool isPressed(void)
			{
				if constexpr (type == ButtonType::GND) return RegDef<pin>::getBit( n );
				if constexpr (type == ButtonType::VCC) return !RegDef<pin>::getBit( n );
			}
			
			static inline constexpr void waitForRelease(void)
			{
				mem = true;
			}
			
			static inline constexpr bool isJustPressed()
			{
				if(isPressed() == true && mem == false)
				{
					mem = true;
					return true;
				}
				if(isPressed() == false)
					mem = false;

				return false;
			}
		private:
			static bool mem;
	};
}
