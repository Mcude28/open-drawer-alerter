# open-drawer-alerter
Authors: Michael Ude (Myself), Ashley Olson, and Doua Vue

This project was a group project done at the University of Minnesota Twin cities in the
introduction to computing systems course (EE 1301). This project is ran with our a Particle
Device where it is programmed to alert the owner if an unwanted person is entering into a
drawer.

#project description 
Growing up in a large family, privacy isn’t something that your siblings would know when it
comes to your stuff. Not a lot of people are lucky enough to have their own rooms, locks on their bedroom doors, or specified keys to the locks as well. Some stuff 
that one might want to
keep to themselves are snacks, personal belongings such as files, records and even personal journals or diaries. One would usually keep these things in their 
drawers, but because it is one of the most obvious places to keep your stuff, one's siblings would definitely check there. Therefore we have come up with a device 
that alarms anyone that would come digging through your drawers. 

Since our device is light sensitive, it consists of one light sensor which makes the alarm to turn on when the sensor detects light of a certain intensity. This is 
under the assumption that your pesky intruder would be assuming that whoever is going through your drawers would turn on the light or be using a flashlight to be 
able to see when digging through your stuff. When the alarm is inside the drawer it will be dark, therefore the sensor will not detect enough light to activate the 
alarm. Upon opening the drawer, the sensor will detect the light you use to be able to see whatever is inside and will meet the threshold set to activate the alarm, 
and the alarm will go off. 

The alarm on our device is operated with two actuators. They consist of eight flashing LEDs
with changing, randomized colors and intensities, and a piezo buzzer. The LEDs are set to
flash at a very high frequency right away when the alarm goes off and then at a lower frequency after some time has elapsed. The buzzer makes an obnoxious noise at 
the frequency at which the LEDs blink.  After the initial trigger of the alarm, it will continue to go off regardless of whether it is placed back into the drawer or 
not. This is because the light from the LEDs are very bright triggering the light sensor on the broad. This annoyingly indefinite alarm is sure to make any siblings, 
parents, or friends think twice about going through your stuff again! 
The alarm on our device will only turn off when its owner wants it to be turned off, and they do this by pressing a button on their phone turning the alarm off. When 
we press the button to turn it off, IFTTT communicates with it to the device to turn it off 
through its wifi connection. To simply set up the alarm again, the owner can put the alarm back in the drawer and press the reset button on their phone to reset it. 

#Code Description
Our code utilizes a series of functions and enums to have them collaborate with each other to have our alarm work. First, we set our enum to have two separate 
settings (ie. ON and OFF). Which we can initialize to be on. With this mode, it allows us to set pre existing conditions for the alarm to turn on and off.  While 
the enum labeled alarm_on is set to ON, the code is automatically searching for a light intensity below 1500 (around 1500 is really dim light and higher 
brightness outputs a smaller value). Where it gets sent to the function (alarm) to blink the LEDs and turn on the speaker. It also is capable of checking the 
light intensity in the terminal. Otherwise, if the mode is set to OFF then it will shut off the lights and no longer run through the function that turns the 
speaker on. Since the LEDs store memory, simply stopping the function from being run will not turn off the lights. With our two particle functions initialized in 
the setup, we can communicate to the photon through the cloud whether or not the mode is set to on or off. Thanks to IFTTT, we set a widget that inputs a string 
into a specific function that can switch the mode from on to off. Thus allowing the programmer to iterate through each mode whenever they please.

#schematic
![Screenshot 2023-05-17 145223](https://github.com/Mcude28/open-drawer-alerter/assets/133912612/06187a36-2b53-4166-b522-ea6cb142bd99)

