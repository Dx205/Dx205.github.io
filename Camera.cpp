#include "Camera.h"
#include <math.h>

// Định nghĩa Pi để tính toán lượng giác (chuyển đổi độ sang radian)
#define M_PI 3.14159265358979323846

Camera::Camera(float startX, float startY, float startZ) {
    x = startX;
    y = startY; // Chiều cao của mắt người (thường giữ cố định)
    z = startZ;

    yaw = -90.0f;  // Mặc định nhìn thẳng theo trục Z âm
    pitch = 0.0f;  // Nhìn ngang, không ngước lên hay cúi xuống

    moveSpeed = 0.5f;
    mouseSensitivity = 0.1f;

    capNhatHuongNhin();
}

void Camera::capNhatHuongNhin() {
    // Dùng công thức lượng giác của Euler Angles để tính vector hướng nhìn 3D
    lx = (float)(cos(yaw * M_PI / 180.0) * cos(pitch * M_PI / 180.0));
    ly = (float)(sin(pitch * M_PI / 180.0));
    lz = (float)(sin(yaw * M_PI / 180.0) * cos(pitch * M_PI / 180.0));
}

void Camera::diTienLui(int huongDi) {
    // Tính toán vị trí dự kiến sẽ bước tới
    float newX = x + lx * moveSpeed * huongDi;
    float newZ = z + lz * moveSpeed * huongDi;

    // Chỉ cho phép bước đi nếu vị trí mới nằm TRONG ranh giới bức tường (-19.5 đến 19.5)
    if (newX > -19.5f && newX < 19.5f) x = newX;
    if (newZ > -19.5f && newZ < 19.5f) z = newZ;
}

void Camera::diSangNgang(int huongDi) {
    float rx = -lz;
    float rz = lx;

    // Tính toán vị trí dự kiến khi đi ngang
    float newX = x + rx * moveSpeed * huongDi;
    float newZ = z + rz * moveSpeed * huongDi;

    // Kiểm tra va chạm tương tự
    if (newX > -19.5f && newX < 19.5f) x = newX;
    if (newZ > -19.5f && newZ < 19.5f) z = newZ;
}

void Camera::xoayHuongNhin(float deltaYaw, float deltaPitch) {
    yaw += deltaYaw * mouseSensitivity;
    pitch += deltaPitch * mouseSensitivity;

    // Khóa góc ngước/cúi cổ (không cho xoay quá 89 độ để tránh hiện tượng lật ngược camera)
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    capNhatHuongNhin();
}