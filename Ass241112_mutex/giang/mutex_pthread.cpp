/**
 * Viết chương trình C với yêu cầu sau:
 * - Process mẹ tạo vùng nhớ dùng chung cho một struct{int x, y, z}
 * Su dung mutex de dong bo hoa hai tien trinh nhu sau:
 * - Process me tao 1 khoa mutex sau do khoa lai
 * - Tao thread con va thread do se bi block
 * - Process me do gia tri x,y tu ban phim sau cho mo khoa va pthread_join thread con
 * - Thread sau do duoc  chay thuc hien z=x+y
 * - sau do no ket thuc
 * - sau do process me in ra z,  xoa khoa mutex va thoat chuong trinh
 */