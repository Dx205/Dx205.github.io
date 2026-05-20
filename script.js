// ====== HƯỚNG DẪN CÀI ĐẶT NGÀY ======
// Đổi ngày bắt đầu yêu của bạn ở đây theo định dạng: YYYY-MM-DD
const startDateString = "2026-02-10"; 

function calculateDays() {
    const startDate = new Date(startDateString);
    const currentDate = new Date();
    
    // Tính toán số mili-giây chênh lệch
    const differenceInTime = currentDate.getTime() - startDate.getTime();
    
    // Chuyển đổi sang số ngày
    const differenceInDays = Math.floor(differenceInTime / (1000 * 3600 * 24));
    
    // Hiển thị ra màn hình
    document.getElementById("days").innerText = differenceInDays;
}

// Chạy hàm tính toán khi load trang
calculateDays();