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

    // Apply the hardware change
    if (enable) {
        m_hardware.enableFilter();
    } else {
        m_hardware.disableFilter();
    }
    
    // Update our internal state
    m_filterEnabled = enable;
}
