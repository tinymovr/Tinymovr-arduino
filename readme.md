
# Tinymovr-Arduino library

![CI](https://github.com/tinymovr/tinymovr-arduino/actions/workflows/ci.yaml/badge.svg)

The Tinymovr-Arduino library offers an easy interface for controlling Tinymovr through CAN Bus, using an embedded device such as an Arduino, and a CAN Adapter.

> **Note**
>
> This is the latest stable version of Tinymovr Arduino. For the legacy 0.x.x version, check out the [legacy branch](https://github.com/tinymovr/Tinymovr-arduino/tree/legacy).

## Installing the library

[Download the release .zip](https://github.com/tinymovr/Tinymovr-arduino/releases) that corresponds to your Tinymovr firmware version. Either use the "Install from ZIP file" option in Arduino, or extract the zip contents to `{arduino folder}/libraries/Tinymovr-arduino`. An example file is included with the library.

The library is hardware-agnostic so you can use any CAN 2.0-capable adapter. The library uses dependency injection to talk to hardware. There are three functions, `send_cb`,  `recv_cb` and `delay_us_cb` that need to be implemented. These are passed to the Tinymovr object during initialization, along with the desired board CAN id:

    Tinymovr tinymovr(1, &send_cb, &recv_cb, &delay_us_cb);


## Using the library

The library is object oriented and the main Tinymovr object is what you use to establish communication with the board. Endpoints that are read only implement  `get_{endpoint_name}` style getters. Endpoints that are writeable implement both `get_{endpoint_name}` and `set_{endpoint_name}`. 

    float pos_estimate = tinymovr.sensors.user_frame.get_position_estimate();
    float vel_estimate = tinymovr.sensors.user_frame.get_velocity_estimate();
    tinymovr.controller.position.set_setpoint(10000);

Functions are called with their name and required parameters.

    tinymovr.traj_planner.move_to(10000);

## Hardware Support

Even though the library itself is hardware-agnostic (by means of dependency injection), the examples we provide depend on the [CAN Adafruit Fork](https://github.com/adafruit/arduino-CAN) library for low-level hardware access and configuration. Why this library? Because it is the only one offering robust extended frame hardware filtering configuration. There are a ton of CAN libraries for Arduino and embedded in general, but most have only the basic functionality working and fully tested, not the advanced features that Tinymovr requires. 
 
However, not all hardware is compatible with the CAN Adafruit Fork library. Namely, the MCP2515 breakout boards (the blue ones) with 8MHz crystal, of which there are plenty to be found from Chinese sources, are incompatible. The CAN Adafruit Fork library has the crystal frequency harcoded to 16MHz, which breaks the CAN timing configuration. Unfortunately, Adafruit has archived the library repository so it is impossible to raise an issue on this matter. 

As we cannot afford to maintain another low-level CAN library fork, this situation will most probably remain as is for the foreseeable future. If you use this MCP2515 breakout our advice would be to switch to something like a CAN BUS Shield with a 16 MHz crystal. Alternatively, you may try to fork the CAN Adafruit Fork library, or implement your own `send_cb`, `recv_cb` and `delay_us_cb` routines. In both cases, you can ask for community support in our [Discord server](https://discord.gg/vNvmpfthug), but these options are not officially supported.

We've tested this library with an Arduino MKR CAN Bus Shield. Other boards/shields should be compatible.

## License

MIT

## References

[Official Website](https://tinymovr.com)

[Documentation](https://tinymovr.readthedocs.io)
