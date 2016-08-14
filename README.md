# LaunchPad_3x7-Segment_Booster_Pack

#Description
This is just a simple 3x7-segment display that can be plugged into the TI MSP430 

#Background Info
I wanted to make my own 7-segment LED display booster pack for the LaunchPad that doesn't use a display driver IC, such as the CD4056BE, or SN7446A. In other words, I wanted to be in control of the firmware to perform driving the segments of each digit and performing the digit scanning function. 
So, I came up with this nifty little board - very simple. It includes a buffer driver IC, since the MSP430 IO pins are not rated to drive this much current in total. 
It was also a learning exercise, in that it was the first project where I used KiCAD's EDA software to learn all the ins and outs of creating schematic decals, PCB footprints, working with the component library interface, maping the schematic decals to the PCB footprints. And for the finishing touch, using Wings3D for creating the solid rendering of the boards. It was fun, easy, and it worked and I learned a lot in the process. 
Checkout the video in the links section below to see it in action!

#Links
##CascoLogix Product Page:
http://www.cascologix.com/store/p3/LaunchPad%C2%A03x7-segment_Booster_Pack.html
##Tindie Product Page:
https://www.tindie.com/products/CascoLogix/msp430-launchpad-3x7-segment-booster-pack/
##Hackaday Project Page:
https://hackaday.io/project/1779-launchpad-3x7-segment-display-booster-pack
##OSHPark PCB Page
https://oshpark.com/shared_projects/FeiOSTLi
##Video
https://www.youtube.com/watch?v=f7Dp6MClfQ0
