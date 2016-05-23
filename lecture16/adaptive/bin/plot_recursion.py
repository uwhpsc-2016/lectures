import numpy
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

from numpy import exp, sin, cos, pi, sqrt
from scipy.special import erf
from scipy.integrate import trapz

#
# csv - Python module for easily reading csv files
#
import csv


@numpy.vectorize
def integrand(x, beta=10):
    return exp(-beta**2*x**2) + sin(x)

def integral(x, beta=10):
    return sqrt(pi)/(2*beta) * erf(beta*x) - cos(x)

def plot_integrand(ax):
    x = numpy.linspace(-2,4,256)
    f = integrand(x)

    points = set()
    with open('diagnostics.csv') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            points.add(numpy.double(row['a']))
            points.add(numpy.double(row['b']))

    points = list(points)
    fpoints = integrand(points)
    foo = numpy.zeros_like(points)

    ax.plot(x,f,'b', linewidth=2)
    ax.plot(points, fpoints, 'ro', markersize=8)
    ax.plot(points, foo, 'k|', markersize=8)
    ax.plot(x, numpy.zeros_like(x), 'k')
    ax.grid(True)
    ax.margins(0.05)

def plot_diagnostics(ax):
    z = 0
    with open('diagnostics.csv') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            a = row['a']
            b = row['b']
            plt.plot([a,b], [z,z], 'r', linewidth=2)
            z -= 0.1

    ax.grid(True)
    ax.get_yaxis().set_visible(False)
    ax.margins(0.05)
    ax.set_ylabel("Adaptive Intervals")


if __name__ == '__main__':
    fig = plt.figure(figsize=(8,10))
    ax1 = fig.add_subplot(211)
    ax2 = fig.add_subplot(212)

    plot_integrand(ax1)
    plot_diagnostics(ax2)

    ax1.set_title("Adaptive Quadrature")
    fig.savefig('bin/serial.png')
