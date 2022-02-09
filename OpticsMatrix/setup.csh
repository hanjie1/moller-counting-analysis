# python version needs to be above 3.6
set MY_DIR=`pwd`
set NEW_DIR=`(mkdir $MY_DIR/venv)`
set ENV_DIR=$MY_DIR/venv
python3 -m venv $ENV_DIR
source $ENV_DIR/bin/activate.csh
pip3 install uproot3
pip3 install matplotlib
alias python3 $ENV_DIR/bin/python3
