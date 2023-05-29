# Detector material details
## Liquid Xe material
Xe, density = 3.057g/cm3, element number 1, liquid, 173.15kelvin, 1*atmophere
## Liquid Xe Add properties
1. Add const property electricfied 380V/cm, surface, gate, cathode, bottom 0V/cm
2. TOTALNUM_INT_SITES (缺陷常数) -1?
3.  RINDEX wavelength [144.5,...,2058.2][nm] [1.82,...,1.384]
4. ABSLENGHTH 线性吸收系数100m 波长 [144.5,2058.2][nm]
5. RAYLENGH 瑞利散射系数 40cm 波长 [144.5,2058.2][nm]

## SiO2 
Add properties (G4_SILICON_DIOXIDE->Anode, SiPM pad, SiPM Base)
1. RINDEX [0.602,...,12.60][eV] RefIndex[1.455,1.800]
2. ABSLENGTH [0.602,...,12.60][eV] 10000cm



## Other material from G4
G4_STAINLESS-STEEL -> Inner vessel, Outer vessel, Top construction
G4_Cu -> Cooper vessel, Field rings, Cathode
G4_Si -> Active sipms
