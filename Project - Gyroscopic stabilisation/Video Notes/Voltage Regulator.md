# Voltage regulator

## What is a voltage regulator?

A voltage regulator is a device that takes a unregulated input voltage which can be challenging overtime and outputs a smooth output voltage. So if we have a 16V DC supply with a 2V ripple on it and we feed it into a 12V regulator, the output will be a constant 12V.

Most regulators will have the same naming convention, looking something like: `**78XX**` where the *'s will be some letters and the XX an indication of the Voltage it will supply. For example:

**LM7809AC** is a 9V regulator.

## Things to note:

- Linear Voltage regulators are inefficient.
- They also have a drop out voltage.

#### Efficiency

To work out the power dissipated from a regulator we can the equation:

P<sub>dissipated</sub> = (V<sub>in</sub> - V<sub>out</sub>) x I<sub>out</sub>

In general you want to avoid high input voltages with linear regulators as this makes them very inefficient.

Efficiency of linear voltage regulator ~= V<sub>out</sub>/V<sub>in</sub>

#### Dropout voltage

The dropout voltage refers to the minimum input voltage that you have to pass to the regulator to guarantee a stable output. Most of the time your input voltage will have to be a volt or 2 above the voltage you are trying to supply. So the given amount of dropout voltage on a data sheet refers to the "head room" you have in your input voltage.

See Note_Picture_1 in `Project - Gyroscopic stabilisation\Video Notes\Pictures` for an example circuit for a regulator
