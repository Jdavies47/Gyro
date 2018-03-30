# Biophysics - lecture 7 24/10/2017

### Carrying on from last lecture

Looking back at the isolated systems. (the barrier systems, one allows heat energy, one allows volumes to change, one that allows the number of particles on each side to change)

In each in these cases, right down the entropy and the variables to work out how to maximize the entropy.

##### How do we calculate the entropy of an isolated system?

**DNA example:**

Assume:
- N binding sites on DNA
- N<sub>P</sub> of them are occupied by a protein.
- Binding energy is the same at all sites.

***Entropy*** - The entropy is a measure of the number of microstates that correspond to a particular macro state.

S = k<sub>B</sub>ln(W)

(where w is the statistical weight.)

What is a microstate: The

What is a macro state: N<sub>P</sub> is the macro state.

Find W(N<sub>P</sub>;N) = the number of ways of arranging N<sub>P</sub> things on N sites.

Total number of ways of arranging N<sub>P</sub> proteins of N sites = N(N-1)(N-2)....(N-N<sub>P</sub> + 1)

This is an overestimate -> e.g. swapping any two proteins gives no change.

- The are N<sub>P</sub> ways of occupying the first state.
- There are (N<sub>P</sub>-1) ways of occupying the second site.
- etc

W(N<sub>P</sub>;N) = N(N-1)(N-2)....(N-N<sub>P</sub>+1)/N<sub>P</sub>(N<sub>P</sub>-1)...(2x1) = N!/N<sub>P</sub>!(N-N<sub>P</sub>)! (the number of ways of occupying all the sites with N<sub>P</sub> proteins.)

Therefore:

S = k<sub>B</sub>ln[N!/N<sub>P</sub>!(N-N<sub>P</sub>)!]

Stirling approx: ln(N!) ~ NlnN-N for large N.

Therefore:

S = k<sub>B</sub>N[cln(c)+(1-c)ln(1-c)]

Where c = N<sub>P</sub>/N.

#### Introduction to Gibbs energy

We now need to develop a more complicated way of representing systems other than as an isolated system, as this is unrealistic.

It is necessary to do this when the system is not isolated. (Any biochemical system that will be encountered). It also need to share energy and matter with its surroundings.

1. A ***Closed system*** can exchange energy with its surroundings
1. A ***Open system*** can exchange energy and matter with its surroundings
1. A ***Isolated system*** can exchange neither with its surroundings.

Construct: Composite system<sub>tot</sub> = Original system<sub>S</sub> + reservoir<sub>r</sub>.

We are making the assumption that the Composite system is isolated.

Lets suppose we want to maximise the entropy of the isolated system using the second law of thermodynamics. => entropy will increase as the system moves towards equilibrium.

dS<sub>tot</sub> = dS<sub>s</sub> + dS<sub>r</sub> &ge; 0

From the first law of thermodynamics:

dE<sub>r</sub> = T dS<sub>r</sub> - P dV<sub>r</sub> (is the change in energy of the reservoir)

Therefore:

 dS<sub>s</sub> + dE<sub>r</sub>/T + PdV<sub>r</sub>/T &ge; 0

but the composite system is isolated:

dE<sub>r</sub> = -dE<sub>s</sub>

dv<sub>r</sub> = -dV<sub>s</sub>

Therefore:

***dS<sub>s</sub> - dE<sub>s</sub>/T - PdV<sub>s</sub>/T &ge; 0***

or

***dG = d(E<sub>s</sub> - TS<sub>s</sub> + PV<sub>s</sub>) &le; 0***

Where:

G = E - TS + PV (Gibbs energy)
