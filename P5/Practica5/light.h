#ifndef light_h
#define light_h

#include <GL/glut.h>
#include <string>
#include "nodo.h"

class Light : public Nodo{
private:
    GLfloat* pos;
    GLfloat* color;
    GLenum luzID;
public:
    Light();
    Light(GLenum luzID, GLfloat* pos, GLfloat* color);
    void activarLuz();
    void desactivarLuz();
    void setID(GLenum luzID);
    void setColor(GLenum tipo,GLfloat *color);
    void setPos(GLfloat *pos);
};



#endif