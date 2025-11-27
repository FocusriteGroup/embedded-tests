#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "FilterManager.h"
#include "mocks/MockHardwareInterface.h"
#include "mocks/MockDspInterface.h"

TEST_CASE("FilterManager initialization", "[FilterManager]") 
{
    MockHardwareInterface hardware;
    MockDspInterface dsp;
    FilterManager manager(hardware, dsp);

    SECTION("starts with default sample rate") 
    {
        REQUIRE(manager.getSampleRate() == 48000);
    }

    SECTION("starts with filter inactive") 
    {
        REQUIRE_FALSE(manager.isFilterActive());
    }
}

TEST_CASE("FilterManager sample rate behavior", "[FilterManager]") 
{
    MockHardwareInterface hardware;
    MockDspInterface dsp;
    FilterManager manager(hardware, dsp);

    manager.setFilterEnabled(true);

    SECTION("enables filter at 44.1kHz") 
    {
        manager.setSampleRate(44100);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("enables filter at 48kHz") 
    {
        manager.setSampleRate(48000);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("enables filter at 96kHz") 
    {
        manager.setSampleRate(96000);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("disables filter at 192kHz") 
    {
        manager.setSampleRate(192000);
        REQUIRE_FALSE(manager.isFilterActive());
        REQUIRE_FALSE(hardware.isFilterEnabled());
    }

    SECTION("disables filter at 384kHz") 
    {
        manager.setSampleRate(384000);
        REQUIRE_FALSE(manager.isFilterActive());
        REQUIRE_FALSE(hardware.isFilterEnabled());
    }

    SECTION("enables filter when returning to 48kHz") 
    {
        manager.setSampleRate(48000);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }
}

TEST_CASE("FilterManager enable behavior", "[FilterManager]") 
{
    MockHardwareInterface hardware;
    MockDspInterface dsp;
    FilterManager manager(hardware, dsp);

    SECTION("enables filter when setFilterEnabled is called") 
    {
        manager.setSampleRate(48000);
        manager.setFilterEnabled(true);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("disabled filter when setFilterEnabled is called with false") 
    {
        manager.setSampleRate(48000);
        manager.setFilterEnabled(false);
        REQUIRE_FALSE(manager.isFilterActive());
        REQUIRE_FALSE(hardware.isFilterEnabled());
    }

    SECTION("doesn't enable filter if sample rate is too high") 
    {
        manager.setSampleRate(192000);
        manager.setFilterEnabled(true);
        REQUIRE_FALSE(manager.isFilterActive());
        REQUIRE_FALSE(hardware.isFilterEnabled());
    }

    SECTION("enables filter if valid sample rate is set") 
    {
        manager.setSampleRate(192000);
        manager.setFilterEnabled(true);
        manager.setSampleRate(48000);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }
}


TEST_CASE("FilterManager mutes during transitions", "[FilterManager]") 
{
    MockHardwareInterface hardware;
    MockDspInterface dsp;
    FilterManager manager(hardware, dsp);

    SECTION("mutes and unmutes when enabling filter") 
    {

    }

    SECTION("mutes and unmutes when disabling filter") 
    {

    }

    SECTION("does not mute if sample rate doesn't change filter state") 
    {


    }
}

