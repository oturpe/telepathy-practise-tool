/// \class BeatRecorder
///
/// Records heartbeat rate.
class BeatRecorder {
public:
    /// \brief
    ///    Initialize a new BeatRecorder.
    ///
    /// \param delay
    ///    How long this recorder waits for next beat until it decides that
    ///    the recording run has concluded.
    ///
    /// \param debouncePeriod
    ///    Length of switch debounce period
    BeatRecorder(uint16_t delay, uint16_t debouncePeriod);

public:
    /// \brief
    ///    Run the recorder. This needs to be called once each LOOP_DELAY when
    ///    recording.
    ///
    /// \return
    ///    If this recorder is recording at the moment
    bool Run();

    /// \brief
    ///    Records a single beat
    ///
    /// \return
    ///    Newly calculated mean beat length
    uint16_t Record();

    /// \brief
    ///    Calculated mean beat length
    uint16_t GetRate() const;

private:
    /// \brief
    ///    If current time is so close to last recording event that any new
    ///    signals should be interpreted as button bounce.
    ///
    /// \return
    ///    If current time is within bounce period
    bool IsWithinBouncePeriod() const;

private:
    // How long this recorder waits for next beat until it decides that
    // the recording run has concluded.
    const uint16_t delay;

    // Length of switch debounce period.
    const uint16_t debouncePeriod;

    // How many beats have been recorded during current recording run
    uint16_t beatsRecorded;
    
    // Recording length
    uint32_t counter;

    // Current recorded rate
    uint16_t rate;

    // Debounce helper: Last recording moment
    uint16_t lastRecordingMoment;
};
