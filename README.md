# Overview
This is an ESPHOME component that controls a Laz-y-boy recliner with 2 degrees of freedom and adds a couple of useful 'gestures' to the physical control buttons, the hardware is inserted between the button pad and the motor control connector, these are PC power supply style molex connectors so its fairly easy to build a harness to do this w/o any cutting of the factory wires.

These recliners use 30V power supplies, the circuit is an ESP32, a buck convertor board to make 5V from 30v, and a 4 relay board with opto-isolators.

# Sample config

To get from git:

```
external_components:
  - source:
      type: git
      url: https://github.com/evarsanyi/chair_component.git
      ref: main
    components: [ chair ]
```

The virtual buttons on the chair platform allow remote control.

```
button:
  - platform: chair
    name: "Back Up"
    chair_id: xyzzy
    but_id: 0
  - platform: chair
    name: "Back Down"
    chair_id: xyzzy
    but_id: 1
  - platform: chair
    name: "Leg Up"
    chair_id: xyzzy
    but_id: 2
  - platform: chair
    name: "Leg Down"
    chair_id: xyzzy
    but_id: 3


chair:
  name: "Chair1"
  id: xyzzy
  pin_back_up: GPIO14
  pin_back_dn: GPIO27
  pin_leg_up: GPIO26
  pin_leg_dn: GPIO25
  pin_back_up_but: GPIO18
  pin_back_dn_but: GPIO19
  pin_leg_up_but: GPIO21
  pin_leg_dn_but: GPIO22
```
