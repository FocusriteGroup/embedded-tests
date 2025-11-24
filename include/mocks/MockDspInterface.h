#pragma once

#include "IDspInterface.h"
#include <vector>
#include <string>

/**
 * @brief Mock implementation of IDspInterface for testing
 * 
 * This mock allows tests to verify that the FilterManager correctly
 * mutes/unmutes audio during filter state transitions.
 */
class MockDspInterface : public IDspInterface {
public:
    MockDspInterface() : m_muted(false) {}

    void mute() override {
        m_muted = true;
        m_callHistory.push_back("mute");
    }

    void unmute() override {
        m_muted = false;
        m_callHistory.push_back("unmute");
    }

    bool isMuted() const override {
        return m_muted;
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
    bool m_muted;
    std::vector<std::string> m_callHistory;
};
