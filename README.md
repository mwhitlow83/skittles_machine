# skittles_machine
#### Machine that physically separates skittles candy by color

![alt text](<Screenshot 2024-07-13 at 5.12.46 AM.png>)


#### Items Required 
Adafruit_TCS34725 color sensor, arduino, 2 servos, leds, resistors and button.

#### Description of operation
One servo is located under the larger gear. in order for the slide to reach 270 degrees of rotation with a servo thats limited to 180 degrees a gear system is needed.

The second servo is located in the processing housing and it operates in the means of allowing one skittle at a time to be analysed by the color sensor. See photo
 below.
![alt text](<Screenshot 2024-07-13 at 5.31.44 AM.png>)

#### Calibration may be needed
The raw ADC value range for each color are used in condiitonal statements to indentify the color. The range was calculated by recording the ADC values of 10 pieces of 1 color and then conditional boundaries are set in the code.

#### Additional Requirments
The initial drop of the skiddles down the sorting slide is greater that what is needed for the skittle not to bounce out of the container. A mechanical structure is needed to slow the velocity of the skittle at the botton of the slide.