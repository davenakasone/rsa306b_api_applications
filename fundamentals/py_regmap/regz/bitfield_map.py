from . bitfield_struct import bitfield_struct

bitfield_map = []
bitfield_map.append(bitfield_struct(reg_name="who_i_be", adr=0x0, bf_name="response", bf_stop=0, bf_start=0, bf_init=0x6, notes="who am i response, chip ID"))
bitfield_map.append(bitfield_struct(reg_name="uart", adr=0x1, bf_name="transmit", bf_stop=3, bf_start=3, bf_init=0x123, notes="set high when transmitting"))
bitfield_map.append(bitfield_struct(reg_name="uart", adr=0x1, bf_name="receive", bf_stop=2, bf_start=2, bf_init=0x456, notes="set high when receiving"))
bitfield_map.append(bitfield_struct(reg_name="interupt", adr=0x69, bf_name="user interrupts", bf_stop=14, bf_start=10, bf_init=0x789, notes="indicates an interupt happened"))
bitfield_map.append(bitfield_struct(reg_name="GPIO", adr=0x33, bf_name="port B", bf_stop=2, bf_start=8, bf_init=0xABC, notes="GPIO for port B"))
