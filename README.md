# SandSlope

AR Sandbox Ski Resort with Terrain-Driven Ski Runs

## Setup (macOS only)

### 1. Install dependencies

```sh
brew install cmake glfw glm libfreenect
```

### 2. Build and run

From the project root:

```sh
cmake -S . -B build     # configure (run once, or after changing CMakeLists.txt)
cmake --build build     # compile
./build/SandSlope       # run from the project root
```
