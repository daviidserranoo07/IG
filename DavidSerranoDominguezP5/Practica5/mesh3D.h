#ifndef mesh3D_h
#define mesh3D_h
#include <vector>

class Mesh3D{
private:
    std::vector<float> vertices_ply;
	std::vector<int> caras_ply;
	std::vector<float> normalesVertice;
public:
    std::vector<float> getVertices();
    std::vector<int> getCaras();
    std::vector<float> getNormalesVertice();
    void setVertices(std::vector<float> vertices);
    void setCaras(std::vector<int> caras);
    void setNormalesVertice(std::vector<float> normales);
};

#endif