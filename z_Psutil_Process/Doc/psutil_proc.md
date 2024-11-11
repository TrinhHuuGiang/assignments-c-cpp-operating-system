# Thư viện Python: `psutil` cho Quản lý Tiến trình

## Mục lục
- [Giới thiệu](#giới-thiệu)
- [Cài đặt](#cài-đặt)
- [Các tính năng chính](#các-tính-năng-chính)
- [Cấu trúc thư viện](#cấu-trúc-thư-viện)
<!-- - [Hướng dẫn sử dụng cơ bản](#hướng-dẫn-sử-dụng-cơ-bản) -->
- [Danh sách các hàm](#danh-sách-các-hàm)
- [Xử lý ngoại lệ](#exceptions)
- [Process Class](#process-class)
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
for p in alive: // kill các process alive sau khi hết timeout
    p.kill()
```
## Exceptions

1. **`class psutil.Error`**: Lớp ngoại lệ cơ bản, tất cả các trường hợp ngoại lệ khác đều kế thừa từ trường hợp này.
    - Quyền hạn không đủ: Khi chương trình của bạn không có quyền truy cập vào thông tin về các tiến trình khác hoặc không thể thực hiện các thao tác trên chúng.
    - Tiến trình không tồn tại: Khi bạn cố gắng truy cập vào một tiến trình đã bị kết thúc hoặc không tồn tại.
    - Lỗi hệ thống: Khi có lỗi xảy ra ở cấp độ hệ điều hành, ví dụ như lỗi I/O, lỗi bộ nhớ, v.v.
    - Tham số không hợp lệ: Khi bạn truyền vào các tham số không đúng hoặc không hợp lệ cho các hàm của psutil.

**Lí do sử dụng**: giúp chương trình không bị dừng đột ngột, xử lý lỗi linh hoạt hơn như log lỗi, gửi thông báo, thực hiện các biện pháp khôi phục

**Ví dụ**
```python
try:
    # Lấy thông tin của một tiến trình không tồn tại
    p = psutil.Process(999999)
    print(p.name())
except psutil.Error as e:
    print(f"Lỗi xảy ra: {e}") 
```
2. **`class psutil.NoSuchProcess(pid, name=None, msg=None)`**: được đưa ra khi không thể tìm thấy một quy trình có ID tiến trình (PID) được chỉ định hoặc tiến trình đó không còn tồn tại(terminated). Đây là một lớp con của ngoại lệ psutil.Error tổng quát hơn.

**Lí do sử dụng**
- Xử lý lỗi: Điều quan trọng là phải xử lý ngoại lệ này để ngăn chương trình của bị crashing (*sập đột ngột*).
- Thông tin lỗi cụ thể: Đối tượng ngoại lệ cung cấp thông tin về quy trình bị thiếu, chẳng hạn như PID và tên của nó (nếu có).

**Ví dụ**
```python
try:
    p = psutil.Process(12345)  # Assuming process with PID 12345 doesn't exist
    print(p.name())
except psutil.NoSuchProcess as e:
    print(f"Process with PID 12345 not found: {e}")
```

3. **`class psutil.ZombieProcess(pid, name=None, ppid=None, msg=None)`**: đưa ra khi một tiến trình ở trạng thái zombie. Một tiến trình zombie là một tiến trình đã kết thúc nhưng mục nhập của nó trong bảng tiến trình vẫn tồn tại.
    - Đưa ra khi cố gắng truy cập thông tin về tiến trình zombie bằng psutil. Có thể xảy ra trong trường hợp một tiến trình con đã kết thúc nhưng tiến trình cha của nó vẫn chưa gọi **wait()** để thu thập nó.

**Lí do sử dụng**
- Tiến trình Zombie: Chúng tiêu tốn tài nguyên hệ thống tối thiểu, nhưng chúng có thể làm lộn xộn bảng tiến trình.
- Trách nhiệm của tiến trình cha: Trách nhiệm của tiến trình cha là thu thập các tiến trình con của nó bằng cách sử dụng lệnh gọi hệ thống **wait()**.

**Giải pháp**
- Sự khác biệt về hệ điều hành: Hoạt động của các tiến trình zombie có thể khác nhau một chút giữa các hệ điều hành khác nhau.

- Công cụ giám sát hệ thống: Các công cụ như **top** hoặc **htop** có thể giúp xác định và giám sát các tiến trình của zombie.

- Thực tiễn tốt nhất: Đảm bảo rằng tiến trình của bạn xử lý đúng tiến trình con và gọi **wait()** để thu thập chúng.

**Ví dụ**
```python
try:
    p = psutil.Process(12345)  # Assuming process 12345 is a zombie process
    print(p.name())
except psutil.ZombieProcess as e:
    print(f"Process with PID 12345 is a zombie process: {e}")
```


4. **`class psutil.AccessDenied(pid=None, name=None, msg=None)`**: đưa ra khi người dùng thiếu đủ quyền để truy cập thông tin về một tiến trình cụ thể hoặc thực hiện các thao tác trên đó.
    - Quyền không đủ: Khi người dùng chạy tập lệnh Python không có các đặc quyền cần thiết để truy cập thông tin tiến trình.
    - Hạn chế của Hệ điều hành: Một số hệ điều hành có thể áp đặt các hạn chế đối với việc truy cập thông tin tiến trình, đặc biệt là đối với các tiến trình hệ thống.

**Giải pháp**
- Chạy bằng quyền root: Trên các hệ thống giống Unix, việc chạy tập lệnh bằng quyền root thường có thể cung cấp các quyền cần thiết. Tuy nhiên, việc này cần được thực hiện một cách thận trọng và chỉ khi thực sự cần thiết.

- Sử dụng sudo: Trên các hệ thống giống Unix, bạn có thể sử dụng sudo để tạm thời nâng cao đặc quyền cho một lệnh cụ thể.

- Phương pháp tiếp cận thay thế: Trong một số trường hợp, bạn có thể nhận được thông tin hạn chế về các quy trình mà không có quyền truy cập đầy đủ.

**Ví dụ**
```python
try:
    p = psutil.Process(1)  # Trying to access the init process (usually requires root privileges)
    print(p.name())
except psutil.AccessDenied as e:
    print(f"Access denied to process with PID 1: {e}")
```
5. **`class psutil.TimeoutExpired(seconds, pid=None, name=None, msg=None)`**: đưa ra khi thời gian chờ trong khi chờ quá trình kết thúc nhưng tiến trình vẫn alive hoặc thực hiện một hành động. 

**Giải pháp**
- Điều chỉnh thời gian chờ: Giá trị thời gian chờ thích hợp tùy thuộc vào trường hợp sử dụng cụ thể và thời lượng dự kiến ​​của quá trình.

- Hoạt động không chặn: Hãy cân nhắc sử dụng các hoạt động không chặn hoặc kỹ thuật lập trình không đồng bộ để tránh chặn tập lệnh của bạn trong thời gian dài.

- Thông báo lỗi: Thông báo ngoại lệ có thể cung cấp thông tin về quá trình đã hết thời gian chờ và lý do hết thời gian chờ.

**Ví dụ**
```python
try:
    p = psutil.Process(12345)
    p.wait(timeout=5)  # Wait for 5 seconds for the process to terminate
except psutil.TimeoutExpired as e:
    print(f"Process {p.pid} did not terminate within 5 seconds: {e}")
```
## Process Class

**`oneshot()`** : 
- Trình quản lý bối cảnh **(context manager)** tiện ích giúp tăng tốc đáng kể việc truy xuất thông tin nhiều quy trình cùng một lúc
- Thông tin tiến trình khác nhau bên trong (ví dụ: *`name(), ppid(), uids(), create_time(), ...`)* có thể được tìm nạp bằng cách sử dụng cùng một quy trình, nhưng chỉ một giá trị được trả về và các giá trị khác sẽ bị loại bỏ.
- Tiến trình nội bộ được thực thi 1 lần, giá trị quan tâm sẽ được trả về và các giá trị khác sẽ được lưu vào bộ nhớ cached. Bộ đệm sẽ bị xóa khi thoát khỏi khối quản lý bối cảnh.

**Lưu ý** : Để tìm nạp nhiều thông tin về quy trình cùng một lúc một cách hiệu quả, hãy đảm bảo sử dụng trình quản lý bối cảnh `oneshot()` hoặc phương thức tiện ích `as_dict()`.

**Ví dụ**
```python
p = psutil.Process()
with p.oneshot():
    p.name()  # execute internal routine once collecting multiple info
    p.cpu_times()  # return cached value
    p.cpu_percent()  # return cached value
    p.create_time()  # return cached value
    p.ppid()  # return cached value
    p.status()  # return cached value
```
<hr style="border: px solid;">

**`exe()`**: trả về đường dẫn thực thi của một tiến trình. Xác định chương trình hoặc tập lệnh cụ thể mà một tiến trình đang chạy.
- Khả năng tương thích đa nền tảng: Phương pháp này hoạt động trên các hệ điều hành khác nhau, cung cấp một cách nhất quán để truy xuất đường dẫn thực thi.path.
- Công cụ có giá trị để giám sát hệ thống, phân tích quy trình và điều tra bảo mật.

**Ví dụ**

```python
p = psutil.Process(psutil.Process().pid)

# Get the executable path
exe_path = p.exe()

print(exe_path)
```

<hr style="border: px solid;">

**`cmdline()`**: Giá trị trả về là danh sách các chuỗi, trong đó mỗi chuỗi đại diện cho một đối số dòng lệnh.

**Ví dụ**

```python
# Get the current Python process
p = psutil.Process(psutil.Process().pid)

# Get the command-line arguments
cmdline = p.cmdline()

print(cmdline)
# ['python3', 'Code/main.py']
```

<hr style="border: px solid;">

**`environ()`**: trả về một từ điển chứa các biến môi trường của một tiến trình. Biến môi trường là cặp key-value cung cấp thông tin về môi trường thực thi của quy trình.

**Đặc điểm**:
- Các biến môi trường cụ thể có sẵn có thể khác nhau giữa các hệ điều hành khác nhau.
- Các biến này có thể ảnh hưởng đến hành vi của một quy trình, chẳng hạn như thư mục làm việc, đường dẫn đến tệp thực thi và các cài đặt cấu hình khác.
- Truy cập và sửa đổi các biến môi trường, vì nó có thể gây ra những hậu quả không lường trước được.

**Ví dụ**
```python
# Get the current Python process
p = psutil.Process(psutil.Process().pid)

# Get the environment variables
env_vars = p.environ()

print(env_vars)
```

<hr style="border: px solid;">

**`create_time()`**: trả về thời gian tạo của một tiến trình. Nó cung cấp dấu thời gian khi quá trình được bắt đầu, được biểu thị dưới dạng số dấu phẩy động biểu thị số giây kể từ kỷ nguyên Unix (ngày 1 tháng 1 năm 1970, 00:00:00 UTC).

**Ví dụ**

```python
# Get the current Python process
p = psutil.Process(psutil.Process().pid)

# Get the creation time
create_time = p.create_time()

# Convert the creation time to a human-readable format
create_time_str = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(create_time))

print(f"Process created at: {create_time_str}")
```

<hr style="border: px solid;">

**`as_dict(attrs=None, ad_value=None)`**: Cung cấp một cách thuận tiện để truy xuất nhiều thuộc tính của một quy trình dưới dạng từ điển. 

**Tham số**:
- attrs: Danh sách tên thuộc tính tùy chọn để đưa vào từ điển. Nếu không được chỉ định, tất cả các thuộc tính có sẵn sẽ được bao gồm.
- ad_value: A default value to use for attributes that cannot be retrieved due to access restrictions or other errors.

**Ví dụ**

```python
# Get the current Python process
p = psutil.Process(psutil.Process().pid)

# Get a dictionary of process information, including PID, name, and CPU usage
info = p.as_dict(attrs=['pid', 'name', 'cpu_percent'])

print(info)
```

<hr style="border: px solid;">

**`parent()`**: trả về một đối tượng đại diện cho tiến trình cha trực tiếp của tiến trình hiện tại.
```python
# Get the parent process
parent_process = p.parent()

if parent_process:
    print(f"Parent process PID: {parent_process.pid}")
    print(f"Parent process name: {parent_process.name()}")
else:
    print("This process is a top-level process.")
```

<hr style="border: px solid;">

**`parents()`**: trả về một danh sách các đối tượng đại diện cho tất cả các tiến trình tổ tiên của tiến trình hiện tại, bắt đầu từ tiến trình cha trực tiếp và đi lên theo hệ thống phân cấp tiến trình.

**Ví dụ**

```python
# Get the current Python process
p = psutil.Process(psutil.Process().pid)

# Get all ancestor processes
ancestor_processes = p.parents()

for ancestor in ancestor_processes:
    print(f"Ancestor process PID: {ancestor.pid}")
    print(f"Ancestor process name: {ancestor.name()}")
```
<hr style="border: px solid;">

**`status`**: Trạng thái quá trình hiện tại dưới dạng một chuỗi. Chuỗi trả về là một trong các hằng số psutil.STATUS_*.

<hr style="border: px solid;">

**`cwd()`**: trả về thư mục làm việc hiện tại của một tiến trình. Đây là thư mục mà quy trình được khởi chạy hoặc thư mục mà quy trình sau đó đã thay đổi thành.

<hr style="border: px solid;">

**`username`**: Tên của người dùng sở hữu quá trình. Trên UNIX, điều này được tính bằng cách sử dụng uid quy trình thực.

<hr style="border: px solid;">

**`uids()`**: trả về một namedtuple chứa ID người dùng (UID) thực, hiệu quả và đã lưu của một quy trình. Các UID này rất quan trọng để hiểu các quyền và bối cảnh bảo mật của quy trình.

**Ví dụ**

```python
# Get the current Python process
p = psutil.Process(psutil.Process().pid)

# Get the user IDs
uids = p.uids()

print(f"Real UID: {uids.real}")
print(f"Effective UID: {uids.effective}")
print(f"Saved UID: {uids.saved}")
# Real UID: 1000
# Effective UID: 1000
# Saved UID: 1000
```
<hr style="border: px solid;">

**`gids()`**: Id người dùng thực, hiệu quả và được lưu của quá trình này dưới dạng một bộ dữ liệu namedtuple.

- `Namedtuple`: Đây là một kiểu dữ liệu đặc biệt trong Python, cho phép tạo các cấu trúc dữ liệu giống như tuple nhưng có tên cho từng phần tử.
- `GID: Group` ID là một số nguyên duy nhất xác định một nhóm người dùng trong hệ thống Unix-like.
- `Real GID: `GID thực tế của người dùng khởi chạy tiến trình.
- `Effective `GID: GID hiệu dụng mà tiến trình đang sử dụng để thực hiện các hoạt động. Nó có thể khác với GID thực tế nếu tiến trình đã thay đổi quyền hạn của mình.
- `Saved GID:` GID được lưu trữ để phục hồi sau khi tiến trình thay đổi quyền hạn của mình.

**Ví dụ**

```python

gids = p.gids()

print(f"Real GID: {gids.real}")
print(f"Effective GID: {gids.effective}")
print(f"Saved GID: {gids.saved}")
# Real GID: 1000
# Effective GID: 1000
# Saved GID: 1000
```
<hr style="border: px solid;">

**`terminal()`**: trả về thiết bị đầu cuối được liên kết với một quy trình. Thông tin này có thể hữu ích để hiểu cách một quy trình tương tác với thiết bị đầu cuối và cho mục đích gỡ lỗi.

**Ví dụ**

```python
# Get the current Python process
p = psutil.Process(psutil.Process().pid)

# Get the terminal device
terminal = p.terminal()

if terminal:
    print(f"Process is associated with terminal: {terminal}")
else:
    print("Process is not associated with a terminal.")
# Process is associated with terminal: /dev/pts/7
```
<hr style="border: px solid;">

**`nice(value=None)`**: Nhận hoặc thiết lập mức độ ưu tiên của quy trình (ưu tiên). Trên UNIX, đây là con số thường đi từ -20 đến 20. Giá trị Nice càng cao thì mức độ ưu tiên của quy trình càng thấp.

**Lí do sử dụng**:
- Cân bằng việc sử dụng tài nguyên giữa các tiến trình khác nhau.
- Tự nguyện giảm mức độ ưu tiên của quy trình, để quan tâm đến những người dùng khác, đặc biệt là trên các hệ thống dùng chung.

**Ví dụ**

```python
p.nice(10)  # set
p.nice()  # get
```
<hr style="border: px solid;">

**`ionice(ioclass=None, value=None)`**: Nhận hoặc thiết lập mức độ độc đáo I/O của quy trình (ưu tiên)


**Tham số**
- class: Xác định lớp ưu tiên (Idle, Best-effort, Real-time).
- value: Giá trị phụ thuộc vào lớp ưu tiên, thường được sử dụng để tinh chỉnh mức độ ưu tiên trong cùng một lớp.

**Cấp độ ưu tiên I/O**
- `Idle`: Ưu tiên thấp nhất, thích hợp cho các tiến trình nền hoặc các tiến trình không quan trọng đến hiệu suất.
- `Best-effort`: Ưu tiên trung bình, đây là mức ưu tiên mặc định cho hầu hết các tiến trình.
- `Real-time`: Ưu tiên cao nhất, dành cho các tiến trình đòi hỏi thời gian đáp ứng thực sự nhanh, chẳng hạn như các tiến trình âm thanh hoặc video.

**Ví dụ**

```python

```

**``**:

**Ví dụ**

```python

```

**``**:

**Ví dụ**

```python

```

**``**:

**Ví dụ**

```python

```




**``**:

**Ví dụ**

```python

```


<!-- -----------------------Template---------------------------------------------- -->
<!-- .**``**:

- **Lí do sử dụng**
**Ví dụ**
```python

``` -->
<!-- -------------------------------------------------------------------------------->






## Tham khảo thêm
- [Kho mã nguồn psutil trên GitHub](https://github.com/giampaolo/psutil)
- [Hướng dẫn Python `psutil` trên Real Python](https://realpython.com/python-psutil)
- [Chi tiết các hàm trong psutil process ](https://psutil.readthedocs.io/en/latest/#processes)

## Tài liệu chính thức
Để có thêm thông tin chi tiết, tham khảo tài liệu chính thức:
- [Tài liệu `psutil`](https://psutil.readthedocs.io/)