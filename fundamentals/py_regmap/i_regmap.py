# interactive driver for the register map class

from regz.spimod import spimod
spi = spimod()

def wr(adr, dat) :
    spi.write_reg(adr, dat)

def rr(adr) :
    spi.read_reg(adr)

def wrb(val=0x1111, idx=3) :
    spi.writeb(val, spi.bfmap[idx].name_bitfield)

########~~~~~~~~END>  i_regmap.py