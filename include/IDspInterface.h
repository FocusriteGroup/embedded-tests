#pragma once

/**
 * @brief Interface for DSP audio muting control
 * 
 * This interface abstracts the DSP-specific operations for muting and unmuting
 * audio. Muting should be used during filter state transitions to prevent
 * audible clicks, pops, or other artifacts.
 */
class IDspInterface {
public:
    virtual ~IDspInterface() = default;

    /**
     * @brief Mute the audio signal
     * 
     * This method should immediately mute the audio output to prevent
     * artifacts during filter state transitions.
     */
    virtual void mute() = 0;

    /**
     * @brief Unmute the audio signal
     * 
     * This method should restore audio output after a filter state transition
     * has completed.
     */
    virtual void unmute() = 0;

    /**
     * @brief Check if audio is currently muted
     * 
     * @return true if audio is muted, false otherwise
     */
    virtual bool isMuted() const = 0;
};
