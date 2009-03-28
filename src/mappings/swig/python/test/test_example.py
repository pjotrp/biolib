
import sys

sys.path += ['../example']
print sys.path

import biolib.example as example

result = example.my_mod(7,3)
print result
sys.exit(0)
