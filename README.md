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


