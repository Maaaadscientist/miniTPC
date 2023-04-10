#!/bin/sh
date="5_27_13"
iso="Co60"
. Batch_Call_Scripts/DecayValues.txt

for type in TPC
#HFE InnerCryo OuterCryo
#TPC FieldRing TReflector APDPlatter KCables TeflonInsulator FieldSupport

do 
#rm -rf $type-$date
#mkdir /nfs/slac/g/exo/user-data/tesjohns/TPC_Components/$type-$date

if [ $iso = Co60 ]; then
gpsion="/gps/ion 27 60 0 0"
numdecays="numdecays_$type"
eval numdecays=\$$numdecays
factor="factor_$type"
eval factor=\$$factor
echo "$factor"
fi




for(( i = 1; i<=$factor; i++))
do
echo "
##############################################################################
#           Event Generator for $iso in the $type
#
##############################################################################

/rootfile/fileName $EXODIR/tesjohns/ClusteringAlgorithm/$type-$iso-$date-$i

/run/initialize

/run/verbose 0
/event/verbose 0
/tracking/verbose 0
/grdm/verbose 0

/gps/pos/type Volume
/gps/pos/shape Cylinder
/gps/pos/centre 0 0 0 cm
/gps/pos/halfz 200 cm
/gps/pos/radius 200 cm
/gps/pos/confine $type
/gps/energy 0 keV
/gps/particle ion
$gpsion

/run/beamOn $numdecays

"  > $EXODIR/tesjohns/ClusteringAlgorithm/$type-$iso-$date-$i.mac

bsub -q xlong ~/geant4/bin/Linux-g++/CoppernEXO $EXODIR/tesjohns/ClusteringAlgorithm/$type-$iso-$date-$i.mac 

done



done
