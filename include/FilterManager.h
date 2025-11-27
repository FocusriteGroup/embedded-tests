#pragma once

#include "IHardwareInterface.h"
#include "IDspInterface.h"
#include <cstdint>

/**
 * @brief Manages audio filter state based on sample rate
 * 
 * The FilterManager coordinates filter enable/disable operations with hardware
 * and DSP interfaces. It ensures that:
 * - The filter is only active at appropriate sample rates
 * - Audio is muted during filter state transitions to prevent artifacts
 * - Hardware state is kept in sync with the logical filter state
 */
class FilterManager {
public:
    /**
     * @brief Construct a new Filter Manager
     * 
     * @param hardware Reference to the hardware interface for filter control
     * @param dsp Reference to the DSP interface for muting control
     */
    FilterManager(IHardwareInterface& hardware, IDspInterface& dsp);

    /**
     * @brief Set the sample rate and update filter state accordingly
     * 
     * The filter will be automatically enabled or disabled based on the
     * sample rate.
     * 
     * @param sampleRate The new sample rate in Hz
     */
    void setSampleRate(uint32_t sampleRate);

    /**
     * @brief Explicitly enable or disable the filter
     * 
     * 
     * @param enabled true to enable the filter, false to disable
     */
    void setFilterEnabled(bool enabled);

    /**
     * @brief Check if the filter is currently active
     * 
     * @return true if the filter is engaged, false otherwise
     */
    bool isFilterActive() const;

    /**
     * @brief Get the current sample rate
     * 
     * @return uint32_t The current sample rate in Hz
     */
    uint32_t getSampleRate() const { return m_sampleRate; }

private:
    /**
     * @brief Apply a filter state change with proper muting
     * 
     * @param enable true to enable the filter, false to disable
     */
    void applyFilterState(bool enable);

    IHardwareInterface& m_hardware;
    IDspInterface& m_dsp;
    uint32_t m_sampleRate;
    bool m_filterEnabled;
    bool m_userRequestedState;
    bool m_shouldFilterBeEnabled;
};
