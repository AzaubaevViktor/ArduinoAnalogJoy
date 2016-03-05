import joy

joystick = joy.Joy("/dev/ttyUSB1", 9600, config_file="joy_config")

print("START!")

while 1:
    print(joystick.get_data())
