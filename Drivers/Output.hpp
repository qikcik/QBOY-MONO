#pragma once

#include "../Hardware/Registers.hpp"

namespace Drivers
{
	template<Hardware::RegName port,Hardware::RegName ddr,uint8_t n, bool prepareState = true, bool invert = false>
	class Output
	{
		public:
		static inline constexpr void init(void)
		{
			Hardware::RegDef<ddr>::setTrue( bitValue(n) );
			
			if constexpr (prepareState == true)
				on();
			if constexpr (prepareState == false)
				off();
		}
		
		static inline constexpr void on(void)
		{
			if constexpr (invert == false)
				Hardware::RegDef<port>::setTrue( bitValue(n) );
			if constexpr (invert == true)
				Hardware::RegDef<port>::setFalse( bitValue(n) );
		}
		static inline constexpr void off(void)
		{
			if constexpr (invert == false)
				Hardware::RegDef<port>::setFalse( bitValue(n) );
			if constexpr (invert == true)
				Hardware::RegDef<port>::setTrue( bitValue(n) );
		}
		
		static inline constexpr void toogle(void)
		{
			Hardware::RegDef<port>::setToogle( bitValue(n) );
		}
		
		static inline constexpr void get(void)
		{
			return Hardware::RegDef<port>::getBit( bitValue(n) );
		}
	};
}