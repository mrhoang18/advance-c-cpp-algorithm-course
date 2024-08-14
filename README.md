BÀI 1: COMPILER-MACRO

Compiler (trình biên dịch) là quá trình xử lý chương trình từ ngôn ngữ bậc cao thành ngôn ngữ bậc thấp để máy tính thực thi.

<img src="https://github.com/user-attachments/assets/68c4be2c-ee5b-41ab-9aeb-bd986aac8a4f" alt="Compiler Macro" width="500">

Quá trình này bao gồm các giai đoạn:

+ Giai đoạn Preprocessor (Tiền xử lý): thực hiện nhận source code (bao gồm các file: .c,.h,.cpp,.hpp,...), xóa bỏ comment và xử lý các chỉ thị tiền xử lý và đầu ra là file .i.
  
+ Giai đoạn Compiler: chuyển từ ngôn ngữ bậc cao sang ngôn ngữ bậc thấp assembly, đầu vào là file .i đầu ra là file .s.
  
+ Giai đoạn Assembler: dịch chương trình sang mã máy 0 và 1, đầu vào là file .s đầu ra là file .o hay còn gọi là file Object.
  
+ Giai đoạn Linker: liên kết các file Object .0 lại thành một chương trình duy nhất 





