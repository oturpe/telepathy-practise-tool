// This is the configuration file. Ideally, any configuration and calibration
// of the device should be done by changing this file only.

// Needed by util/delay.h
#define F_CPU 1000000UL

// Delay between two executions of main loop, given in millisecond.
#define LOOP_DELAY 20

// Definition of indicator pin data direction and data ports and pins
#define INDICATOR_DATA_DIR DDRD
#define INDICATOR_DATA_DIR_PIN DDD1
#define INDICATOR_DATA PORTD
#define INDICATOR_DATA_PIN PORTD1

// Half length of one complete indicator period. In other words, the time the
// indicator spends on and off. Given in units of LOOP_DELAY.
#define INDICATOR_HALF_PERIOD 25

// How long heartbeat counter waits for the next record before it concludes
// that the recording session has ended and waits for the next one. Given in
// units of LOOP_DELAY
#define BEAT_COUNTER_DELAY 200

// Definition of lamp driver pin data direction and data ports and pins
#define LAMP_DATA_DIR DDRD
#define LAMP_DATA_DIR_PIN DDD3
#define LAMP_DATA PORTD
#define LAMP_DATA_PIN PORTD3

// Ratio of lamp on time compared to total flash period, given as divisor
// of total period that gives on time (e.g. 4 would give 25 % duty cycle)
#define LAMP_ON_DIVISOR 4