#!/bin/sh

date="7_23_13"
iso="Th232"
#iso="Xe137"
. Batch_Call_Scripts/DecayValues.txt

numdecays_ActiveLXe="1000000"
factor_ActiveLXe="10"

numdecays_InactiveLXe="1000000"
factor_InactiveLXe="10"



for type in FieldRing TeflonInsulator TPC APDPlatter TReflector FieldSupport
#FieldRing TPC TReflector APDPlatter TeflonInsulator FieldSupport
#InnerCryo OuterCryo HFE
do 


#mkdir ${type}-${date}

#if [ $iso = Th232 ]; then

numdecays="numdecays_$type"
eval numdecays=\$$numdecays
factor="factor_$type"
eval factor=\$$factor


for piece in Tl208
#Ac228 Ra224 Bi212 Tl208
#Rn220 Po216 Pb212 Bi212 Po212 Tl208
#

#Th232 Ra228 Ac228 Th228 Ra224 Rn220 Po216 Pb212 Bi212 Po212 Tl208

#Pieces with gammas emitted
# 

do

echo "$piece"

if [ $piece = Xe137 ]; then
gpsion="/gps/ion 54 137
/grdm/nucleusLimits 137 137 54 54"
fi

if [ $piece = Th232 ]; then
gpsion="/gps/ion 90 232
/grdm/nucleusLimits 232 232 90 90"
fi

if [ $piece = Ra228 ]; then
gpsion="/gps/ion 88 228
/grdm/nucleusLimits 228 228 88 88"
fi

if [ $piece = Ac228 ]; then
gpsion="/gps/ion 89 228
/grdm/nucleusLimits 228 228 89 89"
fi

if [ $piece = Th228 ]; then
gpsion="/gps/ion 90 228
/grdm/nucleusLimits 228 228 90 90"
fi

if [ $piece = Ra224 ]; then
gpsion="/gps/ion 88 224
/grdm/nucleusLimits 224 224 88 88"
fi

if [ $piece = Rn220 ]; then
gpsion="/gps/ion 86 220
/grdm/nucleusLimits 220 220 86 86"
fi

if [ $piece = Po216 ]; then
gpsion="/gps/ion 84 216
/grdm/nucleusLimits 216 216 84 84"
fi

if [ $piece = Pb212 ]; then
gpsion="/gps/ion 82 212
/grdm/nucleusLimits 212 212 82 82"
fi

if [ $piece = Bi212 ]; then
gpsion="/gps/ion 83 212
/grdm/nucleusLimits 212 212 83 83"
fi

if [ $piece = Po212 ]; then
numdecays=$(($numdecays*64/100))
gpsion="/gps/ion 84 212
/grdm/nucleusLimits 212 212 84 84"
fi

if [ $piece = Tl208 ]; then
numdecays=$(($numdecays*36/100))
gpsion="/gps/ion 81 208
/grdm/nucleusLimits 208 208 81 81"
fi


for((i = 1; i <= 1; i++))
#for((i = 1; i <= $factor; i++))
#for i in 12 17 74 75 93 94
do
echo "
##############################################################################
#           Event Generator for $piece in the $type
#
##############################################################################

/rootfile/fileName /nfs/slac/g/exo/user-data/tesjohns/TPC_Components/${type}-${date}/${type}-${iso}-${piece}-${date}-${i}_200

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

/run/beamOn 10000" > /nfs/slac/g/exo/user-data/tesjohns/TPC_Components/${type}-${date}/${type}-${iso}-${piece}-${date}-${i}.mac


#bsub -q xxl 
echo "type = ${type}"
~/geant4/bin/Linux-g++/CoppernEXO /nfs/slac/g/exo/user-data/tesjohns/TPC_Components/$type-$date/$type-$iso-$piece-$date-$i.mac $i

#~/geant4/bin/Linux-g++/CoppernEXO /nfs/slac/g/exo/user-data/tesjohns/TPC_Components/$type-$date/$type-$iso-$piece-$date-$i.mac $i

done
done

#else
#echo "Not the right isotope."
#fi

done






