#!/usr/bin/env python3

from subprocess import check_output
import pandas as pd
import matplotlib.pyplot as plt
from random import choice

begin = 1000000
end =   50000000

def gettime(args):
    out = str(check_output(args, shell=True))
    return float(out.split("Tiempo: ")[1].split()[0])

def get_dataframe():
    data_series = list(range(begin, end + 1, begin))
    time_data = pd.DataFrame(columns=['Criba','Destructivo Paralelo', 'Destructivo Secuencial'],
                             index=data_series)

    for i in data_series:
        print("Computing for i = {0}".format(i))
        destructivo_p   = gettime("bin/list -out=off {0}".format(i))
        destructivo_s   = gettime("bin/list -out=off -seq {0}".format(i))
        criba           = gettime("bin/eratosthenes -nowrite {0}".format(i))
        time_data.ix[i] = [criba, destructivo_p, destructivo_s]

    print("\n")

    return time_data

def plot(time_data):
    plt.figure()
    style = choice(plt.style.available)
    print("Usando el estilo de gráfica {0}\n".format(style))
    plt.style.use(style)
    time_data.plot()
    plt.savefig('time_compare.png')

if __name__ == "__main__":
    time_data = get_dataframe()
    plot(time_data)
    print(time_data)
