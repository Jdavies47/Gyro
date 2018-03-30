# Light and matter - 06/11/2017

### The Mosfet

V<sub>T</sub> is the threshod voltage, when we exceed this, as it marks the transition, we get strong inversion. V<sub>G</sub> > V<sub>T</sub>

As we increase the drain voltage we get a linear increase in current until the saturation point when all the charge carriers are being used.

  - Sub threshold region:
      - Operation of MOSFET as low voltage leading to low power devices; applications as a switch in digital logic and memory devices.
      - Drain current: I<sub>D</sub> = -eAD<sub>n</sub> dn/dy Where n is the concentration of charge carriers.
        - (if n is small) ~ eAD<sub>n</sub> (n(0) - n(l))/(L) Where L is the gate width, n(0) the electron density at the source and n(l) is the electron density at the drain.
        - n(0) = n<sub>i</sub>exp(e[&phi;<sub>s</sub> - &phi;<sub>B</sub>]/K<sub>B</sub\>T)
        - n(l) = n<sub>i</sub>exp(e[&phi;<sub>s</sub> - &phi;<sub>B</sub> - V<sub>D</sub>]/K<sub>B</sub>T)
        - &phi;<sub>s</sub> is the surface potential at source.

      => I<sub>D</sub> eAD<sub>n</sub> n<sub>i</sub>/L exp(-e) continued in Lab book

      - of &phi;<sub>s</sub> ~ V<sub>G</sub> - V<sub>T</sub> (sub-threshold condition)
      - Minimise I<sub>D</sub>
        - Chose large enough V<sub>G</sub>

### Solar Cells

Irradiance - explains the source.

&lambda;<sub>c</sub> is directly related to the band gap.

E = h(bar)&omega; => hc/&lambda;<sub>c</sub>

- Creation of electron hole pairs in the valence band and the conduction bands via electromagnetic radiation.
- Use of n tyoe silicon (shallow) on bulk p type silicon
- Silicon is not very good but is affordable and abundant.
- Increase of efficiency by use of anti-reflective layer.
- Light shines bewteen the metal contact ridges.
  - I<sub>L</sub>: light induced current.

##### Band Structure

Picture in lab book.

- Open CIrcuit voltage V<sub>OC</sub> (for I = 0):
  - => V<sub>OC</sub> = k<sub>B</sub>T/e * ln(I<sub>L</sub>/I<sub>s</sub> + 1) ~ (for I<sub>L</sub>>>I<sub>s</sub> )  V<sub>OC</sub> = k<sub>B</sub>T/e * ln(I<sub>L</sub>/I<sub>s</sub>)

#### Power Output of solar cell

P = VI = I<sub>s</sub>V[exp(ev/k<sub>B</sub>T)-1]-I<sub>L</sub>V

###### Max power obtained dp/dv=0

- Max voltage V<sub>M</sub> = k<sub>B</sub>T/e * ln((1+I<sub>L</sub>/I<sub>s</sub>)/(1+eV<sub>M</sub>/k<sub>B</sub>T))

=> V<sub>M</sub> ~ V<sub>OC</sub> - k<sub>B</sub>T/e ln (1+eV<sub>M</sub>/k<sub>B</sub>T)

I<sub>M</sub> ~ I<sub>L</sub>[1-k<sub>B</sub>T/eV<sub>M</sub>]: Maximum current => P<sub>m</sub> = I<sub>M</sub>V<sub>M</sub>

I-V Charcteristics
- I<sub>SC</sub> is the short circuit current.
- The rectangle formed from V and I is the efficiency of the solar cell so we want to maximise the area.
- efficiency: &eta; = I<sub>m</sub>V<sub>m</sub>/P<sub>inp</sub> = FF.I<sub>L</sub>V<sub>oc</sub>/pimp

Fill Factor (FF) = I(m)V(m)/I(L)V(oc)

P<sub>input</sub>: integration of all the photons of the solar spectrum.
- Increase efficiency by spectrum splitting
  - dedicated band gap SC for different parts of the solar spectrum
- Degrading factors:
  - Low resistivity at the metal interfaces and the pn-junction (serial resistance)
  - reduced &tau; due to recombination centres in depletion zone.
  -
- Optimisation factor:
  - Large p-n area

### Photodetector

- Photodetectors convert optical signals into electrical signals.
- Incident light produced electron/hole pairs.
- Charge carriers are transported to electrical circuits.

1. Photoconductor -
