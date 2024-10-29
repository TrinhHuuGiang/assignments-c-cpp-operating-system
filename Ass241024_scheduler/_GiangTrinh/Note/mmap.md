# So sánh các hàm quản lý vùng bộ nhớ chia sẻ giữa Linux và Windows

| Chức năng                          | Linux              | Windows              |
|------------------------------------|--------------------|----------------------|
| Tạo vùng bộ nhớ chia sẻ            | `shm_open`         | `CreateFileMapping`  |
| Đặt kích thước vùng nhớ            | `ftruncate`        | Đặt trực tiếp trong `CreateFileMapping` |
| Ánh xạ vào không gian địa chỉ      | `mmap`             | `MapViewOfFile`      |
| Giải phóng ánh xạ bộ nhớ           | `munmap`(optional) | `UnmapViewOfFile`    |
| Xóa vùng nhớ khỏi hệ thống         | `shm_unlink`       | `CloseHandle`        |
