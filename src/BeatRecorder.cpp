#include <stdint.h>
#include "BeatRecorder.h"

// Constant for marking the "last recording moment" in situation where
// recording has not started yet.
#define RECORDING_NOT_STARTED 0xFFFF

BeatRecorder::BeatRecorder(uint16_t delay, uint16_t debouncePeriod) :
    delay(delay),
    debouncePeriod(debouncePeriod),
    beatsRecorded(0),
    counter(0),
    rate(0),
    lastRecordingMoment(RECORDING_NOT_STARTED) {
}

bool BeatRecorder::Run() {
    if (!beatsRecorded) {
        // Not recording, return immediately
        return false;
    }

    counter++;

    if(counter > lastRecordingMoment + delay) {
        // Recording concluded, clean data and stop recording
        counter = 0;
        beatsRecorded = 0;
        lastRecordingMoment = RECORDING_NOT_STARTED;
    }

    return true;
}

uint16_t BeatRecorder::Record() {
    if (IsWithinBouncePeriod()) {
        // Debounce: Ignore very quick successions
        return rate;
    }

    beatsRecorded++;
    lastRecordingMoment = counter;

    rate = counter/(beatsRecorded - 1);

    return rate;
}

uint16_t BeatRecorder::GetRate() const {
    return rate;
}

bool BeatRecorder::IsWithinBouncePeriod() const {
    return
        counter >= lastRecordingMoment
        && counter < lastRecordingMoment + debouncePeriod
    ;
}

