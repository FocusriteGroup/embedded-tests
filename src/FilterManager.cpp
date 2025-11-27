#include "FilterManager.h"

FilterManager::FilterManager(IHardwareInterface& hardware, IDspInterface& dsp)
    : m_hardware(hardware)
    , m_dsp(dsp)
    , m_sampleRate(48000)
    , m_filterEnabled(false)
    , m_userRequestedState(false)
    , m_shouldFilterBeEnabled(true)
{
}

void FilterManager::setSampleRate(uint32_t sampleRate) 
{
    m_sampleRate = sampleRate;
    bool m_previousShouldFilterBeEnabled = m_shouldFilterBeEnabled;
    m_shouldFilterBeEnabled = (m_sampleRate <= 192000);
    
    if (m_shouldFilterBeEnabled != m_previousShouldFilterBeEnabled) 
    {
        bool filterStateToSet = false;

        if (m_shouldFilterBeEnabled)
        {
            filterStateToSet = m_userRequestedState;
        }
        else
        {
            filterStateToSet = false;
        }

        applyFilterState(filterStateToSet);
    }
}

void FilterManager::setFilterEnabled(bool enabled) 
{
    m_userRequestedState = enabled;

    if (enabled != m_filterEnabled) 
    {
        applyFilterState(m_shouldFilterBeEnabled ? enabled : false);

    }
}

bool FilterManager::isFilterActive() const {
    return m_filterEnabled;
}

void FilterManager::applyFilterState(bool enable) 
{
    // Apply the hardware change
    if (enable) {
        m_hardware.enableFilter();
    } else {
        m_hardware.disableFilter();
    }
    
    // Update our internal state
    m_filterEnabled = enable;
}
