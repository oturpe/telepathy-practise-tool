// Telepathy practise tool for Koelse Museum of Paranormal Technology
//
// Author: Otto Urpelainen
// Email: oturpe@iki.fi
// Date: 2018-04-10

#include "AvrUtils.h"

#include "config.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "BeatRecorder.h"

/// \brief
///    Sets indicator to given state
///
/// \param light
///    If indicator should be lit
void setIndicator(bool light) {
    if (light) {
        INDICATOR_DATA |= BV(INDICATOR_DATA_PIN);
    }
    else {
        INDICATOR_DATA &= ~BV(INDICATOR_DATA_PIN);
    }
}

/// \brief
///    Toggles the indicator led state.
void toggleIndicator() {
    static bool isLit;

    isLit = !isLit;
    setIndicator(isLit);
}

/// \brief
///    Sets lamp to given state
///
/// \param light
///    If lamp should be lit
void setLamp(bool light) {
    if (light) {
        LAMP_DATA |= BV(LAMP_DATA_PIN);
    }
    else {
        LAMP_DATA &= ~BV(LAMP_DATA_PIN);
    }
}

uint32_t lampCounter = 0;

// If heartbeat has already been recorded
bool recorded = false;

BeatRecorder recorder(BEAT_COUNTER_DELAY, BEAT_COUNTER_DEBOUNCE);
uint8_t beatLength = 50;

ISR(INT0_vect) {
    recorded = true;
    beatLength = recorder.Record();
}

int main() {
    INDICATOR_DATA_DIR |= BV(INDICATOR_DATA_DIR_PIN);
    LAMP_DATA_DIR |= BV(LAMP_DATA_DIR_PIN);

    // Setup external interrupt for reading button presses
    MCUCR |= BV(ISC01);
    GIMSK |= BV(INT0);
    // INTO pin (PD2) as input with pullup enables
    DDRD |= BV(DDD2);
    PORTD |= BV(PORTD2);

    sei();

    while (true) {
        bool recording = recorder.Run();

        if (recording) {
            // No lights during recording
            setIndicator(false);
            setLamp(false);
        }
        else if (lampCounter < beatLength/LAMP_ON_DIVISOR) {
            // Light on time
            setIndicator(true);

            // But no lamp before heartbeat has been recorded
            if (recorded) {
                setLamp(true);
            }

            lampCounter++;
        }
        else if (lampCounter < beatLength) {
            // Light off time
            setIndicator(false);
            setLamp(false);
            lampCounter++;
        }
        else {
            lampCounter = 0;
        }

        _delay_ms(LOOP_DELAY);
    }
}
