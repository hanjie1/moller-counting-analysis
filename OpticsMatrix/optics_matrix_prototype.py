import math
import uproot
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from polygon_selector_demo import SelectFromCollection
from scipy.stats import gaussian_kde


class OPTICS:

    def __init__(self):
        self.orig = pd.DataFrame()        # data before cut
        self.sec1 = pd.DataFrame()        # sector1 data before cut
        self.sec2 = pd.DataFrame()        # sector2 data before cut
        self.sec3 = pd.DataFrame()        # sector3 data before cut
        self.sec4 = pd.DataFrame()        # sector4 data before cut
        self.sec5 = pd.DataFrame()        # sector5 data before cut
        self.sec6 = pd.DataFrame()        # sector6 data before cut
        self.sec7 = pd.DataFrame()        # sector7 data before cut

        self.selected = pd.DataFrame()    # data of selected holes

    def GenNumpyArray(self,filename):
        #df = ROOT.RDataFrame("newT", "../SlimRootfiles/rootfiles/"+filename) 
        #npy_arr = df.AsNumpy(columns=["main_x","main_y"])     
        #npy_arr = df.AsNumpy()     

        file = uproot.open("../SlimRootfiles/rootfiles/"+filename)
        T=file["newT"]

        geo = T.arrays(["gem1_x", "gem1_y","gem1_r","gem1_ph","gem1_px","gem1_py","gem1_pz","tg_th","tg_ph","tg_vz","tg_p"],library="pd")  # panda dictionary
        geo = geo.loc[geo["gem1_r"]>300]

        self.orig=geo

    def DefineSectors(self):
        rot_angle=0        # put the GEM rotation angle here

        angle_lo=[]
        angle_up=[]

        for i in range(7):
            angle_lo.append(math.pi/14 + i*2*math.pi/7+rot_angle)
            angle_up.append(3*math.pi/14 + i*2*math.pi/7+rot_angle)
            if angle_lo[i]>math.pi:
               angle_lo[i]=angle_lo[i]-2*math.pi;
            if angle_up[i]>math.pi:
               angle_up[i]=angle_up[i]-2*math.pi;
            
        geo=self.orig

        self.sec1=geo.loc[(geo["gem1_ph"]<=angle_up[0]) & (geo["gem1_ph"]>=angle_lo[0])]
        self.sec2=geo.loc[(geo["gem1_ph"]<=angle_up[1]) & (geo["gem1_ph"]>=angle_lo[1])]
        self.sec3=geo.loc[(geo["gem1_ph"]<=angle_up[2]) & (geo["gem1_ph"]>=angle_lo[2])]
        self.sec4=geo.loc[((geo["gem1_ph"]<=angle_up[3]) & (geo["gem1_ph"]>=-math.pi)) | ((geo["gem1_ph"]>=angle_lo[3]) & (geo["gem1_ph"]<=math.pi))]
        self.sec5=geo.loc[(geo["gem1_ph"]<=angle_up[4]) & (geo["gem1_ph"]>=angle_lo[4])]
        self.sec6=geo.loc[(geo["gem1_ph"]<=angle_up[5]) & (geo["gem1_ph"]>=angle_lo[5])]
        self.sec7=geo.loc[(geo["gem1_ph"]<=angle_up[6]) & (geo["gem1_ph"]>=angle_lo[6])]

    def DrawHistAllSectors(self):
        fig, axs = plt.subplots(2, 4, figsize=(20,10))

        #fig,ax = plt.subplots(figsize =(10, 7))
        #plt.hist2d(npy_arr["main_x"], npy_arr["main_y"])
        #pts=ax.scatter(geo["gem1_x"], geo["gem1_y"])

        axs[0,0].hist2d(self.orig.gem1_x, self.orig.gem1_y,(200,200),cmap=plt.cm.jet, cmin=1)
        #axs[0,0].set_xlim((-1000,1000))
        #axs[0,0].set_ylim((-1000,1000))
		
        axs[0,1].hist2d(self.sec1.gem1_x,self.sec1.gem1_y,(100,100),cmap=plt.cm.jet, cmin=1)
        axs[0,1].set_title('sec1')
        axs[0,2].hist2d(self.sec2.gem1_x,self.sec2.gem1_y,(100,100),cmap=plt.cm.jet, cmin=1)
        axs[0,2].set_title('sec2')
        axs[0,3].hist2d(self.sec3.gem1_x,self.sec3.gem1_y,(100,100),cmap=plt.cm.jet, cmin=1)
        axs[0,3].set_title('sec3')
        axs[1,0].hist2d(self.sec4.gem1_x,self.sec4.gem1_y,(100,100),cmap=plt.cm.jet, cmin=1)
        axs[1,0].set_title('sec4')
        axs[1,1].hist2d(self.sec5.gem1_x,self.sec5.gem1_y,(100,100),cmap=plt.cm.jet, cmin=1)
        axs[1,1].set_title('sec5')
        axs[1,2].hist2d(self.sec6.gem1_x,self.sec6.gem1_y,(100,100),cmap=plt.cm.jet, cmin=1)
        axs[1,2].set_title('sec6')
        axs[1,3].hist2d(self.sec7.gem1_x,self.sec7.gem1_y,(100,100),cmap=plt.cm.jet, cmin=1)
        axs[1,3].set_title('sec7')

        plt.show()


    def DrawScatterPlot(self,df):

        xy = np.vstack([df.gem1_x,df.gem1_y])
        density = gaussian_kde(xy)(xy)

        # Sort the points by density, so that the densest points are plotted last
        idx = density.argsort()
        x, y, z = df.iloc[idx].gem1_x, df.iloc[idx].gem1_y, density[idx]

        fig, ax = plt.subplots()
        ax.scatter(x, y, c=z, s=50)
        plt.show()



    def SelectOneHole(self, df):

        fig, ax = plt.subplots(figsize=(10,7))

        pts=ax.scatter(df.gem1_x,df.gem1_y)
        selector = SelectFromCollection(ax, pts)

        print("Select points in the figure by enclosing them within a polygon.")
        print("Press the 'esc' key to start a new polygon.")
        print("Try holding the 'shift' key to move all of the vertices.")
        print("Try holding the 'ctrl' key to move a single vertex.")

        plt.show()

        selector.disconnect()
        self.selected=df.loc[df.index[selector.ind]]
