# WroTeamX


This repository contains technical materials for a self-navigating vehicle prototype intended for the WRO Future Engineers event in the 2023 season. Detailed insights into each subcomponent of the robotic system can be explored in the README.md files located within respective folders.

### Contents:

- **Build:** Detailed documentation focusing on our chassis design and the rationale behind the chosen materials.
- 
- **Electrical:** Schematic diagrams illustrating the interconnections among various electromechanical components, including datasheets and explanations for component selection.
- 
- **Models:** Files used by 3D printers to fabricate the vehicle's components.
- 
- **t-Photos:** Folder containing team photos.
- 
- **v-Photos:** Images of the robot.
- 
- **Src:** Software code responsible for controlling all the components programmed for the competition.
- 
- **Schemes:** Documentation and diagrams elucidating our approach to solving the competition's challenges.
- 
- **Video:** Includes the 'video.md' file containing the link to a video demonstrating the vehicle's operational abilities.

### Requirements:

This project meets the following requirements specified by the WRO Future Engineers event:
**Mobility Management** is found in electrical and models

**Power and Sense Management** is found in schemes.

***Components List** The list of all components is in schemes as well.

**Obstacle Management** and coding files are found in src.

**Pictures**  Team and Vehicle is found in photos.

**Performance Videos** are in video folder.

**Engineering Factor** is found in build and README


### Introduction:
AcTeamX by mechabotix is a team of high school students from Aitchison College Lahore Pakistan. We have been working on our robot since june .
We have won the National round and then qualified for international round. We are working hard to get the position in the International round as well.
Instead of buying OFF THE SHELF materials for the design of our car , we have designed our car by ourselves . We made 3d models then got the print of the car .
In the National round , we made a design and used that oe but that was really big car and we afraid that it may hit the obstacles so we changed the design making it smaller one .
As far as the electrical components are concerned , we have used pixy camera for detecting the obstacles and used sonar sensors for avoiding the walls .



### Aim of participation:

**Skills Enhancement:** Develop expertise in robotics, coding, and problem-solving.

**Innovative Solutions:** Foster creativity in tackling challenges through innovative robotics solutions.

**Team Collaboration:** Strengthen teamwork and communication skills within a competitive environment.

**Global Engagement:** Engage and learn from a diverse global community of robotics enthusiasts.

**Critical Thinking:** Enhance critical thinking and problem-solving abilities in real-world scenarios.

**Competition Experience:** Learn to perform under pressure and manage time effectively in a competitive setting.

**STEM Advocacy:** Promote STEM education and interest in robotics and technology.

**Personal Growth:** Encourage individual growth and confidence through overcoming challenges.

**Technology Exposure:** Stay updated on cutting-edge technology trends in robotics and automation.


**NEW CAR VS OLD CAR**
![NEW DESIGN)](https://github.com/ACteamX/WroTeamX/assets/141714595/608c06b5-4983-4be8-89e8-85847c232f5f) ![sidetiltright](https://github.com/ACteamX/WroTeamX/assets/141714595/cb22b858-2131-4d04-bb26-f10d0f93bfd0)

**DIFFERENCES**

**1.DESIGN**

  **OLD CAR** We made a bigger car in National round for WRO and we have won too but we felt that it is too big to cross obstacles .
We were afraid that it might hit the obstacles with its big design.the dimensions of our old car are 26x19.8x25cm length width and height and the weight of this car was 1490g. Our old car was very close to maximum dimensions are weight allowed for the car so we had a concern of disqualification as well. We used thick 3D printed wheels as well in our old car. We used some 3d printed parts and used some PVC sheets for the upper base of our car , it was 3 storeys car which was very big so we decided to change it.

**NEW CAR** In the new car , we made a new design making it small and fast. We have made so many changes in our design. The new dimensions are very less than the dimensions of our prevoius robot.This Robot is fast and we have have made design flexible that we can easily change the components when required. 

**ELECTRONICS components**

**Old Car** In the old car, we used the raspberry pi and connected it with arduino by sending signals to arduino from pi and we used CV2 library for detecting the obstacles.We used Power banks to power our arduino and raspberry pi. Also, we used only two buck and boost convertors for powering the main motor , sensors and servo motor. This thing disturbed us so much that whenever servo motor moves that it produces noise in the sensors and readings fluatuates.So, we have faced so many issues in our old robot .

**New Car** In the new car, we have used Arduino due and for obstacle detetction we have used the pixy camera as it is easy to use and train models. For reducing noise, we have now used two batteries and 1 battery is connected in parallel with one buck convertor(giving 5V to sensors) and one buck-boost convertor(giving power to drive motor and Arduino Due), the other battery is connected with a convertor separately which is giving 5V to servo motor. Also for making the output smooth , we have used some capacitors in parallel fashion to all our components like sensors, motors etc.
So, these are the thing which we missing in our prevois Robot.


**Note**

****An important thing to note that is that we tried to use MPU920 and RGB color sensor for getting the best output but the sensors available in Pakistan are too noisy to use, we tried so many times for getting accurate readings but failed, with MPU920 we used kalman filter and it was working fine but when we tried to put it in our car then the readings started fluctuating and same faced same thing with RGB color sensor, so we tried to rely on encoder motor and pixy camera for making U-turn.
we have uploaded our all codes in the SRC file.**







