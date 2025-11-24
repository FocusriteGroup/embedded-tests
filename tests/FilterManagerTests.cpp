#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "FilterManager.h"
#include "mocks/MockHardwareInterface.h"
#include "mocks/MockDspInterface.h"

TEST_CASE("FilterManager initialization", "[FilterManager]") {
    MockHardwareInterface hardware;
    MockDspInterface dsp;
    FilterManager manager(hardware, dsp);

    SECTION("starts with default sample rate") {
        REQUIRE(manager.getSampleRate() == 48000);
    }

    SECTION("starts with filter inactive") {
        REQUIRE_FALSE(manager.isFilterActive());
    }
}

TEST_CASE("FilterManager sample rate behavior", "[FilterManager]") {
    MockHardwareInterface hardware;
    MockDspInterface dsp;
    FilterManager manager(hardware, dsp);

    SECTION("enables filter at 44.1kHz") {
        manager.setSampleRate(44100);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("enables filter at 48kHz") {
        manager.setSampleRate(48000);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("enables filter at 96kHz") {
        manager.setSampleRate(96000);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("disables filter at 192kHz - THIS TEST FAILS!") {
        // According to the specification, the filter should NOT be active at 192kHz
        manager.setSampleRate(192000);
        
        // This test will FAIL because the current implementation incorrectly
        // enables the filter at 192kHz (using <= instead of <)
        REQUIRE_FALSE(manager.isFilterActive());
        REQUIRE_FALSE(hardware.isFilterEnabled());
    }

    SECTION("disables filter at 384kHz") {
        manager.setSampleRate(384000);
        REQUIRE_FALSE(manager.isFilterActive());
        REQUIRE_FALSE(hardware.isFilterEnabled());
    }
}

TEST_CASE("FilterManager mutes during transitions", "[FilterManager]") {
    MockHardwareInterface hardware;
    MockDspInterface dsp;
    FilterManager manager(hardware, dsp);

    SECTION("mutes and unmutes when enabling filter") {
        dsp.clearCallHistory();
        
        manager.setSampleRate(48000);
        
        auto& calls = dsp.getCallHistory();
        REQUIRE(calls.size() >= 2);
        REQUIRE(calls[0] == "mute");
        REQUIRE(calls[calls.size() - 1] == "unmute");
    }

    SECTION("mutes and unmutes when disabling filter") {
        // First enable the filter
        manager.setSampleRate(48000);
        dsp.clearCallHistory();
        
        // Now disable it
        manager.setSampleRate(384000);
        
        auto& calls = dsp.getCallHistory();
        REQUIRE(calls.size() >= 2);
        REQUIRE(calls[0] == "mute");
        REQUIRE(calls[calls.size() - 1] == "unmute");
    }

    SECTION("does not mute if sample rate doesn't change filter state") {
        manager.setSampleRate(48000);
        dsp.clearCallHistory();
        
        // Change sample rate but keep filter enabled
        manager.setSampleRate(96000);
        
        // Should not have called mute/unmute since filter state didn't change
        REQUIRE(dsp.getCallCount() == 0);
    }
}

TEST_CASE("FilterManager manual control", "[FilterManager]") {
    MockHardwareInterface hardware;
    MockDspInterface dsp;
    FilterManager manager(hardware, dsp);

    SECTION("can manually enable filter") {
        manager.setFilterEnabled(true);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("can manually disable filter") {
        manager.setFilterEnabled(true);
        manager.setFilterEnabled(false);
        REQUIRE_FALSE(manager.isFilterActive());
        REQUIRE_FALSE(hardware.isFilterEnabled());
    }

    SECTION("mutes during manual state changes") {
        dsp.clearCallHistory();
        
        manager.setFilterEnabled(true);
        
        auto& calls = dsp.getCallHistory();
        REQUIRE(calls.size() >= 2);
        REQUIRE(calls[0] == "mute");
        REQUIRE(calls[calls.size() - 1] == "unmute");
    }
}

TEST_CASE("FilterManager edge cases", "[FilterManager]") {
    MockHardwareInterface hardware;
    MockDspInterface dsp;
    FilterManager manager(hardware, dsp);

    SECTION("handles repeated sample rate changes correctly") {
        manager.setSampleRate(48000);
        REQUIRE(hardware.isFilterEnabled());
        
        manager.setSampleRate(192000);
        // This will fail due to the bug
        REQUIRE_FALSE(hardware.isFilterEnabled());
        
        manager.setSampleRate(96000);
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("doesn't change hardware state unnecessarily") {
        hardware.clearCallHistory();
        
        manager.setSampleRate(48000);
        size_t callCount1 = hardware.getCallCount();
        
        // Set to same state - should not trigger hardware calls
        manager.setSampleRate(96000);
        size_t callCount2 = hardware.getCallCount();
        
        REQUIRE(callCount1 == callCount2);
    }
}
