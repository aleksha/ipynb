# AKIP measurements

## Init and out spectra

See:
 * `view.py` for exaple;
 * `viewer.py` do all statistics (quite lonf).

Examples are in `figs/init.png` and ``figs/out.png``

Charge pulse (black histogram) obraned by differentiation of init voltage.


## Input pulse stability

For different inital pulses a set of five measurements were produced.
All measurements gives same distribution of the initial pulse.
Kolmogorov-Smirnov test suggests that they are same.

See `disto.py` and figures in `figs/`.


## Bootstrapping

With the bootstapping technique one can validate an a distribution for any 
statistics. This is done for a means and medians of initial-pulse 
energy distributions. The mean value has no bias as well as uncertainties, 
which follows standard **1/sqrt(N)** rule.

For the meadians an uncertainty of the statistics is obtained _via_ bootstrap.

Script `bootstrap.py`

See results in `results.txt`.
