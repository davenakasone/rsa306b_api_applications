"""
    drive the sub directories
    composition is good, inheritance is bad (for your use case)
"""

from my_class.my_class import my_class

obj = my_class("potatoe")
x = 11
y = obj.b1.b1_fun1(x)

obj.mc_print()
print(f"x= {x}  , y= {y}")
print(f"{obj.CLASS_ID}  ,  {obj.name}")
print(f"{obj.b1.CLASS_ID}  ,  {obj.b1.name}")



########~~~~~~~~END>  tester.py
