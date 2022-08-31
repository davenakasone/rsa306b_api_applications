"""
    this class is derived from base classes
    see if inheritance or composition is better
"""

import sys
sys.path.insert(0, '/home/unlv/Desktop/rsa306b_api_applications/fundamentals/pclass_ex/my_class')

from b1_class.b1_class import b1_class

class my_class :
    CLASS_ID = "derived class, by composition"

    def __init__(self, name) :
        self.name = name
        self.b1 = b1_class("comp-ed")


####~~~~


    def mc_print(self) :
        print("this is my class")


########~~~~~~~~END>  my_class.py
