#!/bin/bash
# Star War Game Launcher for macOS

echo "🌟 Star War Game Launcher for macOS 🌟"
echo "========================================"

# Check if SFML is installed
if ! brew list sfml@2 &> /dev/null; then
    echo "❌ SFML 2.x is not installed. Installing now..."
    brew install sfml@2
    if [ $? -ne 0 ]; then
        echo "❌ Failed to install SFML. Please install Homebrew first."
        exit 1
    fi
    echo "✅ SFML installed successfully!"
fi

# Build the game
echo "🔨 Building the game..."
make clean && make

if [ $? -ne 0 ]; then
    echo "❌ Build failed. Please check the error messages above."
    exit 1
fi

echo "✅ Build successful!"

# Check for missing textures and create placeholders
echo "🎨 Checking for missing textures..."
if [ ! -f "build/Textures/Han.png" ]; then
    echo "⚠️  Creating placeholder for missing Han.png texture..."
    cp "build/Textures/son.png" "build/Textures/Han.png" 2>/dev/null || echo "Could not create Han.png placeholder"
fi

# Run the game
echo "🚀 Launching Star War..."
echo ""
echo "Game Controls:"
echo "  - Use keyboard to control (controls will be shown in game)"
echo "  - Close the game window to exit"
echo ""
echo "Press Enter to start the game..."
read

cd build && ./StarWar

echo ""
echo "🌟 Thanks for playing Star War! 🌟"
