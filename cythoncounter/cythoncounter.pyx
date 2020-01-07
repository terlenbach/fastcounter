cdef class Counter:
    cdef readonly int value

    def __init__(self, start=0):
        self.value = start
    
    def increment(self):
        self.value += 1