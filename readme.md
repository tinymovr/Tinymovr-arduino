
# Tinymovr-Arduino library

![CI](https://github.com/tinymovr/tinymovr-arduino/actions/workflows/ci.yaml/badge.svg)

This library is an easy interface for controlling Tinymovr through CAN Bus, using an Arduino and a CAN Adapter.

> **Note**
>
> This is the latest stable version of Tinymovr Arduino. For the legacy 0.x.x version, check out the [legacy branch](https://github.com/tinymovr/Tinymovr-arduino/tree/legacy).

## Hardware setup

You will need a Tinymovr, an Arduino and an adapter to allow Arduino to talk to CAN. The most common one is the Microchip MCP2515 paired with a MCP2551 transceiver, both of which are available as a breakout board that talks to Arduino through SPI. However, the library is hardware-agnostic so you can use any adapter you want.

## Installing the library

[Download the zip](https://github.com/tinymovr/Tinymovr-arduino/archive/refs/heads/main.zip). Either use the "Install from ZIP file" option in Arduino, or extract the zip contents to `{arduino folder}/libraries/Tinymovr-arduino`. An example file is included with the library.

The library is hardware-agnostic so you can use any CAN 2.0-capable adapter. The library uses dependency injection to talk to hardware. There are two functions, `send_cb` and `recv_cb` that need to be implemented. These are passed to the Tinymovr object during initialization, along with the desired board CAN id:

    Tinymovr tinymovr(1, &send_cb, &recv_cb);

The example code included assumes the MCP2551, so if you have that set up with Arduino, you're good to go.

## Using the library

The library is object oriented and the main Tinymovr object is what you use to establish communication with the board. Since mose endpoints return multiple data, the functions require references to variables to store the data. For instance, to retrieve encoder estimates:

    float pos_estimate;
    float vel_estimate;
    tinymovr.get_encoder_estimates(&pos_estimate, &vel_estimate);

## License

MIT

## References

[Official Website](https://tinymovr.com)

[Documentation](https://tinymovr.readthedocs.io)
