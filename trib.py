# Author: Jaskirat Singh Maskeen
store = {}

def tribonacci(n: int) -> int:
    """Return the nth tribonacci number"""
    if n in store:
        return store[n]
    if n == 0:
        return 0
    if n in [1, 2]:
        return 1
    store[n] = tribonacci(n - 1) \
        + tribonacci(n - 2) \
        + tribonacci(n - 3)
        
    return store[n]

print(tribonacci(12))
