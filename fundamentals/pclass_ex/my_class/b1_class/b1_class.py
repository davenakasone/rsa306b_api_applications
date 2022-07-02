"""
    first class in the base
"""

class b1_class :
    CLASS_ID = "base class #1"    # an attribute of the class, common to all instances

    def __init__(self, name) :
        self.name = name
    
    def b1_fun1 (self, num_in) :
        return num_in + 1


########~~~~~~~~END>  b1_class.py

