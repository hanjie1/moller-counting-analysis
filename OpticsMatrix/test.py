import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import PolygonSelector
from matplotlib.path import Path

#this is the matplotlib code from their website
class SelectFromCollection:
    def __init__(self, ax, collection, alpha_other=0.3):
        self.canvas = ax.figure.canvas
        self.collection = collection
        self.alpha_other = alpha_other

        self.xys = collection.get_offsets()
        self.Npts = len(self.xys)

        self.fc = collection.get_facecolors()
        if len(self.fc) == 0:
            raise ValueError('Collection must have a facecolor')
        elif len(self.fc) == 1:
            self.fc = np.tile(self.fc, (self.Npts, 1))

        self.poly = PolygonSelector(ax, self.onselect)
        self.ind = []

    def onselect(self, verts):
        path = Path(verts)
        self.ind = np.nonzero(path.contains_points(self.xys))[0]
        self.fc[:, -1] = self.alpha_other
        self.fc[self.ind, -1] = 1
        self.collection.set_facecolors(self.fc)
        self.canvas.draw_idle()

    def disconnect(self):
        self.poly.disconnect_events()
        self.fc[:, -1] = 1
        self.collection.set_facecolors(self.fc)
        self.canvas.draw_idle()


def plot(arr): 
    fig, ax = plt.subplots()
    pts = ax.scatter(arr[:, 2], arr[:, 3])
    selector = SelectFromCollection(ax, pts)
    plt.show()

    selector.disconnect()

    print(selector.ind)
    return(selector.ind)


#random test data 
np.random.seed(123)
my_arr = np.random.choice(range(1000), (5, 4), replace=False)/100
#the first two column contain the unknown coordinates A/B
#the last two columns contain the displayed coordinates C/D 
print(my_arr)

#call the plot function
#receive the C/D coordinates as a numpy array
sel = plot(my_arr)
#print(sel)

newarr = np.take(my_arr, sel, axis=0) 
print(newarr)
#find indexes of C/D coordinates in original array
#to retrieve the corresponding A/B coordinates
#idx = ((my_arr[:, 2:][:, None] == sel[None, :]).all(axis=2)).any(axis=1)
#coords = my_arr[idx, :2]

#print(coords)

