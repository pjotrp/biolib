
import sys

sys.path += ['../staden_io_lib']
print sys.path

import biolib.staden_io_lib as io_lib

datadir = '../../../../test/data/trace'
procsrffn = datadir+'/abi3700-ztr/1dJ671C13-2a01.q1c.ztr'
print io_lib.TT_ANY

result = io_lib.read_reading(procsrffn,io_lib.TT_ANY)
print result.format
print result.NBases
print result.base

print result
sys.exit(0)
