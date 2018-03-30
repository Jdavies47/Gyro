# Biophysics - Lecture 10 31/20/2017

### Two Possible models for polymers

1. Worm like chain (WLC) - Thin tube that is wiggling around in solution. Continuously deformable, with energies involved in the deformations. Bending &prop; (1/R)(k<sub>b</sub>T). Where R is the radius of curvature.
1. Free jointed chain (FJC) - Consists of N rigid rods of equal length L that are joined by hinges. There is no energy cost in changing the shape of the angle between any two rods. Where the angle between two rods would be &theta;.

##### Consider a one dimensional model (1D FJC)

Look in book for diagram.

Force f is exerted externally

Introduce a state variable &sigma;:

         {+1 link pointing to right
&sigma; ={
         {-1 link pointing to the left

Assume N Segments.

The internal energy U of teh system is:

U = U<sub> internal (conformation)</sub> + U<sub>external (external forces)</sub> = 0 - fZ

The end to end length of the molecule:

Z = L &Sigma;&sigma;<sub>i</sub> for N; i = 1

The probability of the conformation with state variables

{&sigma;<sub>1</sub>, &sigma;<sub>2</sub>, ... , &sigma;<sub>N</sub>} is :

P(&sigma;<sub>1</sub>, &sigma;<sub>2</sub>, ... , &sigma;<sub>N</sub>) = e<sup> -U/k<sub>B</sub>T</sup> / Z<sub>conf</sub>

where Z<sub>conf</sub> is the configurational partition function.

Using the above with the further above:

P(&sigma;<sub>1</sub>, &sigma;<sub>2</sub>, ... , &sigma;<sub>N</sub>) = e<sup> +fL&Sigma;&sigma;<sub>i</sub>/k<sub>B</sub>T</sup> / Z<sub>conf</sub>

Where Z<sub>conf</sub> =(&Sigma;&sigma;<sub>1</sub>=+/- 1)(&Sigma;&sigma;<sub>2</sub>=+/- 1)...(&Sigma;&sigma;<sub>N</sub>=+/- 1) e<sup> +fL&Sigma;&sigma;<sub>i</sub>/k<sub>B</sub>T</sup></sup>

From this we can find the mean end to end distance &lt;&gt;

&lt;z&gt; = (&Sigma;&sigma;<sub>1</sub>=+/- 1)(&Sigma;&sigma;<sub>2</sub>=+/- 1)...(&Sigma;&sigma;<sub>N</sub>=+/- 1)P(&sigma;<sub>1</sub>, &sigma;<sub>2</sub>, ... , &sigma;<sub>N</sub>)z

**&lt;z&gt; = ((&Sigma;&sigma;<sub>1</sub>=+/- 1)(&Sigma;&sigma;<sub>2</sub>=+/- 1)...(&Sigma;&sigma;<sub>N</sub>=+/- 1)e<sup> +fL&Sigma;&sigma;<sub>i</sub>/k<sub>B</sub>T</sup>L &Sigma;&sigma;<sub>i</sub> )/ Z<sub>conf</sub>**

&lt;z&gt; = k<sub>B</sub>T d/df ln[e<sup> +fL&Sigma;&sigma;<sub>i</sub>/k<sub>B</sub>T</sup> ]

&lt;z&gt; = k<sub>B</sub>T d/df ln [&Sigma;e<sup>fL&sigma;<sub>1</sub>/k<sub>B</sub>T</sup>&Sigma;e<sup>fL&sigma;<sub>2</sub>/k<sub>B</sub>T</sup>...&Sigma;e<sup>fL&sigma;<sub>N</sub>/k<sub>B</sub>T</sup>]

&lt;z&gt; = k<sub>B</sub>T d/df ln [e<sup>fL/k<sub>B</sub>T</sup> + e<sup>-fL/k<sub>B</sub>T</sup>]<sup>N</sub>

&lt;z&gt; = NL [(e<sup>fL/k<sub>B</sub>T</sup> - e<sup>-fL/k<sub>B</sub>T</sup>)/(e<sup>fL/k<sub>B</sub>T</sup> + e<sup>-fL/k<sub>B</sub>T</sup>)]

***&lt;z&gt; = NL tanh(fL/k<sub>B</sub>T) = L<sub>t</sub> tanh(fL/k<sub>B</sub>T)***

Where L<sub>t</sub> = contour length
