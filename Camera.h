#pragma once
#include <math.h>

class Camera {
public:
    // Tọa độ vị trí của người dùng
    float x, y, z;
    // Vector hướng nhìn (đang nhìn về đâu)
    float lx, ly, lz;
    // Góc xoay của đầu (Yaw: xoay trái/phải, Pitch: ngước lên/cúi xuống)
    float yaw, pitch;

    // Tốc độ di chuyển và độ nhạy chuột
    float moveSpeed;
    float mouseSensitivity;

    // Hàm khởi tạo (Constructor bắt buộc giữ trùng tên Class)
    Camera(float startX, float startY, float startZ);

    // Cập nhật lại vector hướng nhìn mỗi khi xoay chuột
    void capNhatHuongNhin();

    // Các hàm di chuyển và xoay góc nhìn bằng tiếng Việt
    void diTienLui(int huongDi);
    void diSangNgang(int huongDi);
    void xoayHuongNhin(float deltaYaw, float deltaPitch);
};