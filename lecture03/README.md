# Lecture 3 - Introduction to Numpy and Matplotlib

Key functions to cover:

Numpy:

* arrays
  * one-dimensional
  * two-dimensional
  * parameters: `shape`, `size`, `dtype`, `data`
  * types
* array creation
  * `ones`
  * `zeros`
  * `arange`
  * `linspace`
  * `zeros_like`
  * `empty_like`
* matrix-like manipulations
  * `numpy.dot`
  * `numpy.linalg.inv`
  * `numpy.eye`
  * `numpy.trace`
  * `numpy.linalg.eig`
  * `diag`
  * `tril`
  * `numpy.linalg.norm`
* functions
  * difference from Python functions


Matplotlib:

* importing: `import matplotlib.pyplot as plt`
* usage in the Jupyter notebook
* `plot`
  * different plotting options
* `subplots`: `plt.figure(1); plt.subplot(211); plt.plot(...); ...`
* `semilogx`
* `semilogy`
* `contour` and `contourf`:
  ```python
  from matplotlib.mlab import bivariate_normal
  z = (bivariate_normal(X, Y, 0.1, 0.2, 1.0, 1.0)
      + 0.1 * bivariate_normal(X, Y, 1.0, 1.0, 0.0, 0.0))
  ```
* Checking out the gallery: http://matplotlib.org/gallery.html
