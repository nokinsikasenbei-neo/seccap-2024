section .data
    input_filename db 'flag.txt', 0            ; フラグが含まれるファイル名
    output_filename db 'encrypted_flag.txt', 0 ; 暗号化後のフラグを保存するファイル名
    buffer times 64 db 0                       ; フラグを格納するバッファ
    shift_value db 3                           ; シフト値
    err_msg db 'Error: FLAG not found.', 0xA   ; エラーメッセージ
    err_len equ $-err_msg                      ; エラーメッセージの長さ

section .bss
    fd_in resq 1                               ; 入力ファイルディスクリプタ
    fd_out resq 1                              ; 出力ファイルディスクリプタ
    buffer_length resq 1

section .text
    global _start

_start:
    ; 入力ファイルをオープン (sys_open)
    mov rax, 2                                 ; sys_open (64bit)
    lea rdi, [input_filename]                  ; ファイル名
    xor rsi, rsi                               ; O_RDONLY モード
    syscall                                    ; システムコール呼び出し
    mov [fd_in], rax                           ; ファイルディスクリプタを保存
    test rax, rax                              ; rax と 0 を比較
    js file_open_error                         ; もし rax が負の値ならエラー処理

    ; フラグをファイルから読み込む (sys_read)
    mov rax, 0                                 ; sys_read
    mov rdi, [fd_in]                           ; ファイルディスクリプタ
    lea rsi, [buffer]                          ; バッファ
    mov rdx, 64                                ; 読み込むバイト数
    syscall                                    ; システムコール呼び出し

    xor rdi, rdi                               ; インデックスを0に初期化
encrypt_loop:
    mov al, [buffer + rdi]                     ; バッファから1バイト取得
    test al, al                                ; バイトが0（終端）か確認
    jz done                                    ; 終了条件
    add al, [shift_value]                      ; シーザーシフトによる暗号化
    ror al, 1                                  ; 右ローテートシフト
    mov [buffer + rdi], al                     ; 暗号化されたバイトをバッファに戻す
    inc rdi                                    ; インデックスを増加
    jmp encrypt_loop                           ; ループ

done:
    ; 書き込むバイト数を保存
    mov [buffer_length], rdi
    ; 出力ファイルをオープン (sys_open with O_WRONLY | O_CREAT)
    lea rdi, [output_filename]                 ; ファイル名
    mov rsi, 577                               ; O_WRONLY | O_CREAT | O_TRUNC モード
    mov rdx, 0o644                             ; ファイルパーミッション (rw-r--r--)
    mov rax, 2                                 ; sys_open
    syscall                                    ; システムコール呼び出し
    mov [fd_out], rax                          ; ファイルディスクリプタを保存

    ; 暗号化されたフラグをファイルに書き込む (sys_write)
    mov rax, 1                                 ; sys_write
    mov rdi, [fd_out]                          ; ファイルディスクリプタ
    lea rsi, [buffer]                          ; バッファ
    mov rdx, [buffer_length]                   ; 書き込むバイト数
    syscall                                    ; システムコール呼び出し

    ; ファイルをクローズ (sys_close)
    mov rax, 3                                 ; sys_close
    mov rdi, [fd_in]                           ; 入力ファイルディスクリプタ
    syscall                                    ; システムコール呼び出し

    mov rax, 3                                 ; sys_close
    mov rdi, [fd_out]                          ; 出力ファイルディスクリプタ
    syscall                                    ; システムコール呼び出し

    ; プログラム終了 (sys_exit)
    mov rax, 60                                ; sys_exit
    xor rdi, rdi                               ; ステータスコード 0
    syscall                                    ; システムコール呼び出し

file_open_error:
    ; エラーメッセージを出力
    mov rax, 1                                 ; sys_write システムコール番号
    mov rdi, 1                                 ; 標準出力 (fd = 1)
    lea rsi, [err_msg]                         ; エラーメッセージのアドレス
    mov rdx, err_len                           ; エラーメッセージの長さ
    syscall                                    ; システムコール呼び出し

    ; プログラム終了
    mov rax, 60                                ; sys_exit システムコール番号
    mov rdi, 1                                 ; エラー終了コード 1
    syscall                                    ; システムコール呼び出し