# Autonomous Line-following Robot
I made this line following robot from scratch using DIY components and open-source Arduino platform. This robot transports stuff between two users (defined by point A and point B) back and forth. Robot carries the stuff in a basket and moves from point A to point B along a line defined by the black sticky tape on the floor, while avoiding collision with any passing object (e.g. a person) in its way. After it reaches the end (point A or B), robot stops and waits for the user to pick the basket up. Once user puts the basket back on robot, it turns back and moves towards the other end.

The whole project took around 5-6 months (few mins/hours here and there at nights/weekends), where I researched various aspects of robot design - mechanical engineering, electronics and computer programming. I chose Arduino microcontroller for the brain of the robot, since it's an open-source platform with tons of resources available online, mainly on YouTube. The most challenging part for me was the physical design of the robot itself, with the constrains on weight distribution of different parts, power management and robot stability.

Robot utilizes three kinds of sensors:

1. An array of 3 reflectance sensors on the underside of bottom robotic platform to detect and follow the black sticy tape.
2. An ultrasonic sensor mounted on a servo motor at the front to detect and avoid collision with any passing object, e.g. a moving person.
3. Light-dependent resistor (LDR) embedded in the top platform to detect when the user lifts the basket off and puts it back, signaling that robot needs to turn back and move towards the other end.

Following are a series of videos describing the evolution of this robot, while I implemented and optimized different features:

#### Version #1:
First try, got the robot base moving and following the line.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=7gEEXGK_PbU" target="_blank">
 <img src="https://res.cloudinary.com/marcomontalbano/image/upload/v1596294950/video_to_markdown/images/youtube--7gEEXGK_PbU-c05b58ac6eb4c4700831b2b3070cd403.jpg" alt="Line following Robot, version 01" width="240" height="180" border="10" />
</a>

#### Version #2: 
Moved wheels close to the center, which led to better weight distribution and improved robot's agility.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=8QIpKqybj4Y" target="_blank">
 <img src="https://res.cloudinary.com/marcomontalbano/image/upload/v1596335773/video_to_markdown/images/youtube--8QIpKqybj4Y-c05b58ac6eb4c4700831b2b3070cd403.jpg" alt="Line following Robot, version 02" width="240" height="180" border="10" />
</a>

#### Version #3:
Implemented a series of changes:
1. Better power management by having separate battery packs for the Arduino board and the motors.
2. Refined sensors and the code for the robot to follow a thinner line.
3. Added code for the robot to stop at the "T" intersection.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=9Ct8vHiWc-Q" target="_blank">
 <img src="https://res.cloudinary.com/marcomontalbano/image/upload/v1596336902/video_to_markdown/images/youtube--9Ct8vHiWc-Q-c05b58ac6eb4c4700831b2b3070cd403.jpg" alt="Line following Robot, version 03" width="240" height="180" border="10" />
</a>

#### Version #4 (Final design):
1. Added four legs and the top platform; embedded LDR sensor into the top platform, which senses basket movement on and off of the robot.
2. Worked on the code so that all three sensors (LDR  sensor at the top, ultrasonic object avoidance sensor at the front and reflectance sensors at the bottom) are working together.

Robot is working as expected. If a person comes in the way, robot stops and waits until the path is cleared. Robot stops at the end of the line (T intersection), waits for the user to pick up the basket. When user puts the basket back on the platform, robot turns back and starts moving towards the other end.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=npnqdeAV6AY" target="_blank">
 <img src="https://res.cloudinary.com/marcomontalbano/image/upload/v1596337079/video_to_markdown/images/youtube--npnqdeAV6AY-c05b58ac6eb4c4700831b2b3070cd403.jpg" alt="Line following Robot, version 04" width="240" height="180" border="10" />
</a>

### Code
[Here is the code](https://github.com/ved-sharma/line-following-robot/blob/master/Line_tracking.ino) which runs the final version of the robot.
