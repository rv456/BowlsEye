![Alternative text][logo]
[logo]: Resources/Misc/bowlseyelogo.png

# Bowls Eye
-----------

Repository for team 18's Real Time Embedded Programming Raspberry Pi project.



# Problem
----------

Assistive technology is used throughout many sports to aid referees to determine the correct decision, or allow competitors to appeal against said decisions.  However, in the sport of lawn bowls, there is still a large factor of human error that can occur when measuring the distance between the jack and the bowls when the game is close.  As this is currently done with standard measurement techniques, any misreading of this distance by the referee will determine the wrong outcome of the game.  Therefore, this project aims to remove the possibility of human error in these measurements by designing a real time embedded system that can perform these measurments more accurately than a human.

# Solution
-----------

In order to accurately detect the distance between the jack and surrounding bowls we propose the construction of rotation distance sensor. This will consist of a pair of ultrasonic transducers mounted to a stepper motor, which will allow 3600 rotational distance sensing via pule-echo detection. This will then output the detected distance to the nearest object per step via Bluetooth to a circular real-time display running on a laptop. This GUI will also be used to start the scanning procedure and specify the scanning parameters

The responsiveness of our distance sensor will be dictated by the required distance resolution, ie. detection of a smaller axial distance step will slow responsiveness as this will require a higher rate of data from the ultrasonic sensors to the be processed. Similarly, using a smaller angular resolution step will increase the time taken to perform a full rotation. Finally, the time for a single scan to be performed in the absence of a detectable object, ie. the wait time before moving to the next scan, will greatly impact the responsiveness of the application. All of these parameters will be user controllable via the GUI and so may be optimised for their desired time/accuracy result.

The ADC sampling rate will be between 500k-1MS/s using SPI with two channels. For a single A-scan with a maximum range of 1m there will be ~6s of data to be stored, which will be between 3 million to 6 million samples, corresponding to a detection resolution of ~50um. The Rpi will perform threshold detection to estimate the distance to an object per single scan and output this distance along with the angular position via Bluetooth for real-time display. This requires the use of three threads; one for ADC polling, one for data processing and one for data output. The GUI will be constructed using PyQT and will require threads for starting/stopping the scan process and polling/displaying the received data.
