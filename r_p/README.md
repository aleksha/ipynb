# Bias in a proton radius refit

0.86 fm is used as an input to generate 70M events.
The 1000 bin histogram for Q2 in between of 0.001 and 0.04 if refitted with
a proton charged radius as a free perameter.

Three typical prob;ems are considered:
 1. Systematical shift of a Q2 value (in a unites of 10^-6 GeV^2)
 2. Stratch where a  shift is a linear function of Q2 increasing from zero to a value.
 3. Same as previous but the highest Q2 is fine and a bias occurs to a lower Q2.

 * `refit2.C` - constant shift
 * `refit3.C` - stratch higher values (low fixed)
 * `refit4.C` - stratch lower values (high fixed)
 * `graph.py` - to draw a resulut.


## Result

Worst case scenarios 10^-6 shift in a Q2 (0.1% in a relative value) causes 0.005 fm bias in the Rp.

See `Bias.png`
