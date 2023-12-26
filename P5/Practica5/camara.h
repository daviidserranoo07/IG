#ifndef camara_h
#define camara_h

class Camara{
private:
    float view_rotx, view_roty;//Ángulos de rotación de la cámara
    float D; //Distancia de la cámara
    float moverX, moverY;//Trasldar en el eje XY;
public:
    Camara();
    Camara(float view_rotx, float view_roty, float D);
    float getView_rotx();
    float getView_roty();
    float getDistancia();
    void setAngulo(float view_rotx, float view_roty);
    void setDistancia(float D);
    void setXY(float x,float y);
    void aplicarTransformacion();
};


#endif