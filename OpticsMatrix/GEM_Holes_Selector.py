#import ROOT
import uproot
import numpy as np
import matplotlib.pyplot as plt
from polygon_selector_demo import SelectFromCollection


"""
  GenNumpyArray()
  read the slim root file, then generate a numpy array

  input: root filename
  return: numpy array in the format:

	target x, target y, target theta, target phi, main r, main phi, main r', main phi'  
"""

def GenNumpyArray(filename):

    #df = ROOT.RDataFrame("newT", "../SlimRootfiles/rootfiles/"+filename) 
    #npy_arr = df.AsNumpy(columns=["main_x","main_y"])     
    #npy_arr = df.AsNumpy()     

    file = uproot.open("../SlimRootfiles/rootfiles/"+filename)
    T=file["newT"]

    #print(uproot.__version__)
    #geo = T.arrays(["main_x", "main_y"])

    fig,ax = plt.subplots(figsize =(10, 7))
    #plt.hist2d(npy_arr["main_x"], npy_arr["main_y"])
    pts=ax.scatter(T["main_x"].array(), T["main_y"].array())
    #ax.title("Simple 2D Histogram")
  
    selector = SelectFromCollection(ax, pts)

    print("Select points in the figure by enclosing them within a polygon.")
    print("Press the 'esc' key to start a new polygon.")
    print("Try holding the 'shift' key to move all of the vertices.")
    print("Try holding the 'ctrl' key to move a single vertex.")

    plt.show()

    selector.disconnect()

    # After figure is closed print the coordinates of the selected points
    print('\nSelected points:')
    print(selector.xys[selector.ind])


idx = ((my_arr[:, 2:][:, None] == sel[None, :]).all(axis=2)).any(axis=1)
coords = my_arr[idx, :2]    
    

if __name__=='__main__':

    GenNumpyArray("C12_elastic_optics2_usc_pass3_slim.root")







