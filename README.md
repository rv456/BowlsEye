![Alternative text](Resources/Misc/bowlseyelogo.png)

# Bowls Eye
-----------

Repository for team 18's Real Time Embedded Programming Raspberry Pi project.

Watch our promotional video at the link below!

[![Promotional Video](http://img.youtube.com/vi/sJp9lf-OOYo&/0.jpg)](http://www.youtube.com/watch?v=sJp9lf-OOYo&)

## Repository Structure

[Code](https://github.com/rv456/BowlsEye/tree/master/Code) contains all of the code written for the Raspberry Pi and the external GUI.  Code documentation can be found [here](https://rv456.github.io/BowlsEye/).

[KiCad](https://github.com/rv456/BowlsEye/tree/master/KiCad) contains the various hardware design files used throught the project, including a full [BOM](https://github.com/rv456/BowlsEye/blob/master/KiCad/Shield/Fabrication/BOM/BOMfull.csv) and fabrication files. (note that part numbers for everything used in the project can also be found directly in the [schematics](https://github.com/rv456/BowlsEye/blob/master/KiCad/Shield) thanks to [kifields](http://kifield.readthedocs.io/en/latest/).

[Planner](https://github.com/rv456/BowlsEye/tree/master/Planner) contains documents related to project planning.  These will be removed once the project is completed.

[Resources](https://github.com/rv456/BowlsEye/tree/master/Resources) contains various datasheets, notes and other supporting files.

-----------

## Team Structure

[Harvey Leicester](https://github.com/rv456): Raspberry Pi programming and hardware design.

[Calum West](https://github.com/CalumWest): GUI programming and ultrasound guru.


# Problem
----------

Assistive technology is used throughout many sports to aid referees to determine the correct decision, or allow competitors to appeal against said decisions.  However, in the sport of lawn bowls, there is still a large factor of human error that can occur when measuring the distance between the jack and the bowls when the game is close.  As this is currently done with standard measurement techniques, any misreading of this distance by the referee will determine the wrong outcome of the game.  Therefore, this project aims to remove the possibility of human error in these measurements by designing a real time embedded system that can perform these measurments more accurately than a human.

# Solution
-----------

We have designed a system which uses ultrasonic transducers mounted on a stepper motor in order to map the distance from the jack to the surrounding area. This data is read via SPI by a Raspberry Pi and then transmitted via Bluetooth for a display on a GUI. More information can be found on our [wiki](https://github.com/rv456/BowlsEye/wiki).

A system overview is shown below, and you can follow our progress via this git, or our [facebook](https://www.facebook.com/Bowls-Eye-102409543919161/) or [twitter](https://twitter.com/bowlseyepi).


![Alternative text](Resources/Misc/blockDiagram.png)
