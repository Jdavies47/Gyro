# Second year quantum physics

## Lecture 1

**Classical Physics** - The universe is deterministic. If we know the initial conditions well enough we can calculate how a system is going to evolve.

**Quantum Physics** - Both Revolutionary and non-intuitive.
- A fundamentally non-deterministic universe.
- The evolution of a system depends on your observation of it.
- Schrödinger's cat, wave-particle duality.

**The context** - Systems that depend on atomic scale-effects.
- Particle
- Nuclear
- Atomic
- Molecular

#### Failures in Classical Mechanics

1. Atomic Spectra
1. Stability of Matter
1. Bonding of molecular Systems
1. The ultraviolet catastrophe

#### Wave-particle duality
Already well established that light exhibits both wave and particle behaviour [Young 1804 and Einstein 1905]:
- **Wave** - Interference, diffraction, refraction
- **Particle** - Photoelectric effect, Compton Scattering. (See note book for equations) - 1

de Broglie Hypothesised that wave-particle duality also applied to matter as well as radiation.
- particle has associated matter wave.
- wave properties

(See note book for equations) - 2

**Bohr's principle of complementarity** - wave and particle 'models' are complementary: the properties that we observe depend on what we are measuring.

de Broglie Wavelength examples in note book - 3

#### Young's double split experiment

- **Propagation**: Its a wave
- **Detection**: Its a particle.

The electron, neutron, etc... must have passed through both slits at the same time: position is indeterminate.

1. Explained by the uncertainty principle (See note book for equations) - 4
1. In its wave-nature, the momentum of the particle is precisely defined (&lambda; = h/p), so the position *must* be indeterminate.
1. Therefore: if we measure *x* we must destroy the wave-nature of the particle.

## Lecture 2 - The wavefunction &Psi;

### The importance of the wavefunction, &Psi;

The concept of the wavefunction &Psi;(x,t) is central to quantum mechanics:
- A quantum mechanical system (e.g. an electron in an atom and &alpha;-particle, a semi-conductor crystal) can be described completely by the wavefunction.
- If we know &Psi; then we know everything (possible) about the system.
- Cannot be observed: is not identified with a single physical property.

**Postulate 1**: For any system of particles, there exists a wavefunctionfrom which all possible predictions about the physical properties of the system can be obtained. The wavefunction is continuous, single-valued and normalisable, and is generally complex.

### Probability interpretation - Born Postulate

The wavefunction has no direct physical meaning (i.e. is not an observable) but we can extract physical interpretation (observables) from it. For example, we can use the square of the modulus:
<p style="text-align: center;">|&Psi;|<sup>2</sup> = &Psi;<sup>&#42;</sup>&Psi;</p>

The probability of finding the particle at position x at time t (bewteen x and x+dx) is given by the probability density P(x,t):

<p style="text-align: center;">P(x,t)dx = |&Psi;|<sup>2</sup>dx</p>

If the wavefunction is known, we can calculate the probability of finding the particle in a particular region, but this is all that can be known about the position.

### Properties of wavefunctions

1. Normalisable - particle must be found somewhere in the system: &int;P(x,t)dx=1. So the total probability must be 1.

1. Continuous - If the wavefunction is not continuous, the gradient of the wavefunction at that point is undefined. As with any wave, the energy and momentum stored in the wave is related to the slope of the wave, and the momentum and energy are therefore undefined.

1. Single-valued - Particle cannot have two probabilities for being in the same position.

These conditions ensure that the wavefunction is physical. However, as soon as you have two components of a wavefunction (or two wavefunctions), the complex nature of the wavefunction become critical through its phase.

<p style="text-align: center;">&Psi;<sub>2</sub>(x,t) = &Psi;<sub>1</sub>(x,t)*e*<sup>-i&phi;</sup></p>

### Superpostion and phase in diffraction

- One state of the system described by a wavefunction &Psi;<sub>1</sub> and another state of the system by a wavefunction &Psi;<sub>2</sub>.
- Then any (normalised) linear combination:
<p style="text-align: center;">&Psi; = c<sub>1</sub>&Psi;<sub>1</sub> +c<sub>2</sub>&Psi;<sub>2</sub></p>
is also a possible wavefunction of the system. Where c<sub>1</sub> and c<sub>2</sub> are complex.
- So the combined probabilty of a particle position on a screen:
<p style="text-align: center;">|&psi;|<sup>2</sup> = |&psi;<sub>1</sub> + &psi;<sub>2</sub>|<sup>2</sup> = |&psi;<sub>1</sub>|<sup>2</sup> + |&psi;<sub>2</sub>|<sup>2</sup> + &psi;<sub>1</sub><sup>&#42;</sup>&psi;<sub>2</sub> + &psi;<sub>2</sub><sup>&#42;</sup>&psi;<sub>1</sub></p>
becomes critically dependant on exactly which combination of the two wave functions we have in each position.
- The phase &phi; of any component of a wavefunction defines its corresponding front factor c=*e*<sup>-i&phi;</sup>=1.

To achieve interference in the double split experiment, each particle must have passed through both slits:
- Particle trajectory is not just unknown, it is indeterminate.
- Quantum mechanics abandons the classical idea of a particle trajectory. Instead it uses probabilities based on wave packet concept.
- It becomes critical to understand the phases of the two waves as they hit the screen.
- Probability of particle position on a screen:
<p style="text-align: center;">|&psi;|<sup>2</sup> = |exp(-i&phi;<sub>1</sub>(x)&psi;<sub>1</sub> + exp(-i&phi;<sub>2</sub>(x)&psi;<sub>2</sub>)|<sup>2</sup></p>
