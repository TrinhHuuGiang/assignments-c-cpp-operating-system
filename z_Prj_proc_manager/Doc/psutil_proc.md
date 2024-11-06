# Thư viện Python: `psutil` cho Quản lý Tiến trình

## Mục lục
- [Giới thiệu](#giới-thiệu)
- [Cài đặt](#cài-đặt)
- [Các tính năng chính](#các-tính-năng-chính)
- [Cấu trúc thư viện](#cấu-trúc-thư-viện)
<!-- - [Hướng dẫn sử dụng cơ bản](#hướng-dẫn-sử-dụng-cơ-bản) -->
- [Danh sách các hàm](#danh-sách-các-hàm)
- [Tham khảo thêm](#tham-khảo-thêm)
- [Tài liệu chính thức](#tài-liệu-chính-thức)

---

## Giới thiệu
### Tổng quan
`psutil` (Python System and Process Utilities) là một thư viện đa nền tảng giúp lấy thông tin về việc sử dụng tài nguyên hệ thống (CPU, bộ nhớ, ổ đĩa, mạng, cảm biến) và các tiến trình. Thư viện rất hữu ích cho việc giám sát hệ thống, phân tích hiệu năng, và quản lý tài nguyên của tiến trình.

### Lợi ích của `psutil`
- Quản lý và giám sát tài nguyên hệ thống hiệu quả
- Lấy thông tin chi tiết về tiến trình và thực hiện các thao tác như dừng hoặc tạm ngừng tiến trình
- Phù hợp để xây dựng công cụ giám sát hệ thống và tự động hóa

## Cài đặt
Cài đặt `psutil` qua pip:

```bash
pip install psutil
```
## Các tính năng chính

- Quản lý Tiến trình: Bắt đầu, dừng và giám sát tiến trình hệ thống
- Thông tin Hệ thống: Truy cập CPU, bộ nhớ, ổ đĩa và sử dụng mạng
- Dữ liệu Cảm biến: Lấy dữ liệu nhiệt độ và pin (nếu có)

## Cấu trúc thư viện

`psutil` cung cấp nhiều module và phương thức để tương tác với tài nguyên hệ thống. Các mudole chính bao gồm:
- Process: Tương tác với các tiến trình hệ thống
- CPU: Thu thập thông tin và số liệu liên quan đến CPU
- Memory: Truy cập thông tin về việc sử dụng bộ nhớ hệ thống
- Disk: Lấy thông tin về các phân vùng ổ đĩa và tình trạng sử dụng
- Network: Giám sát I/O mạng và thông tin kết nối
- Sensors: Thu thập dữ liệu từ cảm biến nhiệt độ và pin (nếu có)

## Danh sách các hàm

1. `psutil.pids()`: Trả về danh sách đã sắp xếp các PID đang chạy. Để lặp lại tất cả các quy trình và tránh race conditions, nên ưu tiên process_iter().
2. `psutil.process_iter(attrs=None, ad_value=None)`:
- Hàm này trả về một iterator, cho phép lặp qua từng tiến trình một cách hiệu quả.
- Tùy chỉnh thông tin cần lấy về của mỗi tiến trình thông qua tham số `attrs`
- Tham số `ad_value` giúp xử lý trường hợp không thể truy cập được thông tin của một tiến trình nào đó.
- Thứ tự sắp xếp các process sẽ trả về PID của chúng.
``` python
for proc in psutil.process_iter(attrs=['pid', 'name', 'cpu_percent']):
    print(f"PID: {proc.info['pid']}, Name: {proc.info['name']}, CPU%: {proc.info['cpu_percent']}")
psutil.process_iter.cache_clear() //xoá bộ nhớ đệm nội bộ
```
3. `psutil.wait_procs(procs, timeout=None, callback=None)`
- Chờ danh sách các phiên bản Quy trình kết thúc. Nó cung cấp một cách thuận tiện để giám sát và quản lý nhiều quy trình cùng một lúc.
    - Gửi SIGTERM tới danh sách các quy trình
    - Cho các process chút thời gian để chấm dứt
    - Gửi SIGKILL cho những process vẫn còn sống
- **Trả về**: 
    - gone: Danh sách các phiên bản Quy trình đã kết thúc.
    - alive: Danh sách các phiên bản Quy trình vẫn đang chạy.
```python
def on_terminate(proc):
    print(f"Process {proc.pid} terminated with exit code {proc.returncode}")
# Create a list of processes to wait for
procs = [psutil.Process(pid) for pid in [123, 456, 789]]
# Wait for the processes to terminate with a 10-second timeout
gone, alive = psutil.wait_procs(procs, timeout=10, callback=on_terminate)
print(f"Terminated processes: {gone}")
print(f"Still running processes: {alive}")
```







## Tham khảo thêm
- [Kho mã nguồn psutil trên GitHub](https://github.com/giampaolo/psutil)
- [Hướng dẫn Python `psutil` trên Real Python](https://realpython.com/python-psutil)
- [Chi tiết các hàm trong psutil process ](https://psutil.readthedocs.io/en/latest/#processes)

## Tài liệu chính thức
Để có thêm thông tin chi tiết, tham khảo tài liệu chính thức:
- [Tài liệu `psutil`](https://psutil.readthedocs.io/)