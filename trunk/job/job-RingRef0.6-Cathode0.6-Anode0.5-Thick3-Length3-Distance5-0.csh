#!/bin/csh
source /afs/slac.stanford.edu/u/xo/caogf/.setup_nEXO_MC.csh
cd /nfs/slac/g/exo/caogf/nEXO_MC_Lvpin/trunk/job
time ../../build/nEXO -m run-RingRef0.6-Cathode0.6-Anode0.5-Thick3-Length3-Distance5-0.in -r 100078 > /nfs/slac/g/exo_data4/users/caogf/sTPC/photonCollection/log/job-RingRef0.6-Cathode0.6-Anode0.5-Thick3-Length3-Distance5-0.log
