# Thread Overview

## 1. Build Command
- gcc -o ./build/program program.c -pthread

## 2. Include Files
- pthread.h (C)
- thread (C++)

## 3. Types
- pthread_t: Kiểu đại diện cho một luồng (thread).
- pthread_attr_t: Kiểu chứa các thuộc tính cho một luồng.

## 4. Functions
- pthread_attr_init(pthread_attr_t *attr)
    - **Tham số**: pthread_attr_t *attr: Con trỏ đến biến kiểu pthread_attr_t.
    - **Chức năng**: Khởi tạo các thuộc tính **mặc định** cho luồng.
    - **Giá trị trả về**: Trả về 0 nếu thành công; giá trị khác nếu không thành công.

- pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
    - **Tham số**:
        - pthread_t *thread: Con trỏ đến biến sẽ lưu ID của luồng mới.
        - const pthread_attr_t *attr: Con trỏ đến cấu trúc chứa các thuộc tính. Có thể truyền NULL.
        - void *(*start_routine)(void *): Con trỏ đến hàm mà luồng sẽ thực thi.
        - void *arg: Tham số truyền vào hàm start_routine.
    - **Chức năng**: Tạo một luồng mới và thực thi hàm chỉ định.
    - **Giá trị trả về**: Trả về 0 nếu thành công; giá trị khác nếu không thành công.

- void* name_of_thread_function(void* param)
    - **Tham số**: void *param: Con trỏ đến tham số mà bạn muốn truyền vào hàm.
    - **Chức năng**: Hàm mà luồng sẽ thực thi.
    - **Giá trị trả về**: Trả về con trỏ đến giá trị mà bạn muốn gửi về cho luồng gọi pthread_join().

- pthread_join(pthread_t thread, void **retval)
    - **Tham số**:
        - pthread_t thread: ID của luồng mà bạn muốn chờ.
        - void **retval: Con trỏ đến biến sẽ lưu trữ giá trị trả về từ hàm luồng.
    - **Chức năng**: Chờ cho một luồng hoàn thành.
    - **Giá trị trả về**: Trả về 0 nếu thành công; giá trị khác nếu không thành công.

- pthread_exit(void *retval)
    - **Tham số**: void *retval: Con trỏ đến giá trị bạn muốn trả về cho luồng khác.
    - **Chức năng**: Kết thúc luồng hiện tại và có thể trả về giá trị.
    - **Giá trị trả về**: Không có giá trị trả về (void).
