#ifndef BOICANH_H
#define BOICANH_H

#include <GL/glut.h>

// Khai báo extern để file khác (như BoiCanh.cpp) biết các biến này tồn tại
extern GLuint sanTexture, tuongTexture, tranTexture;

void drawRoom();
void drawPillar(float px, float pz);
void veBucTranh(GLuint texID, float px, float py, float pz, float gocXoayY);
void veTuongNgheThuat(float px, float pz);
void veChauCay(float px, float pz);
void veLongKinh(float px, float pz);

#endif