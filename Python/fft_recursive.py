import numpy as np
from scipy.fft import fft as true_fft

# Python prototype fft algorithm
def fft(sequence):
    # Case that the sequence only contains one point
    length = len(sequence)
    if length == 1:
        return sequence
    elif length%2 == 1:
        raise ValueError("Length of sequence must be 2^n")
    else:
        # Create subsequences and combine
        even = sequence[::2]
        odd = sequence[1::2]
        even_dft = fft(even)
        odd_dft = fft(odd)
        output = np.zeros([length], dtype="complex128")
        l2 = int(length/2)
        for i in range(l2):
            output[i] = even_dft[i] + np.exp(-2j * np.pi * i / length) * odd_dft[i]
            output[i + l2] = even_dft[i] - np.exp(-2j * np.pi * i / length) * odd_dft[i]
        return output

if __name__ == "__main__":
    length = 2**2
    x_vals = np.sin(np.linspace(0, 2*np.pi, length))
    true_dft = true_fft(x_vals)
    out_dft = fft(x_vals)
    if np.allclose(true_dft, out_dft, 1e-5):
        print("Works")
    else:
        print("Fail")