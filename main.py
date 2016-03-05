import joy

joystick = joy.JoyMouse("/dev/ttyUSB1", 9600, config_file="joy_config")

print("START!")

while 1:
    joystick.step()

