//Code by the one unknown man...
//Modified by: www.polesite.ru in 2013

#ifndef __NESINTERFACE_H
#define __NESINTERFACE_H

#include "Arduino.h"

#define NES_A      0
#define NES_B      1
#define NES_SELECT 2
#define NES_START  3
#define NES_UP     4
#define NES_DOWN   5
#define NES_LEFT   6
#define NES_RIGHT  7

class NES {

  public:
  	NES();
	
    void Init( uint8_t nesPulsePin, uint8_t nesLatchPin, uint8_t nesDataPin );
	void Update();
	byte Read();

};


#endif//__NES_INTERFACE_H


