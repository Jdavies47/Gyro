# Voltage Dividers

Voltage dividers are circuits that use resistance to reduce the voltage in a circuit.

Uses include:

- Volume Control circuits
- Reference voltages
- etc

Ohms law is used to determine an voltage changes after an resistance is added to a circuit.
The voltage between two equal resistance resistors that have 1V across them would be 0.5V.
Looking at a circuit with two resistors, the voltage drop between the two resistors can simply
 be worked out as a proportion of the total resistance of the circuit, i.e.:

 GRN ------|\\|/ 20 ohms |\\|/|---0.2V---|\\|/ 80 ohms |\\|/|------>1V

Likewise:

GRN ------|\\|/ 80 ohms |\\|/|---0.8V---|\\|/ 20 ohms |\\|/|------>1V

So if you had R1 and R2 as the respective resistors:

V<sub>out</sub> = V<sub>in</sub>(R<sub>1</sub>/R<sub>1</sub>+<sub>R2</sub>) &nbsp;&nbsp;&nbsp; *(1)*

## Choosing the right resistors

Even though the voltage divided is just the ratio of the two resistors, the power dissipated
is also a very important factor to consider when putting the resistors in a real circuit.

Looking at the equation for the dissipated power we can see:

P<sub>dissipated</sub> = V<sub>in</sub><sup>2</sup>/ R<sub>1</sub>+R<sub>2</sub> &nbsp;&nbsp;&nbsp; *(2)*

So if we have a small resistance in both the resistors then the outputted power from
the resistors will be very high causing high temperatures and even ignition.

You should also consider the current draw of a circuit before building a voltage divider.
This is because a voltage divider is not the same as regulated power supplies and a significant voltage
drop will occur with any decent size current.
You generally should not be using a voltage divider if you are planning to be drawing anything more than 10mA.

To actually find the voltage supplies to a device, such as a microcontroller or motor is to first find the
Thevenin resistance of the divider using the equation:

R<sub>th</sub> = R<sub>1</sub>xR<sub>2</sub> / R<sub>1</sub>+R<sub>2</sub> &nbsp;&nbsp;&nbsp; *(3)*

This resistance can then be used with the resistance of the device you are trying to power with equation *(1)* to find the
actual loaded voltage the device will receive.
