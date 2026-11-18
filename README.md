# Line-Following-Robot-using-Arduino
An Arduino-based line-following robot that uses two IR sensors to detect a track and control its movement automatically. The robot uses an Arduino Nano,L298 motor driver and DC motors,with the code written in C/C++ using the Arduino IDE.The project demonstrates basic sensor input,motor control,embedded programming and hardware software integration.
# What it does
| Left sensor | Right sensor | Action |
|---|---|---|
| White | White | Drive forward |
| White | Black | Turn right |
| Black | White | Turn left |
| Black | Black | Stop |
## How it works

-**IR sensors** shine infrared light at the floor. White surfaces reflect more light and black surfaces absorb it, so each sensor outputs a simple 0 or 1.
- **Arduino Nano** reads both sensors thousands of times per second and decides which way to move.
- **L298 motor driver** powers the motors. The Arduino's pins can't supply enough current for motors directly, so it sends control signals to the driver, which switches the motor power.
- **Differential drive:** the robot steers by spinning its two wheels in different directions or at different speeds, with no steering mechanism.
- **PWM speed control:** `analogWrite()` switches the motor enable pins on and off rapidly to set the speed (currently 150 out of 255).
## Pin connections and Circuit Diagram
<img width="1600" height="819" alt="WhatsApp Image 2026-11-18 at 9 16 32 PM" src="https://github.com/user-attachments/assets/92eb1246-b340-497b-aa4a-e232378add40" />




## Problem I faced and how I solved it
**The robot turned the wrong way.** When I first tested it, the robot turned left when it should have turned right, and the other way round. The cause was the wiring: the code assumes the right motor is connected to the first set of L298 terminals (in1/in2) and the left motor to the second (in3/in4), and mine was connected the opposite way. I learned that "forward" and "right" aren't built into the motor driver. They depend on how the motors are wired, so the code and the wiring have to agree. I fixed it by moving the motor wires to the correct L298 terminals, so the hardware matched what the code expected.
## Experiment: Smooth Turning
The original code turns by reversing the inner wheel, so the robot pivots almost on the spot. This makes the movement a little jerky, so I tried to improve it by making the turns smoother.
What I tried: instead of reversing the inner wheel, I kept both motors going forward and slowed the inner wheel down , so the robot curves in an arc instead of pivoting:

```cpp
void forward(){ //forward
digitalWrite(in1, HIGH); //Right Motor forward Pin
digitalWrite(in2, LOW); //Right Motor backward Pin
digitalWrite(in3, LOW); //Left Motor backward Pin
digitalWrite(in4, HIGH); //Left Motor forward Pin
analogWrite(enA, 150); //Right Motor normal speed
analogWrite(enB, 150); //Left Motor normal speed
}

void turnRight() {
  digitalWrite(in1, HIGH);  // right motor forward
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);   // left motor forward
  digitalWrite(in4, HIGH);
  analogWrite(enA, 60);     // right (inner) motor slower
  analogWrite(enB, 150);    // left (outer) motor normal
}


void turnLeft(){ //turnLeft
 digitalWrite(in1, HIGH); //Right Motor forward Pin
 digitalWrite(in2, LOW); //Right Motor backward Pin
 digitalWrite(in3, LOW); //Left Motor backward Pin
 digitalWrite(in4, HIGH); //Left Motor forward Pin
 analogWrite(enA, 150); //Right Motor (outer) normal speed
 analogWrite(enB, 60); //Left Motor (inner) slower
}
```
 
 What happened: the smooth turns looked less jerky on gentle curves, but the robot did not work reliably at sharp corners. Because it keeps moving forward while it curves, its turning radius is wider, so it carried on past the corner and lost the line before the sensors could correct it. 
 I went back to the original pivot turns. Reliably staying on the line mattered more to me than smoother movement, even though the pivot turn makes the motion a little jerky.

What I learnt: a design that looks better can perform worse in practice, and there's a trade-off between smooth motion and sharp-corner accuracy. With only two sensors, the robot can't tell how far off the line it is, which limits how gentle the corrections can be. An aesthetically superior design can underperform in practice, making rigorous physical testing essential




## Photos and Videos of Build Process
<img width="960" height="1280" alt="WhatsApp Image 2026-11-18 at 8 45 13 PM" src="https://github.com/user-attachments/assets/0bb6e70a-c998-4b73-a93a-16c806c3e405" />

<img width="960" height="1280" alt="WhatsApp Image 2026-11-18 at 8 45 13 PM (1)" src="https://github.com/user-attachments/assets/4d2b22cf-7f95-467f-9e69-967c4e5b10ac" />



https://github.com/user-attachments/assets/476ad9bd-1dd0-43bc-9a81-0303c8b7c556




