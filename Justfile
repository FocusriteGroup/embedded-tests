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

# Format code (if clang-format is available)
format:
    @if command -v clang-format >/dev/null 2>&1; then \
        find include src tests -name "*.h" -o -name "*.cpp" | xargs clang-format -i; \
        echo "Code formatted successfully"; \
    else \
        echo "clang-format not found, skipping formatting"; \
    fi
