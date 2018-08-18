# UX-Week-2018-Workshop
Experience Prototyping with IoT Devices

## Short link of this page
###[tiny.cc/uxweek](http://tiny.cc/uxweek)

## Key Mapping

| default_3IO.hex | LED_2IO.hex | accel_3IO.hex |
|---|---|---|
| ![default_3IO.hex](https://github.com/DeqingSun/UX-Week-2018-Workshop/blob/master/connections/conn_3IO.png?raw=true) | ![LED_2IO.hex](https://github.com/DeqingSun/UX-Week-2018-Workshop/blob/master/connections/conn_2IO.png?raw=true) | ![accel_3IO.hex](https://github.com/DeqingSun/UX-Week-2018-Workshop/blob/master/connections/conn_3IO_ACCEL.png?raw=true) |

## Firmware Archive

To upload a new firmware, connect MicroBit to computer with Micro USB cable. You should see a new drive named "MICROBIT" appears. Drag one hex file into the drive to update firmware.

### Mac/iOS

[Download package of 3 hex files.](https://github.com/DeqingSun/UX-Week-2018-Workshop/blob/master/firmware/mac_ios.zip?raw=true)

| Feature  | Filename |
|---|---|
| Pin 0,1,2 all act as input  | default_3IO.hex  |
| Pin 0,1 act as input, Pin 2 can light LED when Pin 0 or 1 is activated  | LED_2IO.hex  |
| Pin 0,1,2 all act as input, also keystrokes will be generated when MicorBit is rotated  | accel_3IO.hex  |

### Android

[Download package of 3 hex files.](https://github.com/DeqingSun/UX-Week-2018-Workshop/blob/master/firmware/android.zip?raw=true)

| Feature  | Filename |
|---|---|
| Pin 0,1,2 all act as input  | default_3IO_Android.hex  |
| Pin 0,1 act as input, Pin 2 can light LED when Pin 0 or 1 is activated  | LED_2IO_Android.hex  |
| Pin 0,1,2 all act as input, also keystrokes will be generated when MicorBit is rotated  | accel_3IO_Android.hex  |

## Develop your own firmware.

[Source code](https://github.com/DeqingSun/UX-Week-2018-Workshop/tree/developPackage/ArduinoTestCode/HID_keyboard)

compiled with [this](https://github.com/DeqingSun/arduino-BLEPeripheral) version of library

