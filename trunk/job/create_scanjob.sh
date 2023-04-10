#!/bin/bash

particle=opticalphoton
energy=6.966292135
seed=100000
ref=0.6
#ref=0
thick=1.5
length=1.5
distance=4.0
for ((i=0; i<3; i=i+1))
do
  A=`awk 'BEGIN{printf '$ref'+0.1*'$i'}'`
  for ((r=4; r<5; r=r+1))
  do
    #R=`awk 'BEGIN{printf '$ref'+0.2*'$r'}'`
    R=$A
    for ((j=0; j<4; j=j+1))
    do
      B=`awk 'BEGIN{printf '$thick'+0.5*'$j'}'`
      for ((k=0; k<4; k=k+1))
      do
        C=`awk 'BEGIN{printf '$length'+0.5*'$k'}'`
        for ((m=0; m<5; m=m+1))
        do
          D=`awk 'BEGIN{printf '$distance'+0.5*'$m'}'`
          for ((n=0; n<1; n=n+1))
          do
            seed=`expr $seed + 1`
            R=$A
            echo "/control/verbose 0" > run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/run/verbose 0" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/event/verbose 0" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/tracking/verbose 0" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            #echo "/nEXO/det/checkOverlap false" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/wwDistance $D mm" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            #echo "/nEXO/TPCInternals/fieldRingRef $R" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/fieldRingRef $A" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/cathodeRef $A" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/bulgeRef $A" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/anodeRef 0.5" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/fieldRingLength $C mm" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/fieldRingThick $B mm" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/nEXO/TPCInternals/ringArrangeID 2" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/generator/setGenerator gps" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/run/initialize" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            #echo "/analysis/setOutputROOTFileName /nfs/slac/g/exo_data4/users/caogf/nEXO/photonCollection/g410/nEXO_10534_15_12_24/run-VesselRefCuIndex-RingRef$R-CathodeRef$A-AnodeRef0.5-Thick$B-Length$C-Pitch$D-$n.root" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            #echo "/analysis/setOutputROOTFileName /nfs/slac/g/exo_data4/users/caogf/nEXO/photonCollection/g410/nEXO_10534_15_12_24/run-VesselRefCuIndex-SiPMRef0-RingRef$R-CathodeRef$A-AnodeRef0.5-Thick$B-Length$C-Pitch$D-$n.root" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/analysis/setOutputROOTFileName /nfs/slac/g/exo_data4/users/caogf/sTPC/photonCollection/run-VesselRefCuIndex-SiPMComplexR-SiO2RIIndex2-RingRef$R-CathodeRef$A-AnodeRef0.5-Thick$B-Length$C-Pitch$D-$n.root" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            #echo "/analysis/setOutputROOTFileName /nfs/slac/g/exo_data4/users/caogf/nEXO/photonCollection/g410/nEXO_10534_15_12_24/run-VesselRefCuIndex-SiliconFieldRingAndCathode-AnodeRef0.5-Thick$B-Length$C-Pitch$D-$n.root" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            #echo "/analysis/setOutputROOTFileName /nfs/slac/g/exo_data4/users/caogf/nEXO/photonCollection/g410/nEXO_10534_15_12_24/test.root" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/analysis/setOutputROOTTreeName tree" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/type Volume" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/shape Cylinder" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/centre 0 0 0 cm" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/halfz 10. cm" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/radius 10. cm" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            #echo "/gps/pos/rot1 0 0 1" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            #echo "/gps/pos/rot2 0 1 0" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/pos/confine /nEXO/TPCInternals/sTPCLXe" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/ang/type iso" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/energy 6.966292135 eV" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/gps/particle opticalphoton" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in
            echo "/run/beamOn 1000000" >> run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in

            echo "#!/bin/csh" > job-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.csh
            echo "source /afs/slac.stanford.edu/u/xo/caogf/.setup_nEXO_MC.csh" >> job-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.csh
            echo "cd /nfs/slac/g/exo/caogf/nEXO_MC_Lvpin/trunk/job" >> job-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.csh
            echo "time ../../build/nEXO -m run-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.in -r $seed > /nfs/slac/g/exo_data4/users/caogf/sTPC/photonCollection/log/job-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.log" >>job-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.csh
#
            chmod 755 job-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.csh
            bsub -W 7200 -R rhel60 -q long ./job-RingRef$R-Cathode$A-Anode0.5-Thick$B-Length$C-Distance$D-$n.csh
          done
        done
      done
    done
  done
done
