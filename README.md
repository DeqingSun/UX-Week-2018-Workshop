# Experience Prototyping with IoT Devices

### Peiqi Su, Deqing Sun 

### UX Week, 2018




## Short link of this page

Github: [tiny.cc/uxweek](http://tiny.cc/uxweek)

Github IO: [tiny.cc/uxweekpage](http://tiny.cc/uxweekpage)

## Demo code

You can open this page on your mobile device for easier navigation

[Assembly instructions](https://deqingsun.github.io/UX-Week-2018-Workshop/instruction/)

|Demo|Recommended firmware| Instruction |
|---|---|---|
|[Function test (P5JS)](https://deqingsun.github.io/UX-Week-2018-Workshop/demo/PressTest/)|Any| |
|[Function test (Snap)](https://snap.berkeley.edu/snapsource/snap.html#present:Username=deqing&ProjectName=testMicrobit)|Any| |
|[Dash Button (Snap)](https://snap.berkeley.edu/snapsource/snap.html#present:Username=deqing&ProjectName=dashButton)|LED_2IO.hex|[Instruction](https://deqingsun.github.io/UX-Week-2018-Workshop/instruction/index.html#dash-button)|
|[Timer (Snap)](https://snap.berkeley.edu/snapsource/snap.html#present:Username=deqing&ProjectName=timer)|default_3IO.hex|[Instruction](https://deqingsun.github.io/UX-Week-2018-Workshop/instruction/index.html#timer--hue)|
|[Hue (Snap)](https://snap.berkeley.edu/snapsource/snap.html#present:Username=deqing&ProjectName=hue)|default_3IO.hex|[Instruction](https://deqingsun.github.io/UX-Week-2018-Workshop/instruction/index.html#timer--hue)|
|[Music (Snap)](https://snap.berkeley.edu/snapsource/snap.html#present:Username=deqing&ProjectName=music) Not work on iOS|accel_3IO.hex|[Instruction](https://deqingsun.github.io/UX-Week-2018-Workshop/instruction/index.html#music-not-work-on-ios)|
|[Cup (Snap)](https://snap.berkeley.edu/snapsource/snap.html#present:Username=deqing&ProjectName=cup)|accel_3IO.hex|[Instruction](https://deqingsun.github.io/UX-Week-2018-Workshop/instruction/index.html#cup)|
|[Steering wheel (Snap)](https://snap.berkeley.edu/snapsource/snap.html#present:Username=deqing&ProjectName=steeringWheel)|accel_3IO.hex|[Instruction](https://deqingsun.github.io/UX-Week-2018-Workshop/instruction/index.html#steering-wheel)|

## Pairing instruction

[Mac](https://deqingsun.github.io/UX-Week-2018-Workshop/pair/Pair%20Microbit%20with%20Mac.pdf)

[iOS](https://deqingsun.github.io/UX-Week-2018-Workshop/pair/Pair%20Microbit%20with%20iOS.pdf)

[Android](https://deqingsun.github.io/UX-Week-2018-Workshop/pair/Pair%20Microbit%20with%20Android.pdf)

## Key Mapping

| default_3IO.hex | LED_2IO.hex | accel_3IO.hex |
|---|---|---|
| ![default_3IO.hex](https://deqingsun.github.io/UX-Week-2018-Workshop/connections/conn_3IO.png){:height="350px" width="258px"} | ![LED_2IO.hex](https://deqingsun.github.io/UX-Week-2018-Workshop/connections/conn_2IO.png){:height="350px" width="266px"} | ![accel_3IO.hex](https://deqingsun.github.io/UX-Week-2018-Workshop/connections/conn_3IO_ACCEL.png){:height="350px" width="391px"} |

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

