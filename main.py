import joy

joystick = joy.Joy("/dev/ttyUSB0", config_file="joy_config")

while 1:
    print(joystick.get_data())

