#ifndef MyOpticalSurface_hh
#define MyOpticalSurface_hh

#include "G4OpticalSurface.hh"

class MyOpticalSurface : public G4OpticalSurface {
    public:
            MyOpticalSurface(const G4String& name): G4OpticalSurface(name) {}
            void SetReflectivity_AOI(const std::vector<double>& v1, const std::vector<double>& v2) {AOI = v1;Reflectivity_AOI = v2;UseExperimentData = true;}
            bool GetUseExperimentData(){return UseExperimentData;}
            double GetReflectivity_AOI(double aPhotonAOI){
    double ref;
    ref = 1;
    if (aPhotonAOI<AOI.front()) {G4cout<<"Attempt to below range"<<G4endl;ref = Reflectivity_AOI.front();}
    else if (aPhotonAOI>AOI.back()) {G4cout<<"Attempt to above range"<<G4endl;ref = Reflectivity_AOI.back();}
    else{
        for(size_t i = 0;i < AOI.size(); i++){
        if (AOI[i] == aPhotonAOI) {ref = Reflectivity_AOI[i]; break;}
        if (aPhotonAOI<AOI[i]) {
            double x0 = aPhotonAOI;
            double x1 = AOI[i - 1];
            double x2 = AOI[i];
            double y1 = Reflectivity_AOI[i - 1];
            double y2 = Reflectivity_AOI[i];
            ref = y1 + (y2 - y1) * (x0 - x1) / (x2 - x1);
            }    
        }
    }
    if(ref>1){G4cout<<"Warning wrong input refelectivity with aoi!"<<G4endl;ref=1;}
    return ref;
}

    private:
            bool UseExperimentData = false;
            std::vector<double> AOI;
            std::vector<double> Reflectivity_AOI;
};

#endif // MyOpticalSurface_hh


