import matplotlib.pyplot as plt
import numpy as np
import sys

print("plot.py")
print("-----------------")
if len(sys.argv) < 2:
    sys.exit("you must supply and input file")
dataFile = sys.argv[1]

data = np.genfromtxt(dataFile, delimiter=', ')
print(data)
plt.imshow(data, cmap='hot', interpolation='nearest')
plt.show()