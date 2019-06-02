#include <avr/io.h>
#pragma  once


#define _OnRegister(b,r,a) \
if constexpr (r == Hardware::RegName::portB) \
	b PORTB a; \
if constexpr (r == Hardware::RegName::pinB) \
	b PINB a; \
if constexpr (r == Hardware::RegName::ddrB) \
	b DDRB a; \
if constexpr (r == Hardware::RegName::portC) \
	b PORTC a; \
if constexpr (r == Hardware::RegName::pinC) \
	b PINC a; \
if constexpr (r == Hardware::RegName::ddrC) \
	b DDRC a; \
if constexpr (r == Hardware::RegName::portD) \
	b PORTD a; \
if constexpr (r == Hardware::RegName::pinD) \
	b PIND a; \
if constexpr (r == Hardware::RegName::ddrD) \
	b DDRD a; \
if constexpr (r == Hardware::RegName::Mcucr) \
	b MCUCR a; \
if constexpr (r == Hardware::RegName::Gicr) \
	b GICR a; \

namespace Hardware
{

	inline constexpr uint8_t bitValue(uint8_t i)
	{
		return (1 << i);
	}
	
	
	enum RegName
	{
		portB,
		ddrB,
		pinB,
		
		portC,
		ddrC,
		pinC,
		
		portD,
		ddrD,
		pinD,
		
		Mcucr,
		Gicr
	};
	
	template <RegName Treg>
	class RegDef
	{
		public:
			RegDef() = delete;
			
			static inline constexpr void set(uint8_t value)
			{
				_OnRegister( ,Treg, = value; );
			}
			static inline constexpr void setTrue(uint8_t value)
			{
				_OnRegister( ,Treg, |= (value) );
			}
			static inline constexpr void setFalse(uint8_t value)
			{
				_OnRegister( ,Treg, &= ~(value) );
			}
			static inline constexpr void setToogle(uint8_t value)
			{
				_OnRegister( ,Treg, ^= (value) );
			}
			
			static inline constexpr uint8_t get()
			{
				_OnRegister( return ,Treg, ; );
			}
			static inline constexpr bool getBit(uint8_t n)
			{
				uint8_t temp;
				_OnRegister( temp =  ,Treg , ; );
				return (temp | ~(1 << n) ) == ~(1 << n);
			}
	};
}