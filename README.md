# NJSlowFeeder

This is a slowfeeder for feeding coffee beans into a grinder. It is designed to be 3D printed and assembled with basic mechanical and electrical tools (hex driver, soldering iron, wire strippers).

## Updates:
V1.2 is out. See Issues for additional adaptors or to request additional functionality.\
Development is actively occuring, the main discussion channel is on the Gaggiuino Discord. 

## V1.2
V1.2 introduces a microcontroller (with BLE/Wifi), PWM motor controller, and load cell compatiblity while maintaining the great battery life of V1.1.\
V1.2 CAD is stable. See Issues to request new adaptors or other features.\
V1.2 Code is very much a proof of concept, and under development.\
BOM at [this link](https://docs.google.com/spreadsheets/d/11zUR7dkBkgdKcGbynbE2zPVb8PsdSGaQEwi6_OAgMBY/edit?usp=sharing).
### Demo Video
[![SlowFeeder V1.2 Demo](https://img.youtube.com/vi/54PZubX1fOw/0.jpg)](https://www.youtube.com/watch?v=54PZubX1fOw)

### Working Functions:
1. Variable speed control (hold up/down once wheel is turning)
2. On/Off control of wheel
3. Loadcell reading and setup taring (basic)
4. Deepsleep (works, but currently higher draw than expected with the HX711 for some reason)

### Planned Functions:
- [ ] WebUI for parameter control
- [ ] PoopCode :tm: - Precise single dosing of beans (for filling vials or grinding)

## V1.1 
V1.1 uses a fully analog approach to slowfeeding and does not include a microcontroller.\
V1.1 is unlikely to receive further updates. An analog V1.2 can be made with some tweaks to the BOM.\
Speed is set using a regulator of user choice (good options listed in BOM) and is not easily adjustable on the fly. \
See the V1.1 folder in CAD_Models for more details.\
BOM at [this link](https://docs.google.com/spreadsheets/d/11zUR7dkBkgdKcGbynbE2zPVb8PsdSGaQEwi6_OAgMBY/edit?usp=sharing).
