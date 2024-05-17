#!/bin/bash

particle=alpha
energy=200
seed=100
for ((i=0; i<=20; i=i+1))
do
  A=`awk 'BEGIN{printf '$energy'+500*'$i'}'`
  seed=`expr $seed + 1`
  echo "/control/verbose 0" > run-$particle-$A.in
  echo "/run/verbose 0" >> run-$particle-$A.in
  echo "/event/verbose 0" >> run-$particle-$A.in
  echo "/tracking/verbose 0" >> run-$particle-$A.in
  echo "/nEXO/det/checkOverlap true" >> run-$particle-$A.in
  echo "/generator/setGenerator gun" >> run-$particle-$A.in
  echo "/run/initialize" >> run-$particle-$A.in
  echo "/rootfile/fileName /nfs/slac/g/exo_data4/users/caogf/nEXO/validateNESTwithDiffG4/g410/$particle/$particle-$A" >> run-$particle-$A.in
  echo "/gun/particle $particle" >> run-$particle-$A.in
  echo "/gun/energy $A keV" >> run-$particle-$A.in
  echo "/run/beamOn 10000" >> run-$particle-$A.in

  echo "#!/bin/csh" > job-$particle-$A.csh
  echo "source /afs/slac.stanford.edu/u/xo/caogf/.setup_G4_10.0p01.csh" >> job-$particle-$A.csh
  echo "cd /nfs/slac/g/exo/caogf/nEXO_MC/trunk/job" >> job-$particle-$A.csh
  echo "time ~/geant4_workdir/bin/Linux-g++/nEXO -m run-$particle-$A.in -r $seed > /nfs/slac/g/exo_data4/users/caogf/nEXO/validateNESTwithDiffG4/g410/$particle/log/$particle-$A.log" >>job-$particle-$A.csh

  chmod 755 job-$particle-$A.csh
  bsub -R rhel50 -q xxl job-$particle-$A.csh
done
