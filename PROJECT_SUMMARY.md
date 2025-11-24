# Audio Filter Manager - Technical Interview Test

## Project Summary

A C++ technical interview exercise focused on debugging an audio filter management system. The project includes a deliberate bug that candidates must identify and fix.

## What's Included

### Core Implementation
- `FilterManager` class - Manages filter state based on sample rate
- `IHardwareInterface` - Hardware abstraction layer
- `IDspInterface` - DSP muting control
- Mock implementations for testing

### Test Suite
- Comprehensive Catch2 test suite
- Tests that demonstrate the bug (2 failing tests)
- Tests for edge cases and proper behavior

### Development Environment
- CMake build system
- Justfile for easy commands (`just build`, `just test`)
- GitHub Codespaces configuration for zero-setup interviews
- Works on macOS, Linux, and Windows

### Documentation
- `README.md` - Candidate instructions
- `ANSWER_KEY.md` - Solution and evaluation guide (for interviewers)
- `SETUP_GUIDE.md` - GitHub setup instructions (for interviewers)

## The Bug

The filter incorrectly enables at 192kHz when it should be disabled. The bug is a simple but realistic off-by-one error in a comparison operator (`<=` instead of `<`).

## Project Structure

```
Interview/
├── README.md                           # Candidate instructions
├── ANSWER_KEY.md                       # Solution (for interviewers)
├── SETUP_GUIDE.md                      # GitHub setup (for interviewers)
├── Justfile                            # Build commands
├── CMakeLists.txt                      # Build configuration
├── .devcontainer/
│   └── devcontainer.json               # Codespaces config
├── include/
│   ├── IHardwareInterface.h            # Hardware interface
│   ├── IDspInterface.h                 # DSP interface
│   ├── FilterManager.h                 # Main class header
│   └── mocks/
│       ├── MockHardwareInterface.h     # Test mock
│       └── MockDspInterface.h          # Test mock
├── src/
│   └── FilterManager.cpp               # Implementation (with bug)
└── tests/
    └── FilterManagerTests.cpp          # Test suite
```

## Quick Commands

```bash
just build      # Build the project
just test       # Run tests (shows 2 failures)
just clean      # Clean build artifacts
just rebuild    # Clean and rebuild
```

## Evaluation Criteria

✅ Can they run the tests and understand the failure?  
✅ Can they identify the bug in the code?  
✅ Can they fix it correctly?  
✅ Can they explain their reasoning?  
✅ Do they verify the fix works?  

## Time Estimates

- **Junior**: 15-30 minutes
- **Mid-level**: 10-20 minutes  
- **Senior**: 5-15 minutes

## Next Steps

1. Push this repository to GitHub
2. Enable Codespaces (automatic with included config)
3. Share the repository link with candidates
4. Review `ANSWER_KEY.md` before the interview
5. Follow `SETUP_GUIDE.md` for detailed setup instructions

## License

This is an internal interview test. Keep the repository private to prevent solution sharing.
