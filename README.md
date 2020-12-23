# ipynb

My IPython notebooks as code examples for myself.

## conda envoirements

First you have to install and update conda. Here are the commands:
```bash
wget http://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh
sh Miniconda3-latest-Linux-x86_64.sh
source ~/miniconda3/etc/profile.d/conda.sh # replace "~/miniconda3/" with your conda path if you've changed it
conda config --add channels conda-forge
conda update -n base -c defaults conda
```

To install envoirement containing: `geant4`, `root`, `ostap`, `scipy`:
```bash
conda create --name hep-env --file requirements.txt
```
