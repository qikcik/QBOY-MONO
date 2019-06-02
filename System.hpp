#pragma once

#include "Drivers/Display.hpp"
#include "Drivers/button.hpp"
#include "Drivers/Output.hpp"

#include "Drivers/ExternalInterruts.hpp"

// 
//if( !keyMenu::isPressed() ) { Light::toogle(); /*if( Pause::run() ) return -1;*/ } 

namespace System
{
	// using driver for keys
	typedef Drivers::Button<Drivers::ButtonType::GND, Hardware::RegName::portD,Hardware::RegName::ddrD,Hardware::RegName::pinD,5> keyA;
	
	typedef Drivers::Button<Drivers::ButtonType::GND, Hardware::RegName::portD,Hardware::RegName::ddrD,Hardware::RegName::pinD,6> keySuper;
	
	typedef Drivers::Button<Drivers::ButtonType::GND, Hardware::RegName::portD,Hardware::RegName::ddrD,Hardware::RegName::pinD,2> keyUp;
	typedef Drivers::Button<Drivers::ButtonType::GND, Hardware::RegName::portD,Hardware::RegName::ddrD,Hardware::RegName::pinD,0> keyDown;
	typedef Drivers::Button<Drivers::ButtonType::GND, Hardware::RegName::portD,Hardware::RegName::ddrD,Hardware::RegName::pinD,1> keyLeft;
	typedef Drivers::Button<Drivers::ButtonType::GND, Hardware::RegName::portD,Hardware::RegName::ddrD,Hardware::RegName::pinD,4> keyRight;
	// using driver for light
	typedef Drivers::Output<Hardware::RegName::portD,Hardware::RegName::ddrD,7,true,true> Light;
	
	// interaupt to menu
	//typedef Drivers::ExternalInterrupt<Drivers::ExternalInterruptPin::i1,Drivers::ExternalInterruptType::toHigh> pauseInteraupt;
	
	// using driver for display
	typedef Drivers::Display Display;
	
	
	const uint8_t ApplicationCount = 2;
		
	void start(void);
}

using namespace System;

#define STATEID_CONTINUE -100
#define STATEID_MENU -1
#define STATEID_4096 0
#define STATEID_FLAPPYBIRD 1
#define STATEID_ARKANOID 2

