#!/usr/bin/env python3

from subprocess import check_output
import pandas as pd
import matplotlib.pyplot as plt
from random import choice
import argparse

parser = argparse.ArgumentParser(usage="%(prog)s [options]",
                    description='Ejecuta un benchmark con distintas versiones del algoritmo.')
parser.add_argument('--begin', dest='begin', type=int, default=1000000,
                    help="Número desde el que empezar el test")
parser.add_argument('--end', dest='end', type=int, default=50000000,
                    help="Número desde el que acabar el test")
parser.add_argument('--step', dest='step', type=int, default=0,
                    help="Número por el que incrementar el test")
parser.add_argument('--style', dest='style', type=str, default=choice(plt.style.available),
                    help="Estilo de la gráfica final")

def gettime(args):
    out = str(check_output(args, shell=True))
    return float(out.split("Tiempo: ")[1].split()[0])

def get_dataframe(begin, end, step):
    perf_step = step if step != 0 else begin
    data_series = list(range(begin, end + 1, perf_step))
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

def plot(time_data, style):
    plt.figure()
    print("Usando el estilo de gráfica {0}\n".format(style))
    plt.style.use(style)
    time_data.plot()
    plt.savefig('time_compare.png')

if __name__ == "__main__":
    ns = parser.parse_args()
    time_data = get_dataframe(ns.begin, ns.end, ns.step)
    plot(time_data, ns.style)
    print(time_data)
