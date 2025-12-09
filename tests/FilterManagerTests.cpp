#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "FilterManager.h"
#include "mocks/MockHardwareInterface.h"
#include "mocks/MockDspInterface.h"

TEST_CASE("FilterManager initialisation", "[FilterManager]") 
{
    MockHardwareInterface hardware;
    MockDspInterface dsp;
    FilterManager manager(hardware, dsp);

    SECTION("filter initial sample rate is 48kHz") 
    {
        REQUIRE(manager.getSampleRate() == 48000);
    }

    SECTION("filter is initially not active") 
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

    SECTION("44.1kHz sample rate enables filter") 
    {
        manager.setSampleRate(44100);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("48kHz sample rate enables filter")  
    {
        manager.setSampleRate(48000);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("96kHz sample rate enables filter")  
    {
        manager.setSampleRate(96000);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("192kHz sample rate disables filter") 
    {
        manager.setSampleRate(192000);
        REQUIRE_FALSE(manager.isFilterActive());
        REQUIRE_FALSE(hardware.isFilterEnabled());
    }

    SECTION("384kHz sample rate disables filter") 
    {
        manager.setSampleRate(384000);
        REQUIRE_FALSE(manager.isFilterActive());
        REQUIRE_FALSE(hardware.isFilterEnabled());
    }

    SECTION("48kHz sample rate enables filter after being disabled") 
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

    SECTION("filter enables when setFilterEnabled is called") 
    {
        manager.setSampleRate(48000);
        manager.setFilterEnabled(true);
        REQUIRE(manager.isFilterActive());
        REQUIRE(hardware.isFilterEnabled());
    }

    SECTION("filter disables when setFilterEnabled is called with false") 
    {
        manager.setSampleRate(48000);
        manager.setFilterEnabled(false);
        REQUIRE_FALSE(manager.isFilterActive());
        REQUIRE_FALSE(hardware.isFilterEnabled());
    }

    SECTION("filter does not enable if sample rate is too high") 
    {
        manager.setSampleRate(192000);
        manager.setFilterEnabled(true);
        REQUIRE_FALSE(manager.isFilterActive());
        REQUIRE_FALSE(hardware.isFilterEnabled());
    }

    SECTION("filter does enable if valid sample rate is set") 
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

