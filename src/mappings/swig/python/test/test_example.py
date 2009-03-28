
import sys

sys.path += ['../example']
print sys.path

import example

result = example.my_mod(7,3)
print result
sys.exit(0)
