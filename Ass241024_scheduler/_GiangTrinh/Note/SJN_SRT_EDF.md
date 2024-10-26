#SJN (Shortest Job Next):

    *SJN còn được gọi là SJF (Shortest Job First) và là một thuật toán không ưu tiên (non-preemptive). Mỗi khi một tiến trình mới đến, hệ thống sẽ chọn tiến trình có thời gian thực thi ngắn nhất để thực hiện tiếp theo.
    *__Ưu điểm__: Giảm thời gian chờ trung bình, vì các tiến trình ngắn sẽ được ưu tiên hoàn thành sớm.
    *__Nhược điểm__: Không phù hợp cho hệ thống có nhiều tiến trình ngắn xen kẽ tiến trình dài (dễ dẫn tới starvation), và khó áp dụng nếu không biết trước thời gian thực thi của mỗi tiến trình.
---
#SRT (Shortest Remaining Time):

    *SRT là phiên bản ưu tiên (preemptive) của SJN. Hệ thống luôn chọn tiến trình có thời gian còn lại ngắn nhất. Nếu một tiến trình mới có thời gian thực thi ngắn hơn so với thời gian còn lại của tiến trình đang chạy, hệ thống sẽ dừng tiến trình hiện tại và chuyển sang tiến trình mới.
    *__Ưu điểm__: Tối ưu thời gian hoàn thành trung bình, xử lý tốt hơn các tiến trình ngắn.
    *__Nhược điểm__: Giống như SJN, SRT có thể gây starvation cho các tiến trình dài, vì các tiến trình ngắn luôn được ưu tiên.
---
#EDF (Earliest Deadline First):

    *EDF là một thuật toán lập lịch ưu tiên động (dynamic priority scheduling) phổ biến trong hệ thống thời gian thực. Hệ thống sẽ luôn chọn tiến trình có thời hạn (deadline) sớm nhất để chạy trước.
    *__Ưu điểm__: Đảm bảo hoàn thành tiến trình đúng thời gian nếu có đủ tài nguyên, do đó thích hợp cho các hệ thống thời gian thực.
    *__Nhược điểm__: Khó dự đoán và tính toán trong môi trường đa nhiệm, có thể gây quá tải hệ thống nếu có nhiều tiến trình cạnh tranh với các deadline sát nhau.