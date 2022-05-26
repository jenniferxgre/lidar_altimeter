# LIDAR Altimeter for GA applications

## Introduction
This project was conducted as part of a university project at the HSRM university of applied sciences, Germany. The goal of the project was to evaluate the concept of utilizing optical distance sensors for determination of hight above ground in smaller aircraft. This provides higher safety in low visability conditions, such as night-VFR or special VFR conditions in GA aircraft not equipped with heavy and expensive radar altimeters.

## Hardware
Due to budget constraints, TeraBee's "TeraRanger Evo 60m" was chosen. It provides TOF-based infrared ranging for distances of up to 60 meters and can be interfaced via I2C or UART. The data transmission is boosted by I2C extender chips to compensate for increased line capacity of the 6 meter telephone cable and allow I2C to be used.

An Arduino nano microcontroller serves as the brains of the sensor system and coordinates all data exchange between the different components.

For analysis, all data is recorded onto an SD card. For this purpose, a micro-SD card reader is integrated via SPI. Additionally, the distance offset, which is dependent upon aircraft structure and mounting position, can be set by means of a push button, and is permanently saved on the SD card.

An I2C LCD display serves as live distance indicator, which is updated every second. In case no SD card was inserted, it also displays a warning message.

Audio callouts are played at specific heights through the "DFPlayer Mini" MP3 module.

## Software
The .ino-file implemented on the arduino nano for the project can be found in the repository: AltiSense_V1_1.ino

## Flight testing
The system was mounted to a Cessna 172 in Sept 2021 and tested in different lighting and flight conditions. The raw height data of those flights can be found in the "exampleData" subfolder. 

The flight testing validated the functionality of the sensor system in lower lighting conditions (i.e. sunset or sunrise). 
