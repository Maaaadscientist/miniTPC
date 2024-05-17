#!/bin/csh
source /afs/slac.stanford.edu/u/xo/caogf/.setup_nEXO_MC.csh
cd /nfs/slac/g/exo/caogf/nEXO_MC_Lvpin/trunk/job
time ../../build/nEXO -m run-RingRef0.7-Cathode0.7-Anode0.5-Thick3-Length3-Distance6-0.in -r 100160 > /nfs/slac/g/exo_data4/users/caogf/sTPC/photonCollection/log/job-RingRef0.7-Cathode0.7-Anode0.5-Thick3-Length3-Distance6-0.log