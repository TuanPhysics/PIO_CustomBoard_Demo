# Custom board demo in PlatformIO 

Repo này chứa mã chạy thử code blink (một dạng hello world trong thế giới nhúng) trên board phát triển ESP32-C3 Super Mini.

## Đặt vấn đề 

Board `ESP32-C3 Super Mini` là một board có kích thước siêu nhỏ, tối giản, giá thành thấp nhất trong các board đang có trên thị trường. Tôi mua trên shopee ở thời điểm hiện tại giá chưa tới 50k một board. 
Cơ bản thì board này dựa trên phần cứng như sau:

- Con chip ESP32-C3 (RISCV single core) mã `ESP32-C3FH4`, mã này là một biến thể trong dòng ESP32-C3 mà nó tích hợp sẵn bộ nhớ flash 4M đóng gói vào con chip, cho nên nó khá nhỏ gọn (Tham khảo: ESP32-C3 datasheet từ Espressif).
- Dùng ăng ten gốm: nhỏ gọn hơn so với ăng ten mạch in, nhưng nhược điểm là độ mạnh tín hiệu và độ nhạy theo các phương không đồng đều như ăng ten mạch in (tham khảo Espressif, sách IoT Comprehensive, phần so sánh các thiết kế ăng ten). 
- Có cổng type-C trên board mạch. Cổng USB này là giao tiếp trực tiếp với chip thông qua giao thức USB Serial/JTAG tích hợp sẵn trong chip mà không cần qua cầu nối USB-to-UART, giúp hạ giá thành board mạch. Tuy nhiên các công cụ phát triển hỗ trợ giao thức này là mới mẻ so với truyền thống, và cần bỏ thời gian đọc và thử nghiệm một chút. 

Vấn đề của bảng mạch này trên PIO:
- Trong PIO không thể tìm được tên chính thức của board này (lệnh `pio boards`, hoặc dùng giao diện PIO trên VScode) --> gây bối rối cho người dùng. Một số người cố tìm một board có trong danh sách mà có thiết kế gần với board này nhất, tuy nhiên đây không phải giải pháp tối ưu. 

Trong repo này tôi demo cách tạo ra một board của người dùng cho chính board này mà không phụ thuộc vào board có trong danh sách sẵn của PIO. 

## Giải pháp

- PIO có cung cấp cách tạo ra một custom board cho người dùng, vì nó là mã mở nên thực ra ai cũng có thể tạo ra board của mình và đóng góp vào board list trên PIO. 
- Tài liệu hướng dẫn tạo board: https://docs.platformio.org/en/stable/platforms/creating_board.html 

Thực chất:
- Việc tạo board này chính là tạo một file `ESP32-C3-Super-Mini.json` trong thư mục `boards` bên trong thư mục chứa dự án của người dùng (cùng thư mục chủ với file README này).
- Cấu trúc trong file json tuân theo hướng dẫn của PIO như link trên. 
- Để cho nhanh ta có thể thao khảo file boards của hai board phát triển gần giống (sử dụng cùng biến thể chip, và cũng sử dụng trực tiếp USB CDC để nạp và giao tiếp UART):
    + https://github.com/platformio/platform-espressif32/blob/develop/boards/lolin_c3_mini.json 
    + https://github.com/pioarduino/platform-espressif32/blob/develop/boards/adafruit_qtpy_esp32c3.json 

## Thử nghiệm (Test) 

- Viết mã blink và hello world như trong `src/main.cpp`
- Bấm nút biên dịch và nạp (Build --> Upload) trên PIO/VSC
- Bấm monitor --> thấy các thông điệp in ra qua cổng USB (ttyACM0 hoặc ttyACM1 trên Linux, trên Windows là một COMx nào đó). 

Nếu quá trình trên trơn chu và không cần phải bấm tổ hợp phím "giữ Boot --> bấm Restart" thì là ta đã thành công. 

## Thêm 

- Để có thể search board mới tạo trên PIO Home (hoặc `pio boards` list) thì thêm file json vừa nhắc vào `~/.platformio/platforms/espressif32/boards/`
- Để có thể định nghĩa cụ thể các chân custom trên board mới như: Built in LEDs, Bult in buttons, thì làm file `pins_arduino.h` và thêm vào `~/.platformio/packages/framework-arduinoespressif32/variants/super_mini_esp32c3/pins_arduino.h`. Tham khảo chi tiết: https://github.com/sigmdel/supermini_esp32c3_sketches/blob/main/resources/README.md