#        self.selected=np.take(geo, selector.ind, axis=0)   # use this when using numpy arrays

#    def GenCSV(self, hole_id):

        df=self.selected
        df["gem1_rp"]=(df.gem1_x*df.gem1_px+df.gem1_y*df.gem1_py)/(df.gem1_r*df.gem1_pz)       #  gem 1 r'
        df["gem1_php"]=(-df.gem1_y*df.gem1_px+df.gem1_x*df.gem1_py)/(df.gem1_r*df.gem1_pz)     #  gem 1 phi'

        hole_id="1"
        filename="output/SieveHole_"+hole_id+".csv"
        header=["tg_th","tg_ph","tg_vz","tg_p","gem1_r","gem1_rp","gem1_ph","gem1_php"]
        df.to_csv(filename,columns=header)


if __name__=='__main__':

    optics=OPTICS()

    optics.GenNumpyArray("C12_elastic_optics2_usc_pass3_slim.root")
    optics.DefineSectors()
    #optics.DrawHistAllSectors()     # Draw the 2D histogram of the GEM 1 y vs. x
    #optics.DrawScatterPlot(optics.sec1)   # Draw the scatter plot of a sector with density as the color
    optics.SelectOneHole(optics.sec1)

    #hole_id=int(input("Hole ID: "))	
    #input("Hole ID: ")	
    #optics.GenCSV(hole_id)




