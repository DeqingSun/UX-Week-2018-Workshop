# UX-Week-2018-Workshop
Experience Prototyping with IoT Devices

## Short link of this page

Github: [tiny.cc/uxweek](http://tiny.cc/uxweek)

Github IO: [tiny.cc/uxweekpage](http://tiny.cc/uxweekpage)

## Demo code

You can open this page on your mobile device for easier navigation



## Key Mapping

| default_3IO.hex | LED_2IO.hex | accel_3IO.hex |
|---|---|---|
| ![default_3IO.hex](https://deqingsun.github.io/UX-Week-2018-Workshop/connections/conn_3IO.png){:height="350px"} | ![LED_2IO.hex](https://deqingsun.github.io/UX-Week-2018-Workshop/connections/conn_2IO.png){:height="350px"} | ![accel_3IO.hex](https://deqingsun.github.io/UX-Week-2018-Workshop/connections/conn_3IO_ACCEL.png){:height="350px"} |

## Firmware Archive

To upload a new firmware, connect MicroBit to computer with Micro USB cable. You should see a new drive named "MICROBIT" appears. Drag one hex file into the drive to update firmware.

### Mac/iOS

[Download package of 3 hex files.](https://deqingsun.github.io/UX-Week-2018-Workshop/firmware/mac_ios.zip)

| Feature  | Filename |
|---|---|
| Pin 0,1,2 all act as input  | [default_3IO.hex](https://deqingsun.github.io/UX-Week-2018-Workshop/firmware/mac_ios/default_3IO.hex)  |
| Pin 0,1 act as input, Pin 2 can light LED when Pin 0 or 1 is activated  | [LED_2IO.hex](https://deqingsun.github.io/UX-Week-2018-Workshop/firmware/mac_ios/LED_2IO.hex)  |
| Pin 0,1,2 all act as input, also keystrokes will be generated when MicorBit is rotated  | [accel_3IO.hex](https://deqingsun.github.io/UX-Week-2018-Workshop/firmware/mac_ios/accel_3IO.hex)  |

### Android

[Download package of 3 hex files.](https://deqingsun.github.io/UX-Week-2018-Workshop/firmware/android.zip)

| Feature  | Filename |
|---|---|
| Pin 0,1,2 all act as input  | [default_3IO_Android.hex](https://deqingsun.github.io/UX-Week-2018-Workshop/firmware/android/default_3IO_Android.hex)  |
| Pin 0,1 act as input, Pin 2 can light LED when Pin 0 or 1 is activated  | [LED_2IO_Android.hex](https://deqingsun.github.io/UX-Week-2018-Workshop/firmware/android/LED_2IO_Android.hex)   |
| Pin 0,1,2 all act as input, also keystrokes will be generated when MicorBit is rotated  | [accel_3IO_Android.hex](https://deqingsun.github.io/UX-Week-2018-Workshop/firmware/android/accel_3IO_Android.hex)  |

## Develop your own firmware.

[Source code](https://github.com/DeqingSun/UX-Week-2018-Workshop/tree/developPackage/ArduinoTestCode/HID_keyboard)

compiled with [this](https://github.com/DeqingSun/arduino-BLEPeripheral) version of library

