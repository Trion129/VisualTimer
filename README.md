# Visual Timer Application

## Overview
The Visual Timer application is a simple yet effective countdown timer tool built using Qt. It provides a visual representation of time remaining similar to TimeTimer clocks, with a draggable dial to set the time. The interface includes intuitive controls for starting/pausing, stopping, and resetting the timer, making it suitable for various timing needs.

## Setup Instructions
1. **Clone the repository**:
   ```
   git clone https://github.com/Trion129/VisualTimer.git
   cd VisualTimer
   ```

2. **Install dependencies**:
   Ensure you have Qt and CMake installed on your system.

3. **Build the project**:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Install the application (optional)**:
   ```
   sudo make install
   ```
   This will install:
   - The executable to `/usr/local/bin/VisualTimer`
   - A desktop entry in `/usr/local/share/applications/`
   - The application icon in `/usr/local/share/icons/`

   After installation, you can launch the application from your system's application menu
   or by typing `VisualTimer` in the terminal.

   To install to a user directory instead (no sudo required):
   ```
   cmake -DCMAKE_INSTALL_PREFIX=$HOME/.local ..
   make
   make install
   ```

5. **Run the application**:
   ```
   ./VisualTimer
   ```
   Or if installed:
   ```
   VisualTimer
   ```

## Usage
- Launch the application to open the main window.
- Drag the red handle on the dial to set your desired time (in 5-minute increments).
- Click the Play icon to begin the countdown. The button will change to a Pause icon while the timer is running.
- Click the Pause icon to temporarily pause the timer (the same button toggles between Start/Pause).
- Click the Reset icon to reset the timer to your last set time.
- The timer shows remaining time with second precision both visually and in digital format.

## Releases

### Installing from Releases
1. Go to the [Releases](https://github.com/Trion129/VisualTimer/releases) page on GitHub
2. Download the appropriate package for your operating system:
   - For Windows: Download `VisualTimer-Windows.zip`, extract it, and run `VisualTimer.exe`
   - For Linux: Download `VisualTimer-Linux.tar.gz`, extract it, and run `./run_visualtimer.sh`

### Creating a New Release
To create a new release:

1. Update the version number in relevant files (if applicable)
2. Create and push a new tag:
   ```
   git tag -a v1.0.0 -m "Release v1.0.0"
   git push origin v1.0.0
   ```
3. GitHub Actions will automatically:
   - Build the application for Windows and Linux
   - Create a new release with these builds attached
   - Generate release notes based on commits since the last release

## Contributing
Feel free to submit issues or pull requests for any enhancements or bug fixes. 

## License
This project is licensed under the MIT License.