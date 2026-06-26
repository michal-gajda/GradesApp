SHELL := pwsh.exe
.SHELLFLAGS := -NoProfile -Command

SRC_DIR := .
BUILD_DIR := build/make
CONFIG ?= Debug
QT_PREFIX_PATH ?= C:/Workspaces/Tools/Qt/6.10.2/msvc2022_64
CMAKE_GENERATOR ?= Visual Studio 17 2022
CMAKE_ARCH ?= x64
APP_NAME := GradesApp
APP_EXE := $(BUILD_DIR)/$(CONFIG)/$(APP_NAME).exe

.PHONY: build configure run clean

configure:
	cmake -S $(SRC_DIR) -B $(BUILD_DIR) -G "$(CMAKE_GENERATOR)" -A $(CMAKE_ARCH) -DCMAKE_PREFIX_PATH="$(QT_PREFIX_PATH)"

build: configure
	cmake --build $(BUILD_DIR) --config $(CONFIG) --target $(APP_NAME)

run: build
	$$env:Path = "$(QT_PREFIX_PATH)/bin;" + $$env:Path; Start-Process -FilePath "$(APP_EXE)" -WorkingDirectory "$(BUILD_DIR)/$(CONFIG)"

clean:
	if (Test-Path "$(BUILD_DIR)") { Remove-Item -Recurse -Force "$(BUILD_DIR)" }
