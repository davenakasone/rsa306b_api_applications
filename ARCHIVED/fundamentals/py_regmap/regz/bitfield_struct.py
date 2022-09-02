# manage the most fundamental unit of the memory map (bit field in the register)


class bitfield_struct() :
    REGISTER_SIZE = 16
    MIN_UINT16 = 0x0
    MAX_UINT16 = 0xFFFF

    def __init__(self, reg_name, adr, bf_name, bf_stop, bf_start, bf_init, notes) :
        self.address = adr
        
        self.name_register = reg_name
        self.name_bitfield = bf_name
        
        self.bit_begin = bf_start
        self.bit_end = bf_stop
        self.bit_width = self.bit_end - self.bit_begin + 1
        
        self.value_reset = bf_init
        self.notes = notes
    
    def __eq__(self, other) :
        result_adr = self.address == other.address
        result_start = self.bit_begin == other.bit_begin
        result_stop = self.bit_end == other.bit_end
        result = result_adr & result_start & result_stop
        return result
    
    def print_bf(self) :
        print(f"register:  {self.name_register}  ,  bitfield:  {self.name_bitfield}")
        print(f"address:  0x{self.address:04X}  ,  {self.address:d}")

########~~~~~~~~END>  bitfield_struct.py
