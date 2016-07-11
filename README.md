# Caramel (Arduino)
### Arduino side of Caramel dog door project

This acts as the server side of the Caramel system. It recieves commands via an HC-05.
- VCC → Pin 8
- GND → GND
- TXD → Pin 2
- RXD → Pin 3
- KEY → Pin 4

It also uses a piezo buzzer to alert animals or people. 
- Pin 5

And the motor/actuator is controlled by two relays in an H-bridge shape.
- Pin 6 → Forward
- Pin 7 → Reverse
