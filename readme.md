
# Tinymovr-Arduino library

![CI](https://github.com/tinymovr/tinymovr-arduino/actions/workflows/ci.yaml/badge.svg)

The Tinymovr-Arduino library offers an easy interface for controlling Tinymovr through CAN Bus, using an embedded device such as an Arduino, and a CAN Adapter.

> **Note**
>
> This is the latest stable version of Tinymovr Arduino. For the legacy 0.x.x version, check out the [legacy branch](https://github.com/tinymovr/Tinymovr-arduino/tree/legacy).

## Installing the library

[Download the zip](https://github.com/tinymovr/Tinymovr-arduino/archive/refs/heads/main.zip). Either use the "Install from ZIP file" option in Arduino, or extract the zip contents to `{arduino folder}/libraries/Tinymovr-arduino`. An example file is included with the library.

The library is hardware-agnostic so you can use any CAN 2.0-capable adapter. The library uses dependency injection to talk to hardware. There are three functions, `send_cb`,  `recv_cb` and `delay_us_cb` that need to be implemented. These are passed to the Tinymovr object during initialization, along with the desired board CAN id:

    Tinymovr tinymovr(1, &send_cb, &recv_cb, &delay_us_cb);


## Using the library

The library is object oriented and the main Tinymovr object is what you use to establish communication with the board. Since mose endpoints return multiple data, the functions require references to variables to store the data. For instance, to retrieve encoder estimates:

    float pos_estimate;
    float vel_estimate;
    tinymovr.get_encoder_estimates(&pos_estimate, &vel_estimate);

## Hardware Support

Even though the library itself is hardware-agnostic (by means of dependency injection), the examples we provide depend on the [CAN Adafruit Fork](https://github.com/adafruit/arduino-CAN) library for low-level hardware access and configuration. Why this library? Because it is the only one offering robust extended frame hardware filtering configuration. There are a ton of CAN libraries for Arduino and embedded in general, but most have only the basic functionality working and fully tested, not the advanced features that Tinymovr requires. 
 
However, there are some edge cases that the CAN Adafruit Fork library is unable to support. The most common one is MCP2515 breakout boards (the blue ones) with 8MHz crystal, of which there are plenty to be found from Chinese sources. The CAN Adafruit Fork library has the crystal frequency harcoded to 16MHz, which breaks the CAN timing configuration. Unfortunately, Adafruit has archived the library repository so it is impossible to raise an issue on this matter. 

As we cannot afford to maintain another low-level CAN library fork, this situation will most probably remain as is for the foreseeable future. Our advice would be to switch to something like a MKR CAN BUS Shield, which is fully supported. Alternatively, you may try to fork the CAN Adafruit Fork library, or implement your own `send_cb`,  `recv_cb` and `delay_us_cb` routines. In both cases, you can ask for community support in our [Discord server](https://discord.gg/vNvmpfthug), but these options are not officially supported.

## License

MIT

## References

[Official Website](https://tinymovr.com)

[Documentation](https://tinymovr.readthedocs.io)
