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

    SECTION("disables filter at 192kHz") {
        manager.setSampleRate(192000);
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

    }

    SECTION("mutes and unmutes when disabling filter") {

    }

    SECTION("does not mute if sample rate doesn't change filter state") {

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

    }
}
