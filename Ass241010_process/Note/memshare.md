# 1. `shm_open()`
- **Mục đích**: Được sử dụng để tạo hoặc mở một đối tượng bộ nhớ chia sẻ.
- **Tuyên bố hàm**:
    ```c
    int shm_open(const char *name, int oflag, mode_t mode);
    ```
- **Tham số**:
    - `name`: Tên của đối tượng bộ nhớ chia sẻ. 
    - `oflag`: Các cờ chỉ định hành vi mở đối tượng. Các giá trị thường sử dụng là:
        - `O_CREAT`: Tạo một đối tượng mới nếu nó chưa tồn tại.
        - `O_EXCL`: Tạo đối tượng mới nhưng sẽ thất bại nếu đối tượng đã tồn tại.
        - `O_RDONLY`: Mở chỉ để đọc.
        - `O_RDWR`: Mở để đọc và ghi.
    - `mode`: Quyền truy cập (permissions) của đối tượng được tạo (nếu sử dụng `O_CREAT`). Tham số này được biểu diễn bằng các giá trị tương tự như trong hàm `open()`.
- **Giá trị trả về**:
    - Trả về một mô tả tập tin (file descriptor) nếu thành công.
    - Trả về `-1` và thiết lập `errno` nếu có lỗi.

---

# 2. `ftruncate()`
- **Mục đích**: Được sử dụng để thiết lập kích thước cho bộ nhớ chia sẻ sau khi nó đã được tạo bằng `shm_open()`.
- **Tuyên bố hàm**:
    ```c
    int ftruncate(int fd, off_t length);
    ```
- **Tham số**:
    - `fd`: Mô tả tập tin (file descriptor) của đối tượng bộ nhớ chia sẻ (nhận được từ `shm_open()`).
    - `length`: Kích thước mới (tính theo byte) của đối tượng bộ nhớ chia sẻ.
- **Giá trị trả về**:
    - Trả về `0` nếu thành công.
    - Trả về `-1` và thiết lập `errno` nếu có lỗi.

---

# 3. `mmap()`
- **Mục đích**: Được sử dụng để ánh xạ vùng bộ nhớ chia sẻ vào không gian địa chỉ của tiến trình để có thể truy cập và ghi dữ liệu vào đó.
- **Tuyên bố hàm**:
    ```c
    void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
    ```
- **Tham số**:
    - `addr`: Địa chỉ ưa thích nơi ánh xạ (thường đặt là `NULL` để hệ thống tự chọn địa chỉ).
    - `length`: Kích thước của vùng bộ nhớ để ánh xạ.
    - `prot`: Quyền truy cập (protection) của vùng bộ nhớ. Các giá trị bao gồm:
        - `PROT_READ`: Quyền đọc.
        - `PROT_WRITE`: Quyền ghi.
        - `PROT_EXEC`: Quyền thực thi.
    - `flags`: Các cờ chỉ định hành vi ánh xạ. Các giá trị thường sử dụng:
        - `MAP_SHARED`: Thay đổi sẽ được ghi lại vào đối tượng bộ nhớ được ánh xạ và chia sẻ với các tiến trình khác.
        - `MAP_PRIVATE`: Thay đổi sẽ không được ghi lại và chỉ có thể thấy bởi tiến trình hiện tại.
    - `fd`: Mô tả tập tin của đối tượng bộ nhớ chia sẻ (nhận được từ `shm_open()`).
    - `offset`: Độ lệch so với đầu của đối tượng bộ nhớ được ánh xạ.
- **Giá trị trả về**:
    - Trả về một con trỏ tới vùng nhớ được ánh xạ nếu thành công.
    - Trả về `MAP_FAILED` và thiết lập `errno` nếu có lỗi.

---

# 4. `shm_unlink()`
- **Mục đích**: Khi không còn cần sử dụng bộ nhớ chia sẻ nữa, `shm_unlink()` xóa tên đối tượng bộ nhớ chia sẻ, giúp giải phóng tài nguyên trong hệ thống.
- **Tuyên bố hàm**:
    ```c
    int shm_unlink(const char *name);
    ```
- **Tham số**:
    - `name`: Tên của đối tượng bộ nhớ chia sẻ (đã được tạo bằng `shm_open()`).
- **Giá trị trả về**:
    - Trả về `0` nếu thành công.
    - Trả về `-1` và thiết lập `errno` nếu có lỗi.
