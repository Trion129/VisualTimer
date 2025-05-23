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

4. **Run the application**:
   ```
   ./VisualTimer
   ```

## Usage
- Launch the application to open the main window.
- Drag the red handle on the dial to set your desired time (in 5-minute increments).
- Click the Play icon to begin the countdown. The button will change to a Pause icon while the timer is running.
- Click the Pause icon to temporarily pause the timer (the same button toggles between Start/Pause).
- Click the Reset icon to reset the timer to your last set time.
- The timer shows remaining time with second precision both visually and in digital format.

## Contributing
Feel free to submit issues or pull requests for any enhancements or bug fixes. 

## License
This project is licensed under the MIT License.