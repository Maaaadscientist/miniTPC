#!/bin/bash

particle=opticalphoton
energy=6.966292135
seed=100
ref=0.5
thick=0.5
length=5
distance=5
for ((i=0; i<3; i=i+1))
do
  A=`awk 'BEGIN{printf '$ref'+0.2*'$i'}'`
  for ((j=3; j<4; j=j+1))
  do
    B=`awk 'BEGIN{printf '$thick'+0.5*'$j'}'`
    for ((k=1; k<2; k=k+1))
    do
      C=`awk 'BEGIN{printf '$length'+5*'$k'}'`
      for ((m=1; m<2; m=m+1))
      do
        D=`awk 'BEGIN{printf '$distance'+5*'$m'}'`
        for ((n=0; n<10; n=n+1))
        do
          seed=`expr $seed + 1`
          echo "/control/verbose 0" > run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/run/verbose 0" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/event/verbose 0" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/tracking/verbose 0" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/tpcLowerRadius 650 mm" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/checkOverlap false" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/wwDistance $D mm" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/fieldRingRef $A" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/cathodeRef $A" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/bulgeRef $A" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/anodeRef 0.5" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/activeSiPMPadFrac 0.8" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/fieldRingLength $C mm" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/fieldRingThick $B mm" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/ringArrangeID 2" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/ringSideDistance 30.85 mm" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/nEXO/det/radialRingDistance 6 mm" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/generator/setGenerator gps" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/run/initialize" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/rootfile/fileName /nfs/slac/g/exo_data4/users/caogf/nEXO/photonCollection/g410/tubeTPC_tubeSiPM_tubeFieldRing_SiRefIndex0.8/run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/gps/pos/type Volume" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/gps/pos/shape Cylinder" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/gps/pos/centre 0 0 0 cm" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/gps/pos/halfz 200. cm" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/gps/pos/radius 200. cm" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/gps/pos/rot1 0 0 1" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/gps/pos/rot2 0 1 0" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/gps/pos/confine InactiveLXe" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/gps/ang/type iso" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/gps/energy 6.966292135 eV" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/gps/particle opticalphoton" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
          echo "/run/beamOn 100000" >> run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in

          echo "#!/bin/csh" > job-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.csh
          echo "source /afs/slac.stanford.edu/u/xo/caogf/.setup_G4_10.0p01_64.csh" >> job-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.csh
          echo "cd /nfs/slac/g/exo/caogf/nEXO_MC/trunk/job" >> job-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.csh
          echo "time ~/geant4_workdir/bin/Linux-g++/nEXO -m run-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.in -r $seed > /nfs/slac/g/exo_data4/users/caogf/nEXO/photonCollection/g410/log/job-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.log" >>job-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.csh

          chmod 755 job-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.csh
          bsub -R rhel60 -q xxl job-RingRef$A-Cathode$A-Thick$B-Length$C-Distance$D-$n.csh
        done
      done
    done
  done
done
