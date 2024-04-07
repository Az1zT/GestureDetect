# GestureDetect
 
Raspberry pi pico implementation of ANN based gesture detector. It is used to detect the shape of motion (circle, triangle, etc)

Hardware used: Raspberry pi Pico, ADXL-335 accelerometer.

# How to use?

1. Clone the repo.
2. Build edge-impulse-sdk/main.cpp.
3. An app.uf2 file will be created in build directory.
4. Connect the setup as shown in the figure with pc, while pressing the "Bootshell" button of R-Pi
5. Copy the app.uf2 file in the newly created directory
6. Pico will now restart and execute the code immediately. The output can be seen in IDEs such as Thonny.


This is the compiled version of the actual model. To see the training and data collection process, visit https://studio.edgeimpulse.com/studio/375387

# Setup

![setup](https://github.com/Az1zT/GestureDetect/blob/4b2121e1f5196079741d709058d40dba383f95d4/media/setup.jpg?raw=true)
![setup](https://github.com/Az1zT/GestureDetect/blob/5e859c73c80aa28409a647d1b0575d75d00a908a/media/setup1.webp?raw=true)
