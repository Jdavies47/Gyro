# Biophysics - Lecture 14

### End of last Lecture

We were looking at the Piosson-Boltzmann equation.

d<sup>2</sup>V/dx<sup>2</sup> ... in book

This is a non-linear equation, but we can solve it ish.

We can make the P.B.E linear is V(x) is small. so:
  - exp(-+ zeV(x)/k<sub>B</sub>T) ~> 1-+zeV(x)/k<sub>B</sub>T

Then PBE becomes:

d<sup>2</sup>V/dx<sup>2</sup> = 2z<sup>2</sup>e<sup>2</sup>c<sub>&infin;</sub>/D&epsilon;<sub>0</sub>k<sub>T</sub>T * V(x)

THIS IS LINEAR! This is also known of the Debye-Huckel eqn. This can be solved easily.

### When is V(x) small?

V(x)&lt;&lt;k<sub>B</sub>T/e=25mV


### How do we solve this equation?
Lets write it as:

d<sup>2</sup>V/dx<sup>2</sup> = 1/&lambda;<sub>D</sub><sup>2</sup> * V(x)

Where &lambda;<sub>D</sub> is the Debye length.

So lets try as a solution:

V(x) = Ae<sup>-x/&lambda;<sub>D</sub></sup> + Be<sup>x/&lambda;<sub>D</sub></sup> Where A and B are constant.

Boundary Conditions:

 V(&infin;) = 0 ----> This leads to B=0, to get rid of the growing term.

 E<sub>x</sub>(0) = &sigma;/&epsilon;<sub>0</sub>D = -dV/dx

 Where &sigma; is the surface charge density.

 Therefore doing the differential we get that A = &sigma;&lambda;<sub>D</sub>/D&epsilon;<sub>0</sub>

 This leads too:

 V(x) = &sigma;&lambda;<sub>D</sub>/D&epsilon;<sub>0</sub> * e<sup>-x/&lambda;<sub>D</sub></sup>

 and we have got:

 &rho; = -&sigma;/&lambda;<sub>D</sub> * e<sup>-x/&lambda;<sub>D</sub></sup>

 #### Looking at a spherical example:
