# a class to handle the spi module

import numpy
import random
from . bitfield_struct import bitfield_struct
from . bitfield_map import bitfield_map

class spimod(bitfield_struct) :
    
    def __init__(self) :
        self.dread = numpy.uint16(0)
        self.bfmap = bitfield_map

    def write_reg(self, address, data) :
        print(f"wrote address 0x{address:04X}  ,  0x{data:04X}")
        
    def read_reg(self, address) :
        self.dread = random.randint(0x0, 0xFFFF)
        print(f"read address 0x{address:04X}  ,  0x{self.dread:04X}")
        return self.dread

    def print_bf(self, bf) :
        if bf in self.bfmap :
            bf.print_bf()
    
    def writeb(self, bf_name, val) :
        idx = 0
        for idx in range(0, len(self.bfmap)) :
            if bf_name == self.bfmap[idx].name_bitfield :
                break
        current = self.read_reg(self.bfmap[idx].address)
        width1s = numpy.uint16((2**self.bfmap[idx].bit_width) - 1)
        mask0s = numpy.uint16((width1s << self.bfmap[idx].bit_begin))
        print(f"{numpy.base_repr(mask0s, base=2)}")
