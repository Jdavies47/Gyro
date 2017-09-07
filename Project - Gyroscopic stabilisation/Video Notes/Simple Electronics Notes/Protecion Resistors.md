# Calculating correct resistor value to protect an Arduino pin

It is important to make sure you are protecting electronic components from over current. The most common way to do this is by adding a resistor in series. You can use Ohms law to calculate the value of the guard resistor for safe operation.

### Protecting Arduino Pins from over current example

Consider the blink example for making a LED flash using the Arduino. If you look at the circuit, you will find that you are asked to connect a 220 Ohm resistor in series to protect the pin and the LED, but it is not mentioned hos or why this value is chosen.

##### Calculating protection resistance

A typical red LED has a voltage drop of 1.8V and requires a current of about 25mA. The Arduino pin has an output voltage of 5V.

Knowing this we can find the difference to calculate the voltage drop across the protection resistor (3.2V).

So using Ohms law we can find the resistance we need for the 25mA current draw:

R = V/I = 3.2V / 0.025A = 128 Omhs.

So a 128 Ohm resistor would be needed, but the tutorial asks for nearly double this.

##### Practical vs theoretical

So why does the tutorial ask for a 220 ohms resistance. The answer is as simple as practical easiness. The standard resistance of available are generally following the value:

{ 100, 220, 470, 1000, 2200, 4700, 10000 }

These are standard and are very easy to find compared to others.

Working out the reverse current values of the two resistors 100 and 220 ohms:

(1-100 Ohms) - I = V/R = 3.2/100 = 0.032A = 32ma

(1-220 Ohms) - I = V/R = 3.2/220 = 0.014A = 14ma

The operating currents of a standard LED is 10-25mA, so the 100 Ohms resistor would over current the LED. The 220 ohm resistor is therefore chosen out of ease.
