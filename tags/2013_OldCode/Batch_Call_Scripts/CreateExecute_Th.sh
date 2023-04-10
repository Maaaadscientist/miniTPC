############################################################################
# The purpose of this script is to send jobs to the batch to produce separate
# files for each daugher in the Th232 decay chain with correct relative 
# branching ratios in the specified components of nEXO.  The number of files 
# and number of decays produced in each file are defined in the 
# 'DecayValues.txt' script.  It creates python scripts for each file and then 
# executes them.  A different seed is used for each file.

#!/bin/sh

iso="Th232"
. Batch_Call_Scripts/DecayValues.txt

### Name of the python file ####
### Incrementation and .py extention are added below ###
PythonFileName=""

### Define the path to the nEXO Executable ####
ExecutablePath=""

### Define the output root file name
### Incrementation is already included
outputFileName=""

### List components to simulate Th232 chain decays in

for type in FieldRing TeflonInsulator 
#FieldRing TPC TReflector APDPlatter TeflonInsulator FieldSupport
#InnerCryo OuterCryo HFE
do 


#if [ $iso = Th232 ]; then

numdecays="numdecays_$type"
eval numdecays=\$$numdecays
factor="factor_$type"
eval factor=\$$factor

## List the specific isotopes you want to simulate
for piece in Ac228 Ra224 Bi212 Tl208

#Th232 Ra228 Ac228 Th228 Ra224 Rn220 Po216 Pb212 Bi212 Po212 Tl208


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


for((i = 1; i <= $factor; i++))

do
echo "
##############################################################################
#           Event Generator for $piece in the $type
#
##############################################################################

/rootfile/fileName ${outputFileName}_${i}

/run/initialize

/run/verbose 0
/event/verbose 0
/tracking/verbose 0
/grdm/verbose 0

/gps/pos/type Volume
/gps/pos/shape Cylinder
/gps/pos/centre 0 0 0 cm
/gps/pos/halfz 80 cm
/gps/pos/radius 80 cm
/gps/pos/confine $type
/gps/energy 0 keV
/gps/particle ion
$gpsion

/run/beamOn $numdecays

"  > ${PythonFileName}_${i}.py

bsub -q xxl ${ExecutablePath} ${PythonFileName}_${i}.py $i
done




done
done


done






