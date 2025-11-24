#pragma once

#include "IHardwareInterface.h"
#include <vector>
#include <string>

/**
 * @brief Mock implementation of IHardwareInterface for testing
 * 
 * This mock allows tests to verify that the FilterManager correctly
 * interacts with the hardware interface without requiring real hardware.
 */
class MockHardwareInterface : public IHardwareInterface {
public:
    MockHardwareInterface() : m_filterEnabled(false) {}

    void enableFilter() override {
        m_filterEnabled = true;
        m_callHistory.push_back("enableFilter");
    }

    void disableFilter() override {
        m_filterEnabled = false;
        m_callHistory.push_back("disableFilter");
    }

    bool isFilterEnabled() const override {
        return m_filterEnabled;
    }

    // Test helper methods
    const std::vector<std::string>& getCallHistory() const {
        return m_callHistory;
    }

    void clearCallHistory() {
        m_callHistory.clear();
    }

    size_t getCallCount() const {
        return m_callHistory.size();
    }

private:
    bool m_filterEnabled;
    std::vector<std::string> m_callHistory;
};
