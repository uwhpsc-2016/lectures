"""stackexample.py

A Python script with some nested functions. Use to practice navigating the
stack with pdb.
"""

def foo(x):
    print 'Entered foo: x = %d'%(x)
    y = x**2
    z = bar(x)
    result = y + z
    return result


def bar(x):
    print 'Entered bar: x = %d'%(x)
    u = 2*x
    v = foobar(u)
    value = u + v
    return value


def foobar(x):
    print 'Entered foobar: x = %d'%(x)
    result = x + 1
    return result


if __name__ == '__main__':
    print 'Starting script...'

    x = 2
    result = foo(x)

    print 'result = %d'%(result)
    print '...exiting. Goodbye!'
