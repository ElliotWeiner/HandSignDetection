# Hand Sign Detection

![Picture of Experimental Design](https://github.com/ElliotWeiner/HandSignDetection/blob/main/resources/media/IMG_4446.jpeg?raw=true)

*Experimental Design*

## Project Summary

This repository contains the source code for a novel hand sign detection system. It uses off-the-shelf components attached to a glove to remotely detect basic hand signs (thumbs up, thumbs down, open, close, and point). The device is designed for use as an Internet-of-Things (IoT) controller for various robotic and computer interaction projects, with plans for further expansion in the coming months. Below is an in-depth explanation of the hardware, software, communication protocols, and future work for this project.

## Hardware

![Picture of Hardware Uncondensed](https://github.com/ElliotWeiner/HandSignDetection/blob/main/resources/media/IMG_4418.jpeg?raw=true)

*Hardware Uncondensed*

#### Microcontrollers
The NodeMCU ESP8266 was selected as the primary microcontroller for the glove. This device provides significant advantages due to its wireless capabilities, allowing it to be configured as a wireless access point. This setup offloads more intensive tasks, such as machine learning queries, keeping both the financial and physical scale of the project relatively small. The main limitation of this microcontroller is its lack of analog pins—critical for flex detection. To overcome this, a Trinket M0 was used to expand the system’s GPIO.

#### Flex Sensors
Three flex sensors were implemented to measure the flexion of the thumb, pointer, and middle fingers, which were identified as the most crucial for detecting key hand signs. Each sensor is connected to an onboard voltage supply, and measurements are taken through a voltage divider, allowing for independent readings from each sensor.

#### 6-DOF Accelerometer
An Adafruit MPU6050 6-DOF accelerometer was included to capture basic hand orientation data, such as roll and pitch. The accelerometer was securely attached to the glove to ensure consistent measurements.

#### Wireless-Compatible Computer
A remote computer is used to interpret sign-related data. By connecting to an access point initialized on the ESP8266, the system uses a REST framework to transmit data (flex and orientation). The data is then processed by a deep neural network (DNN) to predict the specific hand sign in real time.

## Software

#### Machine Learning and Data Collection
Due to the variability in hand signs between individuals, machine learning was chosen to interpret the data. The network was trained using pitch, roll, thumb flex, pointer flex, and middle flex data to balance cost and performance. A dataset was collected through a simple aggregation algorithm, where hand signs were made and recorded, allowing for large-scale data collection in minutes. Given the simplicity of the problem, an effective network was designed and implemented in under an hour. Once tested, the network was integrated with the REST API to continuously interpret incoming data.

#### General Implementation
The software is structured into three key sections: data aggregation, data transmission, and data interpretation. The first section involves reading data from the accelerometer and flex sensors using on-hand devices. Analog pins on the Trinket M0 measure the voltage across the flex sensors, while the Adafruit MPU6050 is read via I2C connections. The data is transmitted from the on-hand device to a remote computer via a REST framework, utilizing the ESP8266’s wireless capabilities. The ESP8266 is initialized as a wireless access point, allowing external devices to connect. Finally, the data is processed by a DNN on the remote computer, and an output is printed for each prediction, completing the data pipeline.

## Communication Protocols

[See the Prototype Here](https://github.com/ElliotWeiner/HandSignDetection/blob/main/resources/media/IMG_4420.MOV)

#### Wireless and I2C
The ESP8266’s wireless capabilities were leveraged to create an access point available for remote connections. On this network, a REST web server was hosted on port 80 to allow for simplified data transmission from the on-hand resources. Additionally, Inter-Integrated Circuit (I2C) communication was used to connect the NodeMCU (master node) with the Trinket M0 and MPU6050 (slave nodes). These two communication protocols, when used together, enabled the creation of a wider Internet-of-Things system.

## Future Work

Several key issues limited the capabilities of this project. One of the main problems was the delay in the wireless network, which caused consistent gaps in data transfer. This resulted in 'pauses' during hand sign inference—depending on the application, this could lead to anything from delayed response to catastrophic failure. Additionally, the lack of sensing on the ring and pinky fingers somewhat limited the number of key signs that could be made, reducing the overall versatility of the system. The adhesion of the sensors to the glove was also relatively ineffective (hand-sewn thread for the flex sensors and hot glue for the MPU6050), meaning the design could benefit greatly from more robust construction.

Future expansions have been considered, particularly in the fields of computer-interactive and robotic applications. Designs for detecting motion in addition to static hand signs have already been conceptualized and would require either the same or upgraded hardware. As such, the problem becomes one of software design, which is relatively simple to address. This would enable unique interactions with computers, akin to Tony Stark working hands-on with holograms (minus the holograms). Additionally, combining this project with other fields could yield innovative ways of interacting with technology. For instance, the introduction of acoustic recognition software could enable more intuitive methods of interaction. Other directions for future work include 3D point detection, dataset aggregation, and further cross-disciplinary developments.
