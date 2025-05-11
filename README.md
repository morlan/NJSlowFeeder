# NJSlowFeeder

This is a slowfeeder for feeding coffee beans into a grinder. It is designed to be 3D printed and assembled with basic mechanical and electrical tools (hex driver, soldering iron, wire strippers).

## Updates:
V1.2 is out. See Issues for additional adaptors or to request additional functionality.

## V1.2
V1.2 introduces a microcontroller (with BLE/Wifi), PWM motor controller, and load cell compatiblity while maintaining the great battery life of V1.1.
[![SlowFeeder V1.2 Demo](https://img.youtube.com/vi/54PZubX1fOw/0.jpg)](https://www.youtube.com/watch?v=54PZubX1fOw)
V1.2 CAD is stable. See Issues to request new adaptors or other features.

V1.2 Code is very much a proof of concept, and under development.

### Working Functions:
1. Variable speed control (hold up/down once wheel is turning)
2. On/Off control of wheel
3. Loadcell reading and setup taring (basic)
4. Deepsleep (works, but currently buggy with the HX711 for some reason)

### Planned Functions:
- [ ] WebUI for parameter control
- [ ] PoopCode :tm: - Precise single dosing of beans (for filling vials or grinding)


BOM at https://docs.google.com/spreadsheets/d/11zUR7dkBkgdKcGbynbE2zPVb8PsdSGaQEwi6_OAgMBY/edit?usp=sharing
