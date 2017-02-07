#include "nesinterface.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bit(b) (1UL << (b))

static uint8_t latchPin;
static uint8_t pulsePin;
static uint8_t dataPin;

static byte data;

NES::NES() {
  // nothing to do here	
}

void NES::Init( uint8_t nesPulsePin, uint8_t nesLatchPin, uint8_t nesDataPin )
{
        latchPin = nesLatchPin;
        pulsePin = nesPulsePin;
        dataPin  = nesDataPin;
        
        pinMode( latchPin, OUTPUT );
        pinMode( pulsePin, OUTPUT );
        pinMode( dataPin,  INPUT  );
}

void NES::Update()
{		
        digitalWrite( latchPin, HIGH );
        digitalWrite( latchPin, LOW  );
           
        for( byte i = 0 ; i < 8 ; ++i ) 
        {
            bitWrite(data, i, boolean( digitalRead( dataPin ) ) );
            
            digitalWrite( pulsePin, HIGH );
            digitalWrite( pulsePin, LOW  );
        }
}

byte NES::Read() {
	return (~data);
}


