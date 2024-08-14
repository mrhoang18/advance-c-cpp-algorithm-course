BÀI 1: COMPILER-MACRO

IDE-Integrated Development Environment là môi trường để viết code hỗ trợ các tính năng như Compiler, Debugger. 

Text Editor là một trình soạn thảo (Ví dụ: Notepad++, VScode,...) không tích hợp sẵn trình biên dịch, muốn chạy được code phải dùng riêng Compiler bên ngoài với C/C++ thường là GCC/G++. 

Compiler (trình biên dịch) là chương trình có nhiệm vụ xử lý chương trình ngôn ngữ bậc cao (C/C++, Python,...) thành ngôn ngữ bậc thấp hơn để máy tính thực thi (thường là ngôn ngữ máy).

Quá trình biên dịch gồm các giai đoạn như sau:

<img src="https://github.com/user-attachments/assets/68c4be2c-ee5b-41ab-9aeb-bd986aac8a4f" alt="Compiler Macro" width="500">

+ Giai đoạn Preprocessor (Tiền xử lý): thực hiện nhận source code (bao gồm các file: .c,.h,.cpp,.hpp,...), xóa bỏ comment và xử lý các chỉ thị tiền xử lý và đầu ra là file .i.
  
+ Giai đoạn Compiler: chuyển từ ngôn ngữ bậc cao sang ngôn ngữ bậc thấp assembly, đầu vào là file .i đầu ra là file .s.
  
+ Giai đoạn Assembler: dịch chương trình sang mã máy 0 và 1, đầu vào là file .s đầu ra là file .o hay còn gọi là file Object.
  
+ Giai đoạn Linker: liên kết các file Object .0 lại thành một chương trình duy nhất 





