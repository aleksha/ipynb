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

## Two ways to measure Vin

There are a better way to meassure input signal. The input voltage is measured 
with 1000 of first AKIP channels and 1000 of last channels. The difference is 
independent on structures before and after pulse.

An example is obtained with script `corr.py`.

For the channel 0007:
  * No visible correlations between two methods are visible on a scatter plot
  * See `figs/Corr_AD_AI_0007.png`
  * Relative precision for this case:
      + AD methos: 1.11 %
      + AI method: 0.25 %
  * Both methods demonstrate no visible correlation with the reconstructed 
     energy of amplified signal. See:
      + `figs/Corr_AD_e1_0007.png`
      + `figs/Corr_AI_e1_0007.png`
  * Indeed, AI-method is betted, due to higher precision.

## Liniarity check

Script `lin.py`.

This uses AI algo. Script to calculate systematic uncertainty of reconstructed 
energy. This uncertainty is an additional uncertainty to each of 5 point, which
gives Chi2/NDoF=1 for linear fit.


**The resulting systematics is order of 3 keV**.





