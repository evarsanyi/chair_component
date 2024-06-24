# Overview
This is an ESPHOME component that controls a Laz-y-boy recliner with 2 degrees of freedom and adds a couple of useful 'gestures' to the physical control buttons, the hardware is inserted between the button pad and the motor control connector, these are PC power supply style molex connectors so its fairly easy to build a harness to do this w/o any cutting of the factory wires.

These recliners use 30V power supplies, the circuit is an ESP32, a buck convertor board to make 5V from 30v, and a 4 relay board with opto-isolators.

# Sample config
