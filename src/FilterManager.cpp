#include "FilterManager.h"

FilterManager::FilterManager(IHardwareInterface& hardware, IDspInterface& dsp)
    : m_hardware(hardware)
    , m_dsp(dsp)
    , m_sampleRate(48000)  // Default to 48kHz
    , m_filterEnabled(false)
{
}

void FilterManager::setSampleRate(uint32_t sampleRate) {
    m_sampleRate = sampleRate;
    
    // BUG: This condition is incorrect!
    // The filter should NOT be active at 192kHz or above
    // But this code enables it at 192kHz when it shouldn't
    bool shouldEnableFilter = (m_sampleRate <= 192000);
    
    if (shouldEnableFilter != m_filterEnabled) {
        applyFilterState(shouldEnableFilter);
    }
}

void FilterManager::setFilterEnabled(bool enabled) {
    if (enabled != m_filterEnabled) {
        applyFilterState(enabled);
    }
}

bool FilterManager::isFilterActive() const {
    return m_filterEnabled && m_hardware.isFilterEnabled();
}

void FilterManager::applyFilterState(bool enable) {
    // Mute audio to prevent clicks/pops during transition
    m_dsp.mute();
    
    // Apply the hardware change
    if (enable) {
        m_hardware.enableFilter();
    } else {
        m_hardware.disableFilter();
    }
    
    // Update our internal state
    m_filterEnabled = enable;
    
    // Unmute audio after transition is complete
    m_dsp.unmute();
}
