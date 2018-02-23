import subprocess as sp
from random import sample
import pandas as pd
import numpy as np
import matplotlib as plt
from multiprocessing import Pool

# Parameters
boardSize = ['20', '10']
playingTypes = ['Random', 'Smart', 'Smarter', 'Smartest']
n = 30
fileLocation = '../cmake-build-debug/KIPO_1_Tetris.exe'

# Functions
def runAnalysis(args):
    output = sp.check_output([fileLocation, args[0], boardSize[0], boardSize[1], args[1]], universal_newlines=True)
    print('#', end='', flush=True)
    return {
        'type': args[0],
        'seed': args[1],
        'result': int((output.splitlines()[3]).split(' ', 1)[0])
    }

if __name__ == '__main__':
    # Start
    print('**This script performs a comparison of ' + str(len(playingTypes)) + ' different AIs playing Tetris.**')
    print('**The results are the number of turns per game.**')

    # n random seeds
    seeds = [str(x) for x in sample(range(100000, 100000000), n)]

    # Results storage
    results = np.empty((n, len(playingTypes)))

    # Play Tetris
    pool = Pool()
    inputs = [[type, seed] for type in playingTypes for seed in seeds]

    print()
    print('Analysing - ', end='', flush=True)
    for output in pool.map(runAnalysis, inputs):
        results[seeds.index(output['seed'])][playingTypes.index(output['type'])] = output['result']
    print(' - Done!')

    # Calculate average
    result = [sum(x) for x in zip(*results)]
    result[:] = [x/len(seeds) for x in result]

    # Display results
    print()
    print("For n = " + str(n))
    for x in playingTypes:
        print(x + ': ' + str(result[playingTypes.index(x)]))

    pd.DataFrame(results, columns=playingTypes).plot.box()
    plt.pyplot.show()
