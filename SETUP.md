# 🌟 Star War Game - macOS Quick Setup Guide

## TL;DR - Quick Start

1. **Install dependencies:**
   ```bash
   brew install sfml@2
   ```

2. **Run the game:**
   ```bash
   ./play.sh
   ```

That's it! The launcher script will handle building and running the game.

## Manual Setup (Alternative)

If you prefer to build manually:

```bash
# Build the game
make clean && make

# Run the game
make run
```

## What We Fixed for macOS

✅ **SFML Compatibility**: Switched from SFML 3.x to SFML 2.x  
✅ **Include Paths**: Fixed Windows backslashes to Unix forward slashes  
✅ **Window Mode**: Changed from fullscreen to windowed (1280x720)  
✅ **Build System**: Added Makefile and CMake support  
✅ **Type Casting**: Fixed floating-point division issues  
✅ **Asset Copying**: Automated texture, audio, and font file copying  

## Game Features

- 🚀 Classic space shooter gameplay
- 👾 Multiple enemy types including bosses
- 🎵 Background music and sound effects  
- 🎮 Single and two-player modes
- 💥 Particle effects and animations
- 🏆 Scoring system

## Requirements

- macOS (any recent version)
- Homebrew package manager
- ~50MB free space

## Troubleshooting

**Game won't start?**
- Run `./play.sh` - it will install dependencies automatically

**No sound?**
- Check your system volume
- Ensure audio files are in `build/Audio/`

**Graphics issues?**
- Try running from terminal to see error messages
- Ensure all textures are in `build/Textures/`

## Technical Stack

- **Language**: C++17
- **Graphics**: SFML 2.6.2
- **Platform**: macOS (ARM64 & Intel)
- **Build**: Make/CMake

---

🎮 **Ready to play?** Run `./play.sh` and enjoy!
