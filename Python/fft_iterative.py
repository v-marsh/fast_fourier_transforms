from multiprocessing.sharedctypes import Value
import numpy as np
from scipy.fft import fft


def getomega(k, n):
    return np.exp(-2j * np.pi * k / n)


def getomega2(n):
    halflen = int(n / 2)
    k_vals = np.arange(0, halflen, 1)
    omega = np.exp(-2j * np.pi * k_vals / n)
    return omega

def bitreverse2(a, bitlen):
    bits = bin(a).split("0b")[-1]
    bits = bits.rjust(bitlen, "0")[::-1]
    bits = "0b" + bits
    return int(bits, 2)



def iterative_fft(array):
    """
    Compute the fft on an array in place. Output will be bit reversed.
    """
    probsize = int(array.shape[0])
    prosize_static = probsize
    n_runs = 1
    bitlen = int(np.log2(probsize))
    nsub = 1
    while probsize > 1:
        halfsize = int(probsize / 2)
        for n in range(n_runs):
            start = 0
            stop = start + halfsize
            for i in range(start, stop):
                omega = getomega(nsub * i, prosize_static)
                temp = array[i]
                array[i] = temp + array[i + halfsize]
                array[i + halfsize] = (temp - array[i + halfsize]) * omega
            start = start + halfsize
        probsize = int(probsize / 2)
        nsub = nsub * 2
        n_runs += 1
    temparr = np.zeros([array.shape[0]], dtype="complex128")
    for i in range(array.shape[0]):
        n = bitreverse2(i, bitlen)
        temparr[n] = array[i]
    array = temparr
    return array


def iterative_fft2(array):
    n_subproblems = 1
    subprobsize = len(array)
    arraylen = subprobsize
    omega = getomega2(arraylen)
    while subprobsize > 1:
        halfsize = int(subprobsize / 2)
        for k in range(0, n_subproblems):
            start = k * subprobsize
            end = start + halfsize
            n_omega = 0
            for i in range(start, end):
                omega_current = omega[n_omega]
                temp = array[i]
                array[i] = temp + array[i + halfsize]
                array[i + halfsize] = (temp - array[i + halfsize]) * omega_current
                n_omega += n_subproblems
        n_subproblems *= 2
        subprobsize = halfsize
    temparr = np.zeros([array.shape[0]], dtype="complex128")
    bitlen = int(np.log2(arraylen))
    for i in range(array.shape[0]):
        n = bitreverse2(i, bitlen)
        temparr[n] = array[i]
    array = temparr
    return array

if __name__ == "__main__":
    x_simple = np.linspace(0, 15, 16, dtype="complex128")
    fft_true = fft(x_simple)
    fft_iterative = iterative_fft2(x_simple)
    if np.allclose(fft_true, fft_iterative, 1e-5):
        print("success")
    else:
        print("fail")
    
    for i in range(fft_true.__len__()):
        print(f"{np.real(fft_true[i])}, ", end="")
