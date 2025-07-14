cmake_minimum_required(VERSION 3.16)
project(StarWar)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set SFML path
set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)

# Source files
set(SOURCES
    "Star War3.0/Star War3.0/main.cpp"
    "Star War3.0/Star War3.0/Game.cpp"
    "Star War3.0/Star War3.0/Player.cpp"
    "Star War3.0/Star War3.0/Bullet.cpp"
    "Star War3.0/Star War3.0/Enemy.cpp"
    "Star War3.0/Star War3.0/eBullets.cpp"
    "Star War3.0/Star War3.0/Animation.cpp"
    "Star War3.0/Star War3.0/Background.cpp"
    "Star War3.0/Star War3.0/Boss.cpp"
    "Star War3.0/Star War3.0/Bomber.cpp"
    "Star War3.0/Star War3.0/Buff.cpp"
    "Star War3.0/Star War3.0/Collision.cpp"
    "Star War3.0/Star War3.0/Menu.cpp"
    "Star War3.0/Star War3.0/Textbox.cpp"
)

# Create executable
add_executable(StarWar ${SOURCES})

# Link SFML libraries
target_link_libraries(StarWar sfml-graphics sfml-window sfml-system sfml-audio)

# Copy assets to build directory
file(COPY "Star War3.0/Release/Textures" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "Star War3.0/Release/Audio" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "Star War3.0/Release/Fonts" DESTINATION ${CMAKE_BINARY_DIR})

# Set working directory for assets
set_target_properties(StarWar PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
