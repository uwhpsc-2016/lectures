import numpy
import matplotlib.pyplot as plt

from numpy import exp, sin, cos, pi, sqrt
from scipy.special import erf
from scipy.integrate import trapz

@numpy.vectorize
def integrand(x, beta=10):
    return exp(-beta**2*x**2) + sin(x)

def integral(x, beta=10):
    return sqrt(pi)/(2*beta) * erf(beta*x) - cos(x)

def plot_integrand():
    x = numpy.linspace(-2,4,256)
    f = integrand(x)

    # plot
    plt.plot(x,f,'b', linewidth=2)
    plt.plot(x, numpy.zeros_like(x), 'k')
    plt.grid(True)
    plt.show()

def plot_equidistant():
    xfine = numpy.linspace(-2,4,256)
    ffine = integrand(xfine)

    x = numpy.linspace(-2,4,64)
    f = integrand(x)
    I_trap = trapz(f,x)
    I_actual = integral(4) - integral(-2)
    error = abs(I_trap - I_actual)

    # plot
    plt.plot(x, f, 'ro', markersize=8)
    plt.plot(xfine, ffine, 'b', linewidth=2)
    plt.plot(x, numpy.zeros_like(x), 'k')
    plt.grid(True)
    plt.title('Trapezoidal Error = %f'%(error))
    plt.show()

if __name__ == '__main__':
    #plot_integrand()
    plot_equidistant()
