# Transistor / MOSFETs

### What is a transistor?

A transistor is a device that allows you to use small changes in voltage to switch things on and off. They can be thought of as a valve for electric current.

### n-channel MOSFET

A n-channel MOSFET (Metal Oxide Field Effect Transistor) is a one type of transistor (an easiest) that can handle a larger current. They work as simply as if the transistor is not powered no current can flow, and vice versa.

A n-channel MOSFET has three pins, known as the gate drain and source. A labelled picture of this can be found in `Project - Gyroscopic stabilisation\Video Notes\Pictures` as Note_picture_4.

1. Drain - this is the pin current will drain into.
1. Source - this is the pin current will flow out of.
1. Gate - this is the pin that will turn the transistor on and off.

The source of a transistor should be connected up to the circuit ground with the drain being connected to the negative side of your load with the positive side of the load being connected to the positive side of the external power supply.

The circuit will be either be on or off depending on the whether the gate is receiving 5V or 0V respectively. A picture of a on transistor in a circuit can be seen in Note_picture_5.

A key factor of MOSFETS is that they are variable resistors controlled by the signaling voltage. After a threshold voltage is supplied to the gate the resistance of the transistor drop allowing a current to flow. This drop in resistance is very sharp. Since this resistance is between the drain and source, the resistance is known as R<sub>DS</sub>ON.

It is also important to check the gate to source voltage of a MOSFET when using them, in a logic circuit. To be used by an Arduino the V<sub>GS/TH</sub> must be lower than 5V. 

Since MOSFETS are used in high current applications, it is also important to check the Power dissipated using:

P<sub>dissipated</sub> = R<sub>DS</sub> x I<sup>2</sup>

To find the maximum power that a MOSFET can handle WITHOUT using a heat sink we can use the equation:

P<sub>dissipated</sub> = T<sub>junction-max</sub> - T<sub>ambient</sub> / R<sub>junction-ambient coefficient</sub>



### Safety

The gate of the transistor has a couple of limitation of the control voltage to switch the transistor on and off. The signaling voltage should be kept below 15V to avoid damages.

However the drain and source voltages are a lot more flexible and dependent on the transistor, but can support much greater voltages.

### More transistors

- npn transistors
- pnp transistors
- p-channel MOSFET
- JFET
