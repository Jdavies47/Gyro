# Light and Matter - lecture 8 24/10/2017

### The Bipolar junction Transistor

- The word is a contraction of the two words, transfer and resistor.
- The BJT is a key device in semiconductor technology.

Active mode operation:
- Increase of E-field at the BC junction: larger depletion zone width
- Decrease of E-field at the EB junction: smaller depletion zone width
- Holes inject from the emitter diffuse to BC junction and float up to the collector => base has to be narrow to minimise the charge carrier recombination.
- Current in active mode:
  - Emitter: I<sub>E</sub> = I<sub>E<sub>p</sub></sub> + I<sub>E<sub>n</sub></sub>
  - Collector: I<sub>C</sub> = I<sub>C<sub>p</sub></sub> + I<sub>C<sub>n</sub></sub>
  - Base: I<sub>B</sub> = I<sub>E</sub> - I<sub>C</sub> = I<sub>E<sub>n</sub></sub> - I<sub>C<sub>n</sub></sub> + (I<sub>E<sub>p</sub></sub> - I<sub>C<sub>p</sub></sub>)
- Characteristics of the BJT in the active mode:
  - Common base current gain: &alpha;<sub>0</sub> &equiv; I<sub>C<sub>p</sub></sub>/I<sub>E</sub>
- To optimize:
  - &alpha;<sub>0</sub> we need to &gamma;->1 and &alpha;<sub>T</sub>->1
  - &gamma;->1: minimise I<sub>E<sub>n</sub></sub> by p<sup>+</sup> doping of Emitter
  - &alpha;<sub>T</sub>->1: minimise base width and recombination of holes (generally W&lt;&lt;L<sub>p</sub>)


### Charge carrier distribution in BJT's
  - Assume:
    - Abrupt Junctions
    - minimal hole drift current
    - low injection
    - neglect generation and recombination in depletion zone
    - No serial resistance

  - Base:
    - Continuity equation:  
