# Audio Filter Manager - Technical Test

Welcome to the Audio Filter Manager technical test! This exercise is designed to assess your ability to debug, test, and improve C++ code in an embedded audio context.

## Background

You've been asked to do some development in filter management system for an audio interface. 
The `FilterManager` class is responsible for:
- Enabling/disabling an audio filter based on sample rate
- Coordinating with hardware to control the filter state
- Managing DSP muting/unmuting during filter transitions

## Your Tasks

Please work through each task sequentially.

1. **Run the tests** to check the current state of the project
2. **Implement** the muting functionality:
    - Mute the signal before the filter state is changed
    - Unmute the signal once the filter state is changed
    - This should only happen when the filter state is changed
3. **Implement hardware specific behaviour**:
    - A product has been designed that has a different filter circuit
    - This circuit needs the software to wait **2 seconds** before unmuting the signal
    - Please implement the necessary code and API to provide this functionality from the class
    - You should allow for other muting time periods in the future
    - You should add the necessary tests to validate this functionality
    - You can assume that the client calling this class has a way of managing time
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
│   └── FilterManager.cpp       # Implementation
└── tests/
    └── FilterManagerTests.cpp  # Test suite
```

## Getting Started

### Prerequisites

This project uses GitHub Codespaces, which provides a pre-configured development environment. Everything you need is already installed!

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

### Debugging with VS Code

The project is pre-configured for VS Code debugging. This works in both Codespaces and local VS Code:

#### Quick Start
1. Open the **Run and Debug** panel (`Cmd+Shift+D` or `Ctrl+Shift+D`)
2. Select **Debug All Tests** from the dropdown
3. Press **F5** to start debugging
4. Use the debug toolbar to step through code

#### Debug Tips
- Click left of line numbers to set/remove breakpoints
- Hover over variables to see their values
- Use the Debug Console to evaluate expressions
- Step Over (F10), Step Into (F11), Continue (F5)

Or run `just debug` for instructions.

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

1. **Problem Solving** - Can you work through each task and achieve the desired outcome
2. **Code Quality** - Is your fix clean and maintainable?
3. **Testing** - Do you understand the test cases?
4. **Communication** - Can you explain your findings and discuss your approach?

## Questions?

Feel free to ask clarifying questions during the interview. Good luck!