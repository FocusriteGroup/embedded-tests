# Audio Filter Manager - Technical Test

Welcome to the Audio Filter Manager technical test! This exercise is designed to assess your ability to debug, test, and improve C++ code in an embedded audio context.

## Background

You've been asked to fix a bug in a filter management system for an audio interface. The `FilterManager` class is responsible for:
- Enabling/disabling an audio filter based on sample rate
- Coordinating with hardware to control the filter state
- Managing DSP muting/unmuting during filter transitions

## The Problem

The current implementation has a bug: **the filter is being engaged at 192kHz sample rate when it should NOT be active at this rate.**

According to the specification:
- The filter should only be active at sample rates **below 192kHz**
- At 192kHz and above, the filter should remain disabled
- The DSP should be muted during filter state transitions to prevent audio artifacts

## Your Task

1. **Run the tests** to see the failing test case
2. **Identify the bug** in the `FilterManager` implementation
3. **Fix the bug** so all tests pass
4. **Bonus**: Consider if there are any other edge cases or improvements needed

## Project Structure

```
Interview/
├── README.md                    # This file
├── Justfile                     # Build automation commands
├── CMakeLists.txt              # CMake build configuration
├── include/
│   ├── IHardwareInterface.h    # Hardware abstraction interface
│   ├── IDspInterface.h         # DSP control interface
│   ├── FilterManager.h         # Main filter manager class
│   └── mocks/
│       ├── MockHardwareInterface.h  # Mock for testing
│       └── MockDspInterface.h       # Mock for testing
├── src/
│   └── FilterManager.cpp       # Implementation (contains the bug!)
└── tests/
    └── FilterManagerTests.cpp  # Test suite with failing test
```

## Getting Started

### Prerequisites

This project uses GitHub Codespaces, which provides a pre-configured development environment. Everything you need is already installed!

If running locally, you'll need:
- CMake 3.20+
- A C++17 compatible compiler (GCC, Clang, or MSVC)
- Just (command runner - optional but recommended)

### Building and Running Tests

We've provided a `Justfile` to make building and testing simple:

```bash
# Build the project
just build

# Run the tests
just test

# Clean and rebuild
just clean
just build

# See all available commands
just --list
```

### Without Just

If you prefer to use CMake directly:

```bash
# Configure
cmake -B build -DCMAKE_BUILD_TYPE=Debug

# Build
cmake --build build

# Run tests
cd build && ctest --output-on-failure
```

## Understanding the Code

### FilterManager

The `FilterManager` class has the following key methods:

- `setSampleRate(uint32_t sampleRate)` - Updates the sample rate and determines if filter should be active
- `setFilterEnabled(bool enabled)` - Explicitly enables/disables the filter
- `isFilterActive()` - Returns whether the filter is currently engaged

### Hardware and DSP Interfaces

The system uses two interfaces for hardware interaction:

- `IHardwareInterface` - Controls the physical filter hardware
- `IDspInterface` - Controls DSP muting (prevents clicks/pops during transitions)

### Test Strategy

The test suite uses:
- **Catch2** - Modern C++ testing framework
- **Mock objects** - To verify interactions with hardware/DSP without real hardware

## Evaluation Criteria

We're looking for:

1. **Problem Solving** - Can you identify and fix the bug?
2. **Code Quality** - Is your fix clean and maintainable?
3. **Testing** - Do you understand the test cases?
4. **Communication** - Can you explain your findings?

## Questions?

Feel free to ask clarifying questions during the interview. Good luck!

## Hints

<details>
<summary>Click here if you need a hint</summary>

- Look carefully at the sample rate comparison logic in `FilterManager::setSampleRate()`
- What sample rates should allow the filter to be active?
- Are the comparison operators correct?

</details>
