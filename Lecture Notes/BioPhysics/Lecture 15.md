# Biophysics - Lecture 15

### Molecular Dynamics Simulation

##### Methods

There is detailed notes to write up on the VLE.

Here we are looking at a real atomic view for the model of DNA.

##### What do we need to know to produce simulations of molecules?

Integrating Newton's equations of motion iteratively!

##### Bonded contributions to the potential energy of a typical molecules

- Bond lengths
- Bond angles
- Rotation about single bonds

But can classical mechanics really be used for simulation of molecules?

- We are talking in atomic scales so quantum effects will come into play, but the typical atoms in biology are H, C, N, O...
- And the typical temperature that these systems are operating in 290-300K.
- So if we look at the de Broglie Wavelength:
  - &lambda; = &sqrt;(2&pi;h(bar)<sup>2</sup>/mk<sub>B</sub>T)
  - SO for quantum effects to become significant we need &lambda; ~ d
  - This is when d is equal to the typical separations in that system (interatomic separation), which will be equal to the covalent bond length (~1.5&#8491;)
  - In biological systems &lambda;<<d, therefore it doesn't produce a effect worth measuring.
- We can go ahead with classical mechanics :)

#### Equations of motion and potential functions

F<sub>x</sub>(x)= -dV(x)/dx = mx(..)

V = 1/2 kx<sup>2</sup>
F(x) = -kx = m(..)

E<sub>D</sub>M: mx(..)+kx=0 => x(t)Acos(sqrt(k/m)t) + Bsin(sqrt(k/m)t)

But for non uniform potential, we would need to know the functions, but this is unlikely to be possible in analytical form. This also could not be solved.

This potentials would have to be solved numerically.

Taylor Series: x(t+&Delta;t) = x(t) + &Delta;tx(.)(t) + ....

Then look at the differential of this.

3D

Consider N particles in 3D,
  - position vectors r<sub>1</sub>,r<sub>2</sub>,
r<sub>3</sub>,....r<sub>N</sub>
  - potential V(r<sup>n</sup>)
  - Force on the i<sup>th</sup> particle: F<sub>i</sub> = m<sub>i</sub>r(..)<sub>i</sub> = - &nabla;V(r<sup>N</sup>)

So Doing the Taylor expansion as beofre:
