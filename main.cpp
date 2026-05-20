#include <GL/glut.h>
#include <stdlib.h>
#include "Camera.h"
#include "BoiCanh.h" 

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int windowWidth = 800;
int windowHeight = 600;
Camera myCam(0.0f, 2.0f, 5.0f);
int lastMouseX = -1;
int lastMouseY = -1;

GLuint sanTexture, tuongTexture, tranTexture; // Phải khai báo ở đây!
GLuint danhSachTranh[11];

GLuint taiHinhAnh(const char* filename) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    }
    else {
        printf("Loi: Khong the tai anh %s\n", filename);
    }
    stbi_image_free(data);
    return textureID;
}

void hienThi() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glLoadIdentity();

    gluLookAt(myCam.x, myCam.y, myCam.z,
        myCam.x + myCam.lx, myCam.y + myCam.ly, myCam.z + myCam.lz,
        0.0f, 1.0f, 0.0f);

    // 1. VẼ PHÒNG (SÀN, TRẦN, TƯỜNG) - BẬT TEXTURE
    glEnable(GL_TEXTURE_2D);
    drawRoom();

    // 1. Vẽ phòng và trụ (Tắt Texture)
    glDisable(GL_TEXTURE_2D);
    drawRoom();
    drawPillar(10.0f, 10.0f); drawPillar(-10.0f, 10.0f);
    drawPillar(10.0f, -10.0f); drawPillar(-10.0f, -10.0f);

    // 2. Vẽ vật trang trí (Tắt Texture)
    veChauCay(-18.0f, -18.0f); veChauCay(18.0f, -18.0f);
    veTuongNgheThuat(-8.0f, 0.0f); veTuongNgheThuat(8.0f, 0.0f);

    // 3. Vẽ Tranh (Bật Texture)
    glEnable(GL_TEXTURE_2D);
    veBucTranh(danhSachTranh[0], 0.0f, 3.0f, -19.9f, 0.0f);
    veBucTranh(danhSachTranh[1], -8.0f, 3.0f, -19.9f, 0.0f);
    veBucTranh(danhSachTranh[2], 8.0f, 3.0f, -19.9f, 0.0f);
    veBucTranh(danhSachTranh[3], -19.9f, 3.0f, 0.0f, 90.0f);
    veBucTranh(danhSachTranh[4], -19.9f, 3.0f, -8.0f, 90.0f);
    veBucTranh(danhSachTranh[5], -19.9f, 3.0f, 8.0f, 90.0f);
    veBucTranh(danhSachTranh[6], 19.9f, 3.0f, -4.0f, -90.0f);
    veBucTranh(danhSachTranh[7], 19.9f, 3.0f, 4.0f, -90.0f);
    veBucTranh(danhSachTranh[8], 0.0f, 3.0f, 19.9f, 180.0f);
    veBucTranh(danhSachTranh[9], -8.0f, 3.0f, 19.9f, 180.0f);
    veBucTranh(danhSachTranh[10], 8.0f, 3.0f, 19.9f, 180.0f);
    glDisable(GL_TEXTURE_2D);

    // 4. Vẽ Lồng kính (Cuối cùng)
    veLongKinh(0.0f, 0.0f);

    glutSwapBuffers();
}

void thayDoiKichThuoc(int w, int h) {
    if (h == 0) h = 1;
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW); glViewport(0, 0, w, h);
}

void xuLyBanPhim(unsigned char key, int x, int y) {
    if (key == 'w') myCam.diTienLui(1); if (key == 's') myCam.diTienLui(-1);
    if (key == 'a') myCam.diSangNgang(-1); if (key == 'd') myCam.diSangNgang(1);
    if (key == 27) exit(0);
    glutPostRedisplay();
}

void chuotDiChuyen(int x, int y) {
    if (lastMouseX != -1) myCam.xoayHuongNhin((float)(x - lastMouseX), (float)(lastMouseY - y));
    lastMouseX = x; lastMouseY = y;
    glutPostRedisplay();
}

void clickChuot(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { lastMouseX = x; lastMouseY = y; }
    else { lastMouseX = -1; lastMouseY = -1; }
}

void khoiTao() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // Load ảnh
    sanTexture = taiHinhAnh("san_go.jpg");
    tuongTexture = taiHinhAnh("tuong_da.jpg");
    tranTexture = taiHinhAnh("tran_nha.jpg");

    glEnable(GL_DEPTH_TEST); glEnable(GL_TEXTURE_2D);
    float lightPos[] = { 0.0f, 10.0f, 0.0f, 1.0f }; // Đèn ở trên trần chiếu xuống
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    danhSachTranh[0] = taiHinhAnh("monalisa.jpg"); danhSachTranh[1] = taiHinhAnh("starry.jpg");
    danhSachTranh[2] = taiHinhAnh("lastsupper.jpg"); danhSachTranh[3] = taiHinhAnh("scream.jpg");
    danhSachTranh[4] = taiHinhAnh("pearl.jpg"); danhSachTranh[5] = taiHinhAnh("memory.jpg");
    danhSachTranh[6] = taiHinhAnh("venus.jpg"); danhSachTranh[7] = taiHinhAnh("adam.jpg");
    danhSachTranh[8] = taiHinhAnh("vuonxuan.jpg"); danhSachTranh[9] = taiHinhAnh("thieunu.jpg");
    danhSachTranh[10] = taiHinhAnh("emthuy.jpg");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600); glutCreateWindow("3D Art Gallery");
    khoiTao();
    glutDisplayFunc(hienThi); glutReshapeFunc(thayDoiKichThuoc);
    glutKeyboardFunc(xuLyBanPhim); glutMotionFunc(chuotDiChuyen);
    glutMouseFunc(clickChuot);
    glutMainLoop();
    return 0;
}