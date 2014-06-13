1.  Download and install [the HT1632 library](https://github.com/workshopweekend/HT1632/releases/download/v0.2/HT1632.zip) for the LED matrix board.
2.  Download and install [the capacitive sensor library](https://github.com/workshopweekend/CapacitiveSensor/releases/download/v0.1/CapacitiveSensor.zip).

3.  Copy this code into a new Arduino sketch:
    <%= capacitive_keyboard.ino =%>
4.  Upload the project!

5.  Play with the threshold value (`20` by default) in the `isTriggered` function to find an appropriate value for your environment. Open up the Serial Monitor to see what values the Arduino is reporting.

6.  Download and install [Processing](https://processing.org/download/?processing) if you don't have it.

7.  Make a new Processing sketch with the following code:
    <%= circular_graph.pde =%>
8.  Modify the `serialInterface` variable to point to the serial port your Arduino is connected on; you can find the port name in the lower right-hand corner of your Arduino IDE window.

9.  Run the Processing sketch!
