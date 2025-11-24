#pragma once

/**
 * @brief Interface for hardware filter control
 * 
 * This interface abstracts the hardware-specific operations for controlling
 * the audio filter. Implementations should handle the low-level register
 * writes or hardware communication required to enable/disable the filter.
 */
class IHardwareInterface {
public:
    virtual ~IHardwareInterface() = default;

    /**
     * @brief Enable the hardware filter
     * 
     * This method should configure the hardware to enable the audio filter.
     * The filter may take some time to stabilize after enabling.
     */
    virtual void enableFilter() = 0;

    /**
     * @brief Disable the hardware filter
     * 
     * This method should configure the hardware to disable the audio filter,
     * allowing audio to pass through unfiltered.
     */
    virtual void disableFilter() = 0;

    /**
     * @brief Check if the filter is currently enabled in hardware
     * 
     * @return true if the filter is enabled, false otherwise
     */
    virtual bool isFilterEnabled() const = 0;
};
