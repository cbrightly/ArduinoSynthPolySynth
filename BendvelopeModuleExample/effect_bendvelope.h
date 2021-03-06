#ifndef effect_bendvelope_h_
#define effect_bendvelope_h_
#include "AudioStream.h"
#include "utility/dspinst.h"

#define SAMPLES_PER_MSEC (AUDIO_SAMPLE_RATE_EXACT/1000.0)

#include "stdint.h"

#include "timeKeeper32.h"

class RateParameter
{
public:
  //Constructor
  RateParameter( void );
//Variables
  uint32_t timeScale;
  int8_t powerScale;


};

class LevelParameter
{
public:
  //Constructor
  LevelParameter( void );
  uint8_t getLevel( void );
  //Variables
  uint8_t level;

};

class AudioEffectBendvelope : public AudioStream
{
public:
	AudioEffectBendvelope();
	//Functions
	void noteOn();
	void noteOff();
	void attack( uint8_t, int8_t );
	void decay( uint8_t, int8_t );
	uint32_t getDecay( void );
	void sustain( uint8_t );
	void release( uint8_t, int8_t );
	void setAttackHold( uint8_t );
	//RateParameter getAttack( void );
	//RateParameter getDecay( void );
	//RateParameter getRelease( void );

	using AudioStream::release;
	virtual void update(void);
	void tick( uint32_t );

private:
	audio_block_t *inputQueueArray[1];
	// state
	uint8_t  state;  // idle, delay, attack, hold, decay, sustain, release
	//uint16_t count;  // how much time remains in this state, in 8 sample units
	int32_t  mult;   // attenuation, 0=off, 0x10000=unity gain
	
	uint8_t noteState;
	uint8_t amp;
	uint8_t shadowAmp;
  
	void changeAmp( RateParameter&, uint32_t, uint8_t, uint8_t& );
	void changeAmp( LevelParameter&, uint8_t& );
	void changeAmp( uint8_t, uint8_t& );
	
	//Timekeepers are modified logical counter modules
	TimeKeeper32 mainTimeKeeper;
	TimeKeeper32 shadowTimeKeeper;
	
	RateParameter envAttack;
	RateParameter envDecay;
	LevelParameter envSustain;
	RateParameter envRelease;
	RateParameter envAttackHold;

	uint32_t maxAttack;
	uint32_t maxDecay; 
	uint32_t maxRelease; 
	uint32_t maxAHold;
	
};

#undef SAMPLES_PER_MSEC
#endif
