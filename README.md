# arduinoTrain
This library is a group of different Arduino scripts for use controlling DC model trains with an XY-160D Dual H-Bridge motor driver.
This is meant to do simple functions using variable voltages to a singular train on one track. Though, you can definitely adapt the code to whatever you want.

## Usage
Each script is a standalone script, this is not an official library, though that may be coming -see Roadmap
In order to use, simply download the script you'd like to use and start setting your base variables. This is all the variables that are 'defined' in the top
Set up your circuit, and upload the code. I recommend testing your output voltages to make sure they are safe levels for your trains.
My HO scale Bachman runs up to ~17V on the stock controls, so the limit as the 'max speed' variable I set was around that mark.
Be very careful using this code to run your trains, as they are all very different.

I am not responsible if you use this code and your trains get fried.

## Roadmap
Some potential areas where we may look into is making an offical Arduino library with the necessary functions to do simple tasks with your trains.
