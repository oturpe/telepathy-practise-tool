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
    BeatRecorder(uint16_t delay);

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
    uint16_t GetRate();

private:
    // How long this recorder waits for next beat until it decides that
    // the recording run has concluded.
    uint16_t delay;

    // How many beats have been recorded during current recording run
    uint16_t beatsRecorded;
    
    // Recording length
    uint32_t counter;

    // Current recorded rate
    uint16_t rate;

    // Debounce helper: Last recording moment
    uint16_t lastRecordingMoment;
};
