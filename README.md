# Maker_Portfolio_Arduino_Code
Hello world! Welcome to my maker portfolio repository. Here I have all the code I used in my sound-tracking robot, as well as the code for models leading up to this.

Each piece of code illustrates the steps that my project progressed through.

1. My project began with the sound_plotter code, where I first analyzed how my mic detected sound. This helped me formulate and troubleshoot my future code, as this basic function gave me unadulterated input to use.

2. Next, I made the sound_threshold_detector program, which had event detection software to indicate loud noises in the serial monitor. This code helped me design my other programs that had event detection as a basis.

3. The next piece of code, the buzzer_and_light_indicator program, uses a couple of LEDs and a buzzer to indicate sound levels. Based on sound intensity, certain LEDs will sound, and the loudest sounds trigger the buzzer. This is the model I went on to implement in my chassis for my final designs.

4. My next code, the motor_test, was used just to initialize and check my wiring on my chassis. This enabled me to successfully wire and use my robot for the latter code.

5. Next, I made my sound_stimulated_car code, which took my indicator programs and connected them to the chassis of my robot. This allowed the robot to drive when it detected louder sounds and increase its speed depending on the sound's intensity. Using this code, I was able to begin code for my final version: a robot that could track the direction of sound and move to it.

6. My last programs are my moving_towards_sound_(v1, v2, & v3). In these, I code my robot to use 2 electret microphones and move towards the sound. The code increased speed with sound intensity, and still incorporated the lights to show sound intensity. Each version accounts for an iteration of my code, to fix some issue:

   a. moving_towards_sound_v1 is my first version, which takes the difference between the volumes on either mic and moves towards the louder sound on the specific side. This was a good start, but it was jerky and inaccurate due to mic fluctuations.

   b. moving_towards_sound_v2 is my second version and attempts to account for inconsistencies in movement with the robot. It tries to use a smoothing function and a multiplier on the difference to change the amount of turn. This code actually didn't work as well and needed a lot of tuning, prompting me to move to the third version.

   c. moving_towards_sound_v3 is the last version, and reverts to the original code, but uses a noiseFloor variable to account for background noise. It also has modified var and float names for ease of use. This version still requires some modifications, but it represents another step forward.

All these programs should be available to view in their entirety, and give an inside look into my method and programming. Feel free to look around!
