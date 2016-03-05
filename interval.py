def getRbyADC(adc):
    r1 = 100000
    if adc == 0:
        return 0
    if adc == 1023:
        return r1/0.0000000001
    return r1 / (1023 / adc - 1)


class Interval:
    def __init__(self, left=0, right=0):
        self.left = left
        self.right = right

    def extend(self, val):
        if val < self.left:
            self.left = val

        if val > self.right:
            self.right = val

    def adc2r(self):
        self.left = getRbyADC(self.left)
        self.right = getRbyADC(self.right)

    def __contains__(self, item):
        return self.left < item < self.right

    def __str__(self):
        return str(self.left) + " " + str(self.right)