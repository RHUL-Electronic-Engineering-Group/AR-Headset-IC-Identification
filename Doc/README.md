# Minimum viable product

The product shall be a custom Augmented Reality Solution for IC Identification. The product will recognise the text on top of an packaged IC chip and will display the relevent data for that chip onto a modified mobile phone AR headset using 2 mini displays.

### Must have:
* Controller on the headset must have following requirements:
* WiFi connectivity
* At least 3 spare IO pins for extra features
* Small enough to comfortable hold on the head (<50g)
* Low power (battery life of 12 hours or more)
* Able to run off battery
* Compatible with camera module
* Enough memory to hold program code
* Camera to take photo if IC in front of the user
* Implement a trigger that will instruct the camera to take a photo. Preferably a button
* AR headset with a camera mounted on it
* Connect wirelessly to a local network to send and fetch IC/image data
* Have a local server which will connect to the headset controller
* Local server will offer extra compute to recognise the text in the image and only send necessary data.
* Send the image captured by the headset to the local server and pass it through an optical character recognition program
* Display the relevant information captured from the image, either on a local computer or the headset.

### Should have:
* Heads up display
* Display the pinout of the IC on the heads up display
* Have the heads up display on at least one eye
* Have a high enough pixel density to make the GUI legible
* Have a local IC database of the IC’s in the lab containing essential information like pinout.
* Stream the camera view live to a web service
* Be able to read multiple IC’s in the same image
* Allow user to switch between detected IC data


### Could have:
* Highlight the IC the AR headset is currently reading and displaying data for
* Calibrate the POV of the camera to ensure the highlighted area is in line with the users eyes and IC
* Fetch online data about the IC if it is not present in the local IC database

### Don’t have:
* 
