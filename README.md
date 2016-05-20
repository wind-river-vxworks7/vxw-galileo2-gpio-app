# Galileo GPIO

A sample application to blink the LED on the Intel Galileo Gen2 board.

The LED is located between the USB host and device ports, on the same side
of the board as the Ethernet connector.  Internally, it is connected to
GPIO Pin 7 which is also broken out on IO13 of the Arduino header.

The program will set up the required GPIO pins and then toggle the LED
10 times with a 1 second delay in between.

## Sample Output

```
Process started (ID: 0x106c040)
Process exited with exit code 0


Process exited with code: 0
```
