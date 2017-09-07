# Pull Up and Pull Down resistors

## Pull-up resistors

Pull up resistors are used in logic circuits to ensure the inputs of devices like Ardinuos settle at expected logic levels if external devices are disconnected or high impedance. 'Just because you have nothing at all connected to an input pin, doesn't mean it is a logical zero.'

A pull-up resistor weakly "pulls" the voltage of the wire it is connected towards its voltage  source level when the other components on the lone are inactive. When the switch on the line is open, it is high impedance and acts like it is disconnected, and the pull up resistor brings the wire up to the high logic level. When another component on the line goes active, it will override the high logic level set by the pull-up resistor. The pull up resistor assures that the wire is at a defined logic level, even if no active devices are connects to it.

## Pull-down resistor

A pull-down resistor works in the same ways as a pull-up resistor but is connected to the ground. It holds the logic signal near zero volts when no other devices are connected.

The value of a pull down or pull up resistor will vary depending on the devices involved.

## Pictires

For a circuit representation of both pull-up and pull-down look in `Project - Gyroscopic stabilisation\Video Notes\Pictures`:

- Pull-up - Note_picture_2
- Pull-down - Note_picture_3
