# Các tham số:
- Thời gian xuất hiện của sự kiện: arrival time
- Thời gian thực thi của sự kiện: burst time

---

# Ý tưởng của thuật toán:
## (1) Khởi tạo danh sách "blocked" cho các sự kiện chưa bắt đầu
Giả sử biết trước thời điểm các sự kiện đến, ta có thể mô phỏng bằng cách:
- Sử dụng một linked list "blocked" để lưu các sự kiện chưa đủ điều kiện chạy do chưa tới arrival time.
- Sắp xếp lại linked list "blocked" theo arrival time tăng dần.

---

## (2) Chọn các sự kiện đủ điều kiện chuyển vào danh sách "ready"
Vì các sự kiện đã được sắp xếp sẵn, chỉ cần:
- Duyệt "blocked" để chọn các sự kiện có arrival time ≤ now.
- Cắt các sự kiện thỏa mãn điều kiện này và thêm vào cuối linked list "ready".

---

## (3) Chọn sự kiện có burst time nhỏ nhất trong danh sách "ready" để thực thi
- Duyệt qua "ready" để tìm sự kiện có burst time nhỏ nhất.
- Lấy sự kiện đó ra khỏi "ready" và đưa vào trạng thái "running".

---

## (4) Chờ tiến trình "running" hoàn thành
Do thuật toán SJN là non-preemptive, cần thực hiện:
- Chờ đến khi tiến trình trong trạng thái "running" hoàn thành.
- Quay lại bước (2) để kiểm tra các tiến trình mới đã đến trong "blocked".
