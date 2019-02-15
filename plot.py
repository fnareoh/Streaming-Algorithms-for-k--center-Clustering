import cartopy.crs as ccrs
import matplotlib.pyplot as plt
import numpy as np

def line_with_unix_to_point(line):
    line = line.split()
    return np.array([float(line[1]), float(line[2])])

def read_dataset(filepath):
    file = open(filepath, "r")
    lines = np.array(file.readlines())
    points = np.array([line_with_unix_to_point(line) for line in lines])
    return (points[:, 0], points[:, 1])

ax = plt.axes(projection=ccrs.PlateCarree())
ax.set_global()

ax.gridlines()
ax.coastlines()

x,y = read_dataset("../dataset/twitter_1000000.txt")
plt.scatter(x,y,transform=ccrs.PlateCarree(), s=0.05)

input_r = 4.66063
r = input_r*6371
c_x,c_y = read_dataset("result.txt")
for i in range(len(c_x)):
    scat = ax.scatter(c_x[i], c_y[i], r, transform=ccrs.PlateCarree(), lw=0.5,
                  edgecolors = 'r', facecolors='None', zorder=10)

plt.savefig('test.pdf')
plt.show()
