# Sketcher

Sketcher is a desktop drawing application built with C++ and Qt 6. It provides a canvas for drawing lines and circles, undo/redo support, SVG import/export, and runtime loading of shape plugins.

## Features

- Draw **lines** and **circles** on a canvas
- Undo and redo drawing actions
- Clear the canvas
- Open existing SVG files
- Save drawings as SVG files
- Close an open SVG file
- Load compatible shape plugins at runtime
- Includes a sample **Rectangle** plugin

## Built With

- C++
- Qt 6.5 or newer
- CMake 3.19 or newer
- Qt Widgets, Core, SVG, and XML modules

## Prerequisites

Install:

- A C++ compiler with C++17 support
- CMake 3.19+
- Qt 6.5+

Qt must include the Widgets, Core, Svg, and Xml components.

## Build

### Linux

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/Qt/6.5-or-newer
cmake --build build --parallel
```

Run the application:

```bash
./build/Sketcher
```

### Windows

From a terminal configured for Qt and your C++ compiler:

```powershell
cmake -S . -B build -DCMAKE_PREFIX_PATH="C:/Qt/6.5.*/msvc*/lib/cmake/Qt6"
cmake --build build --config Release
```

The executable is usually generated under:

```text
build/Release/Sketcher.exe
```

### macOS

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/Qt/6.5-or-newer
cmake --build build --parallel
open build/Sketcher.app
```

## Usage

1. Launch Sketcher.
2. Select **Line** or **Circle** from the toolbar.
3. Drag across the canvas to draw the selected shape.
4. Use **Undo**, **Redo**, or **Clear** to manage the drawing.
5. Use **Save** to export the drawing to an SVG file.
6. Use **Open** to load an existing SVG file.
7. Use **Close SVG** to return to the editing canvas.

## Plugins

Sketcher supports loading shape plugins at runtime. A plugin must implement `SketcherPluginInterface` and expose the Qt plugin interface metadata:

- Interface identifier: `com.sketcher.plugin`
- Required methods:
  - `draw(QPainter&, const QPoint&, const QPoint&)`
  - `shapeName()`

The repository includes `RectanglePlugin`, which builds as a shared library:

- `plugins/RectanglePlugin.dll` on Windows
- `plugins/libRectanglePlugin.so` on Linux
- `plugins/libRectanglePlugin.dylib` on macOS

To use it:

1. Build the project.
2. Select **Load Plugin**.
3. Choose the generated plugin library.
4. Select the plugin's shape name from the toolbar.

## Project Structure

```text
.
├── CMakeLists.txt                 # CMake project configuration
├── main.cpp                       # Application entry point
├── mainwindow.cpp/.h/.ui          # Main Qt window and toolbar
├── DrawingArea.cpp/.h             # Canvas, drawing, undo/redo, and SVG handling
├── SketcherPluginInterface.h      # Interface for external shape plugins
├── RectanglePlugin.cpp/.h         # Example rectangle plugin
├── one.svg / two.svg              # Example SVG files
└── CMakePresets.json              # CMake preset metadata
```

## Contributing

Contributions are welcome.

1. Fork the repository.
2. Create a feature branch.
3. Commit your changes.
4. Open a pull request.

## License

No license is currently specified. Add an appropriate `LICENSE` file before using or redistributing this project commercially.
