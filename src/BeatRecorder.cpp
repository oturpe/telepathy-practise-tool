#include <stdint.h>
#include "BeatRecorder.h"

BeatRecorder::BeatRecorder(uint16_t delay) :
    delay(delay),
    beatsRecorded(0),
    counter(0),
    rate(0),
    lastRecordingMoment(0xFFFF) {
}

bool BeatRecorder::Run() {
    if (!beatsRecorded) {
        // Not recording, return immediately
        return false;
    }

    counter++;

    if(counter > delay) {
        // Recording concluded, clean data and stop recording
        counter = 0;
        beatsRecorded = 0;
        lastRecordingMoment = 0xFFFF;
    }

    return true;
}

uint16_t BeatRecorder::Record() {
    if (counter == lastRecordingMoment) {
        // Debounce: Ignore very quick successions
        return rate;
    }

    beatsRecorded++;
    lastRecordingMoment = counter;

    rate = counter/(beatsRecorded - 1);

    return rate;
}

uint16_t BeatRecorder::GetRate() {
    return rate;
}
