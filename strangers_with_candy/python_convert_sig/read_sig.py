"""
https://forum.tek.com/viewtopic.php?t=139822

You should not need any filtering as long as the signal of interest is the only one in the bandwidth, 
and is reasonably "high-level" (within 30 dBm of the Ref Level). 
If those are not true, then you should apply a filter around your signal to reject other interfering signals, 
or reduce the noise contribution to get an accurate result. 
If you apply a filter, it should have unity gain (0 dB) in the passband so it doesn't change the level of your signal.

You also need to scale the IQ samples by the "DataScale" factor given in the .siqh file to 
convert them to "volts into 50 ohms" values. 
Then you can calculate the instantaneous power of each complex sample point, and find the average power.
"""

import matplotlib.pyplot as plt
import numpy as np

# open file with read permissions
with open('iq_stream_test.siq', 'rb') as f:
    # if siq file, skip header
    if f.name[-1] == 'q':
        f.seek(1024)
    # read in data as int16
    d = np.frombuffer(f.read(), dtype=np.int16)
# separate i and q from interleaved data
i = d[0:-1:2]
q = d[1:-1:2]
    
# plot the first 10k samples
plt.plot(i[:10000])
plt.plot(q[:10000])
plt.show()