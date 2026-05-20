#include "BoiCanh.h"
#include <GL/glut.h> // Bắt buộc phải có dòng này để các hàm OpenGL hoạt động

void drawRoom() {
    float roomSize = 20.0f; float roomHeight = 6.0f;
    glColor3f(1.0f, 1.0f, 1.0f); // Luôn để trắng để Texture hiện đúng màu

    // 1. VẼ SÀN (Vân gỗ)
    glBindTexture(GL_TEXTURE_2D, sanTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-roomSize, 0.0f, -roomSize);
    glTexCoord2f(5.0f, 0.0f); glVertex3f(roomSize, 0.0f, -roomSize);
    glTexCoord2f(5.0f, 5.0f); glVertex3f(roomSize, 0.0f, roomSize);
    glTexCoord2f(0.0f, 5.0f); glVertex3f(-roomSize, 0.0f, roomSize);
    glEnd();

    // 2. VẼ TRẦN (Vân gỗ hoặc thạch cao)
    glBindTexture(GL_TEXTURE_2D, tranTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-roomSize, roomHeight, -roomSize);
    glTexCoord2f(5.0f, 0.0f); glVertex3f(roomSize, roomHeight, -roomSize);
    glTexCoord2f(5.0f, 5.0f); glVertex3f(roomSize, roomHeight, roomSize);
    glTexCoord2f(0.0f, 5.0f); glVertex3f(-roomSize, roomHeight, roomSize);
    glEnd();

    // 3. VẼ 4 MẶT TƯỜNG (Vân đá sang trọng)
    glBindTexture(GL_TEXTURE_2D, tuongTexture);
    glBegin(GL_QUADS);
    // Tường sau (Z âm)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-roomSize, 0.0f, -roomSize);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(roomSize, 0.0f, -roomSize);
    glTexCoord2f(2.0f, 1.0f); glVertex3f(roomSize, roomHeight, -roomSize);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-roomSize, roomHeight, -roomSize);

    // Tường trước (Z dương)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(roomSize, 0.0f, roomSize);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(-roomSize, 0.0f, roomSize);
    glTexCoord2f(2.0f, 1.0f); glVertex3f(-roomSize, roomHeight, roomSize);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(roomSize, roomHeight, roomSize);

    // Tường trái (X âm)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-roomSize, 0.0f, roomSize);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(-roomSize, 0.0f, -roomSize);
    glTexCoord2f(2.0f, 1.0f); glVertex3f(-roomSize, roomHeight, -roomSize);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-roomSize, roomHeight, roomSize);

    // Tường phải (X dương)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(roomSize, 0.0f, -roomSize);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(roomSize, 0.0f, roomSize);
    glTexCoord2f(2.0f, 1.0f); glVertex3f(roomSize, roomHeight, roomSize);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(roomSize, roomHeight, -roomSize);
    glEnd();
}

void drawPillar(float px, float pz) {
    glPushMatrix();
    glTranslatef(px, 3.0f, pz);
    glScalef(1.0f, 6.0f, 1.0f);
    glColor3f(0.4f, 0.4f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void veBucTranh(GLuint texID, float px, float py, float pz, float gocXoayY) {
    glPushMatrix();
    glTranslatef(px, py, pz);
    glRotatef(gocXoayY, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 0.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void veTuongNgheThuat(float px, float pz) {
    glPushMatrix();
    glTranslatef(px, 0.0f, pz);
    glPushMatrix(); glTranslatef(0.0f, 1.0f, 0.0f); glScalef(1.0f, 2.0f, 1.0f); glColor3f(0.2f, 0.2f, 0.2f); glutSolidCube(1.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 2.6f, 0.0f); glColor3f(0.8f, 0.6f, 0.1f); glutSolidTeapot(0.6f); glPopMatrix();
    glPopMatrix();
}

void veChauCay(float px, float pz) {
    glPushMatrix();
    glTranslatef(px, 0.0f, pz);
    glPushMatrix(); glTranslatef(0.0f, 0.5f, 0.0f); glColor3f(0.4f, 0.2f, 0.1f); glutSolidCube(1.0f); glPopMatrix();
    glColor3f(0.1f, 0.5f, 0.1f);
    glPushMatrix(); glTranslatef(0.0f, 1.5f, 0.0f); glutSolidSphere(0.6f, 16, 16); glPopMatrix();
    glPopMatrix();
}

void veLongKinh(float px, float pz) {
    glPushMatrix();
    glTranslatef(px, 0.0f, pz);
    // Bệ đỡ
    glPushMatrix(); glTranslatef(0.0f, 0.5f, 0.0f); glScalef(1.5f, 1.0f, 1.5f); glColor3f(0.3f, 0.1f, 0.0f); glutSolidCube(1.0f); glPopMatrix();
    // Viên kim cương
    glPushMatrix(); glTranslatef(0.0f, 1.6f, 0.0f); glScalef(0.5f, 0.5f, 0.5f); glColor3f(0.0f, 0.8f, 1.0f); glutSolidOctahedron(); glPopMatrix();
    // Lồng kính
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.8f, 0.9f, 1.0f, 0.3f);
    glPushMatrix(); glTranslatef(0.0f, 1.6f, 0.0f); glutSolidCube(1.2f); glPopMatrix();
    glDisable(GL_BLEND);
    glPopMatrix();
}