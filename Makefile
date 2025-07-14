# Makefile for Star War game on macOS

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SFML_PATH = /opt/homebrew/opt/sfml@2
SFML_FLAGS = -I$(SFML_PATH)/include -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Directories
SRC_DIR = Star\ War3.0/Star\ War3.0
BUILD_DIR = build
ASSET_DIRS = Star\ War3.0/Release/Textures Star\ War3.0/Release/Audio Star\ War3.0/Release/Fonts

# Source files
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/Game.cpp \
          $(SRC_DIR)/Player.cpp \
          $(SRC_DIR)/Bullet.cpp \
          $(SRC_DIR)/Enemy.cpp \
          $(SRC_DIR)/eBullets.cpp \
          $(SRC_DIR)/Animation.cpp \
          $(SRC_DIR)/Background.cpp \
          $(SRC_DIR)/Boss.cpp \
          $(SRC_DIR)/Bomber.cpp \
          $(SRC_DIR)/Buff.cpp \
          $(SRC_DIR)/Collision.cpp \
          $(SRC_DIR)/Menu.cpp \
          $(SRC_DIR)/Textbox.cpp

# Target executable
TARGET = StarWar

.PHONY: all clean run copy-assets

all: $(BUILD_DIR) copy-assets $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(BUILD_DIR)/$(TARGET) $(SFML_FLAGS)

copy-assets: $(BUILD_DIR)
	cp -r $(ASSET_DIRS) $(BUILD_DIR)/

clean:
	rm -rf $(BUILD_DIR)

run: all
	cd $(BUILD_DIR) && ./$(TARGET)

install-deps:
	brew install sfml

.DEFAULT_GOAL := all
