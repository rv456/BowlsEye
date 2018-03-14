import numpy
import random

#simple script for generatinge angle/distance measurements and storing as csv
with open("Output.txt", "w") as text_file:
        print("Test data for BowlsEye GUI data display",file=text_file)
        print("Angle,Distance",file=text_file)
        for i in range(0,361):
            angle=i
            distance=random.random()
            print(i)
            print("{},{}".format(angle,distance), file=text_file)
