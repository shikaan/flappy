Latebit Template
===

Welcome to Latebit! 

Latebit is a game engine for pixel-based 2D games with a focus on developer experience.

This template provides a quick start for creating games with [Latebit](https://github.com/latebit/latebit-engine). 
It show examples of the fundamental capabilities of the engine and includes everything you need to begin your game development journey.

## Quick Start

### Dependencies

- C++20 compatible compiler (e.g., [LLVM/Clang](https://releases.llvm.org/) >=14)
- [CMake](https://cmake.org/download/) >=3.28.1
- (for WASM builds) [emscripten](https://emscripten.org/) >=3.1.51

### Option 1: Using Latebit Studio (Recommended)

1. Install [Visual Studio Code](https://code.visualstudio.com/)
2. Install the [Latebit Studio extension](https://github.com/latebit/latebit-studio-vscode)
3. (Optional) Install the [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension 
4. Clone and open the template:
   ```sh
   git clone https://github.com/latebit/latebit-template.git
   code latebit-template
   ```
5. Open the command palette and select `latebit: Run current game` 
   ![command palette example](https://github.com/latebit/latebit-studio-vscode/assets/17052868/a9ae5cbe-6d8d-4137-92c3-06be12feb63f)

### Option 2: Command Line

1. Clone the repository:
   ```sh
   git clone https://github.com/latebit/latebit-template.git
   cd latebit-template
   ```

2. Build and run the game:
   ```sh
   # Native build
   cmake -B build && cmake --build build && ./build/latebit_template
   # WASM build
   emcmake cmake -B build && emmake cmake --build build && emrun build/public
   ```

## What's Included

- Latebit engine integration
- CMake setup for native and WASM builds
- Example assets (sprites, audio) and configurations
- Basic project structure to kickstart your game

## Next Steps

1. Head over to `src/main.cpp` and follow the in-code instructions
2. Check out the [Latebit documentation](https://github.com/latebit/latebit-engine/wiki) for detailed guides

Happy game development with Latebit!