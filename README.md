#Optics analysis

##SlimRootfiles

1. Generate a root file with only primary electrons that reach the main detector
2. run it (remember to change the parameters inside):
```
   root -l 'SlimGeneral.C("input root filename", "output root name","0 (or 1)")'
```

OpticsMatrix
1. create a virtual python environment (for the first time):
```
source setup.csh
```
2. Second time to retrieve the python virtual environment
```
source venv/bin/activate.csh
source sourceme.csh
```
3. Run the optics map script:
```
python3 optics_matrix_prototype.py
``` 

