#pragma once

#include "../Hardware/Registers.hpp"
#include <avr/interrupt.h>

namespace Drivers
{
	enum ExternalInterruptPin { i0 = 0, i1 = 2 };
	enum ExternalInterruptType { low, change, toLow, toHigh };
		
	template< ExternalInterruptPin Tp, ExternalInterruptType Tt>
	class ExternalInterrupt
	{
		public:
		static inline constexpr void init(void)
		{
			if constexpr ( Tt == ExternalInterruptType::low)
				Hardware::RegDef<Hardware::RegName::Mcucr>::setFalse( bitValue(Tp+0) |  bitValue(Tp+1) );
			if constexpr ( Tt == ExternalInterruptType::change)
			{
				Hardware::RegDef<Hardware::RegName::Mcucr>::setFalse( bitValue(Tp+1) );
				Hardware::RegDef<Hardware::RegName::Mcucr>::setTrue( bitValue(Tp+0) );
			}
			if constexpr ( Tt == ExternalInterruptType::toLow)
			{
				Hardware::RegDef<Hardware::RegName::Mcucr>::setFalse( bitValue(Tp+0) );
				Hardware::RegDef<Hardware::RegName::Mcucr>::setTrue( bitValue(Tp+1) );
			}
			if constexpr ( Tt == ExternalInterruptType::low)
				Hardware::RegDef<Hardware::RegName::Mcucr>::setTrue( bitValue(Tp+0) |  bitValue(Tp+1) );
				
			if constexpr ( Tp == ExternalInterruptPin::i0 )
				Hardware::RegDef<Hardware::RegName::Gicr>::setTrue( bitValue( INT0 ) );
			if constexpr ( Tp == ExternalInterruptPin::i1 )
				Hardware::RegDef<Hardware::RegName::Gicr>::setTrue( bitValue( INT1 ) );
		}
		
		static inline void enableAllInterupt() { sei(); }
		static inline void disableAllInterupt() { cli(); }
	};
}