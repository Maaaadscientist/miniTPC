#!/bin/bash

particle=opticalphoton
energy=6.966292135
seed=200000
ref=0.9
anodeRef=0.0
length=5
distance=1
for ((i=0; i<3; i=i+1))
do
  A=`awk 'BEGIN{printf '$ref'+0.05*'$i'}'`
  for ((j=0; j<2; j=j+1))
  do
    B=`awk 'BEGIN{printf '$anodeRef'+0.5*'$j'}'`
    for ((k=0; k<1; k=k+1))
    do
      C=`awk 'BEGIN{printf '$length'+5*'$k'}'`
      for ((m=0; m<3; m=m+1))
      do
        D=`awk 'BEGIN{printf '$distance'+2*'$m'}'`
        for ((n=0; n<5; n=n+1))
        do
          seed=`expr $seed + 1`
          echo "/control/verbose 0" > run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/run/verbose 0" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/event/verbose 0" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/tracking/verbose 0" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/tpcLowerRadius 650 mm" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/checkOverlap false" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/wwDistance 20 mm" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/fieldRingRef $A" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/cathodeRef 0.9" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/bulgeRef 0.9" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/anodeRef $B" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/activeSiPMPadFrac 0.8" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/fieldRingLength 10 mm" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/fieldRingThick 4 mm" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/ringArrangeID 2" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/ringSideDistance 40.85 mm" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/nEXO/det/radialRingDistance $D mm" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/generator/setGenerator gps" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/run/initialize" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/rootfile/fileName /nfs/slac/g/exo_data4/users/caogf/nEXO/photonCollection/g410/lotusTPC_endcapSiPM_tubeFieldRing_ringSide40.85/run-RoundedRing-DiffuseRef-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/gps/pos/type Volume" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/gps/pos/shape Cylinder" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/gps/pos/centre 0 0 0 cm" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/gps/pos/halfz 200. cm" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/gps/pos/radius 200. cm" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/gps/pos/rot1 0 0 1" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/gps/pos/rot2 0 1 0" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/gps/pos/confine InactiveLXe" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/gps/ang/type iso" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/gps/energy 6.966292135 eV" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/gps/particle opticalphoton" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in
          echo "/run/beamOn 200000" >> run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in

          echo "#!/bin/csh" > job-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.csh
          echo "source /afs/slac.stanford.edu/u/xo/caogf/.setup_G4_10.0p01_64.csh" >> job-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.csh
          echo "cd /nfs/slac/g/exo/caogf/nEXO_MC/trunk/job" >> job-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.csh
          echo "time ~/geant4_workdir/bin/Linux-g++/nEXO -m run-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.in -r $seed > /nfs/slac/g/exo_data4/users/caogf/nEXO/photonCollection/g410/log/job-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.log" >>job-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.csh

          chmod 755 job-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.csh
          bsub -R rhel60 -q xxl job-Reflector$A-Cathode0.9-Anode$B-WireD125-Distance$D-$n.csh
        done
      done
    done
  done
done
