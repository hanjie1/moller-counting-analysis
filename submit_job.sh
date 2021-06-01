#!/bin/bash
#
#$ -cwd
#$ -j y
#$ -S /bin/bash
ls /share/library/
source /home/hanjie/moller/remoll/bin/remoll.sh
source /home/hanjie/moller/optics_analysis/bin/GenRoot.sh
export PATH="/share/library":${PATH}
export LD_LIBRARY_PATH="/share/library/":${LD_LIBRARY_PATH}
source /share/apps/geant4/geant4.10.04.p02/bin/geant4.sh
./build/GenRoot $1 $2
