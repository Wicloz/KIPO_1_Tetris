import subprocess as sp
from random import sample
import pandas as pd
import numpy as np
import matplotlib as plt


print("**This script performs comparison of 3 different AI playing styles of tetris.**\n**The results are the average number of turns per game**")

# Parameters
boardSize = ['15', '10']
playingTypes = ['Random', 'Smart', 'Smarter']
n = 20
fileLocation = '../cmake-build-debug/KIPO_1_Tetris'

# n random seeds
seeds = [str(x) for x in sample(range(100000, 100000000), n)]

# Results storage {random, smart, smarter}
results = np.empty((n, len(playingTypes)))

# Play tetris
for type in playingTypes:
    for seed in seeds:
        output = sp.check_output([fileLocation, type, boardSize[0], boardSize[1], seed], universal_newlines=True)
        results[seeds.index(seed)][playingTypes.index(type)] = int((output.splitlines()[3]).split(' ', 1)[0])

# Calculate avarage
result = [sum(x) for x in zip(*results)]
result[:] = [x/len(seeds) for x in result]

# Display results
print("For n = " + str(n))
print()
print("Random: " + str(result[0]))
print("Smart: " + str(result[1]))
print("Smarter: " + str(result[2]))

pd.DataFrame(results, columns=playingTypes).plot.box()

plt.pyplot.show()
