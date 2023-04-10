#!/bin/bash

particle=opticalphoton
energy=6.966292135
seed=100000
ref=0.05
#ref=0
thick=1
length=5
distance=5
for ((i=4; i<5; i=i+1))
do
  A=`awk 'BEGIN{printf '$ref'+0.2*'$i'}'`
  for ((r=4; r<5; r=r+1))
  do
    R=`awk 'BEGIN{printf '$ref'+0.2*'$r'}'`
    for ((j=3; j<4; j=j+1))
    do
      B=`awk 'BEGIN{printf '$thick'+1.0*'$j'}'`
      for ((k=1; k<2; k=k+1))
      do
        C=`awk 'BEGIN{printf '$length'+5*'$k'}'`
        for ((m=3; m<4; m=m+1))
        do
          D=`awk 'BEGIN{printf '$distance'+5*'$m'}'`
          for ((n=0; n<100; n=n+1))
          do
            seed=`expr $seed + 1`
            echo "/control/verbose 0" > run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/run/verbose 0" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/event/verbose 0" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/tracking/verbose 0" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/det/checkOverlap false" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/wwDistance $D mm" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/fieldRingRef $R" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/cathodeRef $A" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/bulgeRef $A" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/anodeRef 0.5" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/fieldRingLength $C mm" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/fieldRingThick $B mm" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/ringArrangeID 2" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/generator/setGenerator gps" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/run/initialize" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            #echo "/analysis/setOutputROOTFileName /nfs/slac/g/exo_data4/users/caogf/nEXO/photonCollection/g410/nEXO_10534_15_12_24/run-VesselRefCuIndex-RingRef$R-CathodeRef$A-AnodeRef0.5-Thick$B-Length$C-Pitch$D-$n.root" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            #echo "/analysis/setOutputROOTFileName /nfs/slac/g/exo_data4/users/caogf/nEXO/photonCollection/g410/nEXO_10534_15_12_24/run-VesselRefCuIndex-RingRef$R-CathodeRef$A-AnodeRef0.5-Thick$B-Length$C-Pitch$D-$n.root" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/analysis/setOutputROOTFileName /nfs/slac/g/exo_data4/users/caogf/nEXO/MCData/gamma/gamma-2.614MeV-$n.root" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/analysis/setOutputROOTTreeName tree" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/type Volume" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/shape Cylinder" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/centre 0 0 0 cm" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/halfz 200. cm" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/radius 200. cm" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/rot1 0 0 1" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/rot2 0 1 0" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/confine /nEXO/TPCInternals/LXe/ActiveRegion" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/ang/type iso" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/energy 2.614 MeV" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/particle gamma" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in
            echo "/run/beamOn 50" >> run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in

            echo "#!/bin/csh" > job-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.csh
            echo "source /afs/slac.stanford.edu/u/xo/caogf/.setup_nEXO_MC.csh" >> job-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.csh
            echo "cd /nfs/slac/g/exo/caogf/nEXO_MC/trunk/job" >> job-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.csh
            echo "time ../../build/nEXO -m run-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.in -r $seed > /nfs/slac/g/exo_data4/users/caogf/nEXO/photonCollection/g410/log/job-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.log" >>job-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.csh
#
            chmod 755 job-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.csh
            bsub -W 7200 -R rhel60 -q long ./job-RingRef$R-Cathode$A-Thick$B-Length$C-Distance$D-$n.csh
          done
        done
      done
    done
  done
done
