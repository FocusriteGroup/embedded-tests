# Audio Filter Manager - Just Commands
# Use 'just --list' to see all available commands

# Default recipe - show help
default:
    @just --list

# Configure the build directory
configure:
    cmake -B build -DCMAKE_BUILD_TYPE=Debug

# Build the project
build: configure
    cmake --build build

# Run all tests
test: build
    cd build && ctest --output-on-failure

# Run tests with verbose output
test-verbose: build
    cd build && ctest --output-on-failure --verbose

# Clean build artifacts
clean:
    rm -rf build

# Rebuild everything from scratch
rebuild: clean build

# Run the tests and show detailed output
run-tests: build
    ./build/FilterManagerTests

# Open VS Code debugger (use F5 or Debug menu in VS Code)
debug: build
    @echo "VS Code debugger configured!"
    @echo ""
    @echo "To debug in VS Code:"
    @echo "  1. Open the Run and Debug panel (Cmd+Shift+D / Ctrl+Shift+D)"
    @echo "  2. Select a debug configuration from the dropdown:"
    @echo "     • Debug All Tests"
    @echo "  3. Set breakpoints in the code (click left of line numbers)"
    @echo "  4. Press F5 to start debugging"
    @echo ""
