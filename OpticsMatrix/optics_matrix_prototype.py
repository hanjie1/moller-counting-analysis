import math
import uproot
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from polygon_selector_demo import SelectFromCollection
from scipy.stats import gaussian_kde
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import PolynomialFeatures
from sklearn import linear_model


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

        geo = T.arrays(["gem1_x", "gem1_y","gem1_r","gem1_ph","gem1_px","gem1_py","gem1_pz","tg_th","tg_ph","tg_vz","tg_p","rate"],library="pd")  # panda dictionary
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


    def DrawScatterPlot(self,x,y):   # x, y are pandas dataframe

        xy = np.vstack([x,y])
        density = gaussian_kde(xy)(xy)

        # Sort the points by density, so that the densest points are plotted last
        idx = density.argsort()
        #print(type(x))
        newx, newy, z = x.iloc[idx], y.iloc[idx], density[idx]

        fig, ax = plt.subplots()
        ax.scatter(newx, newy, c=z, s=50)
        plt.show()

    def SelectOneHole(self, df):

        fig, ax = plt.subplots(figsize=(10,7))

        pts=ax.scatter(df.gem1_x,df.gem1_y)

        y_max=df.gem1_y.max()
        y_min=df.gem1_y.min()
        dy = (y_max-y_min)*0.1

        x_max=df.gem1_x.max()
        x_min=df.gem1_x.min()
        dx = (x_max-x_min)*0.1

        ax.set_ylim(y_min-dy, y_max+dy)
        ax.set_xlim(x_min-dx, x_max+dx)


        selector = SelectFromCollection(ax, pts)

        print("Select points in the figure by enclosing them within a polygon.")
        print("Press the 'esc' key to start a new polygon.")
        print("Try holding the 'shift' key to move all of the vertices.")
        print("Try holding the 'ctrl' key to move a single vertex.")

        plt.show()

        selector.disconnect()
        self.selected=df.loc[df.index[selector.ind]]
#        self.selected=np.take(geo, selector.ind, axis=0)   # use this when using numpy arrays

    def GenCSV(self, hole_id, filename):

        df=self.selected
        df["gem1_rp"]=(df.gem1_x*df.gem1_px+df.gem1_y*df.gem1_py)/(df.gem1_r*df.gem1_pz)       #  gem 1 r'
        df["gem1_php"]=(-df.gem1_y*df.gem1_px+df.gem1_x*df.gem1_py)/(df.gem1_r*df.gem1_pz)     #  gem 1 phi'

        header=["tg_th","tg_ph","tg_vz","tg_p","gem1_r","gem1_rp","gem1_ph","gem1_php"]
        df.to_csv(filename,columns=header)

    def PolynomialRegression(self, X, y, degree):  # X is the GEM variables in numpy array, y is the target variable 

        X_train,X_test,y_train,y_test=train_test_split(X, y, test_size=0.33, random_state=42) # split the data into traning set and test set


        poly = PolynomialFeatures(degree)
        X_train_new=poly.fit_transform(X_train)   # transform columns into polynomial columns
        X_test_new=poly.fit_transform(X_test)

        #print(X_train_new)
        regression = linear_model.LinearRegression()

        model = regression.fit(X_train_new, y_train)
        y_pred = regression.predict(X_test_new)
 
        params = model.coef_
        intercept = model.intercept_

#        ax = plt.axes(projection='3d')
#        ax.scatter3D(X_test[:,[0]], X_test[:,[1]], y_test, c=y_test, cmap='Greens')
#        ax.scatter3D(X_test[:,[0]], X_test[:,[1]], y_pred, c=y_pred, cmap='Reds')
#        plt.show()

        ax = plt.axes()
        #ax.scatter(X_test[:,[1]], y_test, c=y_test, cmap='Greens')
        ax.scatter(X_test[:,[0]], y_test, cmap='Greens')
        #ax.scatter(X_test[:,[1]], y_pred, c=y_pred, cmap='Reds')
        ax.scatter(X_test[:,[0]], y_pred, cmap='Reds')
        plt.show()


        #self.TestFit(X_test,y_test,params[0],intercept)

        score = model.score(X_test_new, y_test)
        print("score:  ", score)

    def TestFit(self, X, y, params, intercept):

        x1_min=np.amin(X[:,[0]])
        x1_max=np.amax(X[:,[0]])

        x2_min=np.amin(X[:,[1]])
        x2_max=np.amax(X[:,[1]])


        print(x1_min, x1_max)
        print(x2_min, x2_max)

        print(params)

        r=np.linspace(x1_min,x1_max)
        rp=np.linspace(x2_min,x2_max)
        func = lambda x1,x2: params[0]+params[1]*x1+params[2]*x2+params[3]*x1**2+params[4]*x1*x2+params[5]*x2**2+intercept
        y_pred = [func(i1,i2) for i1,i2 in zip(r,rp)]

        plt.scatter(X[:,[0]], y, color="black")
        plt.plot(r, y_pred, color="blue", linewidth=3)

        plt.xticks(())
        plt.yticks(())

        plt.show()



if __name__=='__main__':

    optics=OPTICS()

    #optics.GenNumpyArray("C12_elastic_optics2_usc_pass3_slim.root")
    #optics.DefineSectors()
    #optics.DrawHistAllSectors()     # Draw the 2D histogram of the GEM 1 y vs. x
    #optics.DrawScatterPlot(optics.sec1.gem1_x, optics.sec1.gem1_y)   # Draw the scatter plot of a sector with density as the color
    #optics.SelectOneHole(optics.sec7)

    #hole_id=input("Hole ID: ") # give segmenration fault, apparaently different systems have a different way of taking keyboard input in python
    #hole_id="72"
    #filename="output/SieveHole_"+hole_id+".csv"
    #optics.GenCSV(hole_id, filename)

    all_file=["11","12","13","14","21","22","31","32","41","42","51","52","61","62","71","72"]
    all_df = pd.DataFrame()
    for a_file in all_file:
        file_new = "output/SieveHole_"+a_file+".csv"
        df_new=pd.read_csv(file_new)
        all_df = pd.concat([all_df,df_new],axis=0)

    #optics.DrawScatterPlot(df.gem1_rp,df.tg_th)
    df_np=all_df.to_numpy()
    #X=df.iloc[:,5:7]    # (gem_r, gem_r')
    #y=df.iloc[:,1:2]    # tg_th
    
    X=df_np[:,5:7]
    y=df_np[:,1:2]
    optics.PolynomialRegression(X, y, 2)  

#    x1_min=X.iloc[:,[0]].min()[0]
#    x1_max=X.iloc[:,[0]].max()[0]

#    x2_min=X.iloc[:,[1]].min()[0]
#    x2_max=X.iloc[:,[1]].max()[0]

#    print(x1_min, x1_max)
#    print(x2_min, x2_max)
#    print(params[0])

#    r=np.linspace(x1_min,x1_max)
#    rp=np.linspace(x2_min,x2_max)

    
    
    #ax = plt.axes(projection='3d')
    #ax.scatter3D(df.gem1_r, df.gem1_rp, df.tg_th, c=df.tg_th, cmap='Greens')
    #plt.show()
    



