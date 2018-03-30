# Biophysics - Lecture 13 10/11/2017

### Piosson-Boltzman Equation

Lets represent DNA as a tube that is charged. This tube is not necessarily straight.

What would happen if we put DNA (tube) and put it in a typical environment?

- Screening
- Debye length
- PBE (Piosson-Boltzman Equation)

Macromolecules exists in an aqueous environment.

Many macromolecules are charged. For example, DNA.

Many inorganic ions are in biological systems. E.g. Sodium +, chloride -, magnesium ++.

### Piosson-Boltzman Equation

- Piosson Equation: &Delta;<sup>2</sup>V = -&rho;/ D&epsilon;<sub>0</sub>
  - WHere V is the potential
  - &rho; is the charge density
  - D the dielectric constant of medium
  - &epsilon;<sub>0</sub> the universal constant.
- Boltzmann Equation: P(E<sub>i</sub>) = e<sup>-E<sub>i</sub>/k<sub>b</sub>T</sup>/Z

G = U - TS

Looking at this explains the answer to the distribution of charges around something like a DNA molecule.

U is dependant on -q<sub>1</sub>q<sub>2</sub>/r

At low temperature you would find that the charges would cluster near the DNA, so the TS term distributes the charges out more with a temperature factor.

This produces two competing factors of where the charged particles should be. Charge vs entropy. S wants the particles to spread out as much a possible.

This battle is to minimise G, the Gibbs energy. After this is minimised the Boltzmann equation can be used to find the probability of particle distribution.

Screening is just the equalling out of charges around a charged region, preventing the net charge in that region. The Debye length is the point at which the net charge equates to zero.

To derive this Piosson-Boltzman equation we need to first assume that we have both positive and negative ions with charges +ze and -ze. z is equal to the number of charges per ion.

Assume that our macromolecules is negatively charged. Then we expect high concentration of positive ions close to and around the molecule.

Electronically neautral: C<sub>+</sub> + C<sub>-</sub> = C<sub>&infin;</sub>

or

&Sigma;(i) z<sub>i</sub>e<sub>i</sub> = 0

Consider a planar membrane with net -ve charge (immobile), we are assuming that they are stuck on the membrane.

&sigma; = surface charge density.

We are also assuming that it is a very big membrane or that we are very close to it.

##### What can we say about the C's

The number densities of ions will be given by the Boltzmann factor(or the Boltzmann weight).

C<sub>+</sub>(*x*) = C<sub>&infin;</sub>e<sup>-zeV(*x*)/k<sub>B</sub>T</sup>

C<sub>-</sub>(*x*) = C<sub>&infin;</sub>e<sup>zeV(*x*)/k<sub>B</sub>T</sup>

Where v(x) is the electrostatic potential. (due in part the positions of mobile atoms, and some by the stationary negative charges on the surface of the membrane.)

The total charge density at x is:

&rho;(x) = zeC<sub>+</sub>- zeC<sub>-</sub>

and according to the Piosson equation:

d<sup>2</sup>V/dx<sup>2</sup> = &rho;(x)/D&epsilon;<sub>0</sub>

d<sup>2</sup>V/dx<sup>2</sup> = zeC<sub>&infin;</sub>/D&epsilon;<sub>0</sub> x {e<sup>zeV(*x*)/k<sub>B</sub>T</sup> - e<sup>-zeV(*x*)/k<sub>B</sub>T</sup>}

****This is the Piosson-Boltzman equation.****

This equation is non linear! So generally cannot be solved analytically.
