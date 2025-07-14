# Star War Game - macOS Setup and Play Guide

This guide will help you set up and run the Star War game on macOS.

## Prerequisites

- macOS (tested on macOS Sequoia)
- Homebrew package manager
- Command line tools (Xcode)

## Installation and Setup

### 1. Install Dependencies

First, install SFML 2.x which is required for the game:

```bash
brew install sfml@2
```

### 2. Build the Game

Navigate to the project directory and build using the provided Makefile:

```bash
cd "/path/to/Star-War"
make clean && make
```

This will:
- Compile all C++ source files
- Link with SFML libraries
- Copy game assets (textures, audio, fonts) to the build directory
- Create the `StarWar` executable in the `build/` directory

### 3. Run the Game

Run the game using:

```bash
make run
```

Or manually:

```bash
cd build && ./StarWar
```

## Game Controls

The game uses keyboard controls. The specific controls will be shown in the game's menu or instructions.

## Build System Options

### Using Makefile (Recommended)
```bash
make                    # Build the game
make clean             # Clean build files
make run               # Build and run the game
make install-deps      # Install SFML dependencies
```

### Using CMake (Alternative)
```bash
mkdir build && cd build
cmake ..
make
```

## Troubleshooting

### Missing Textures
If you see "Failed to load image" errors, ensure all texture files are in the `build/Textures/` directory. Some textures might need to be created manually.

### Audio Issues
Ensure audio files are in the `build/Audio/` directory and that your system has audio output enabled.

### Font Issues
Font files should be in the `build/Fonts/` directory. If fonts fail to load, the game may use system defaults.

### SFML Version Issues
This game requires SFML 2.x. If you accidentally installed SFML 3.x:
```bash
brew uninstall sfml
brew install sfml@2
```

## Technical Details

- **Language**: C++17
- **Graphics Library**: SFML 2.6.2
- **Build System**: Makefile/CMake
- **Window Mode**: 1280x720 (modified from original fullscreen for better macOS compatibility)

## Changes Made for macOS Compatibility

1. **SFML Includes**: Fixed Windows-style backslashes to Unix forward slashes
2. **Window Mode**: Changed from fullscreen to windowed mode for easier development/testing
3. **Build System**: Added Makefile and CMakeLists.txt for macOS building
4. **Type Casting**: Fixed floating-point division compatibility issues

## Project Structure

```
Star-War/
├── build/                   # Build output directory
│   ├── StarWar             # Game executable
│   ├── Textures/           # Game textures
│   ├── Audio/              # Game audio files
│   └── Fonts/              # Game fonts
├── Star War3.0/            # Original source code
├── CMakeLists.txt          # CMake build configuration
├── Makefile                # Make build configuration
└── README.md               # This file
```

## Known Issues

- Some original texture files may be missing (e.g., "Han.png")
- Compilation warnings about unused parameters and initializer order (non-critical)
- Game was originally designed for Windows and may have some UI scaling differences on macOS

## Contributing

When making changes:
1. Test compilation on macOS
2. Ensure all assets are copied to build directory
3. Verify game runs without errors

## Original Credits

This is a port of the original Star War 3.0 game to macOS. The original game was built for Windows using Visual Studio.
