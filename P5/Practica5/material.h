#ifndef material_h
#define material_h

class Material{
private:
    float ambiental[3];
    float especular[3];
    float difusa[3];
    float emision[4];
    float brillo;
public:
    Material();
    void setAmbiental(float R, float G, float B);
    void setEspecular(float R, float G, float B);
    void setDifusa(float R, float G, float B);
    void setEmision(float R, float G, float B, float C);
    void setBrillo(float brillo);
    void aplicarMaterial();
};

#endif