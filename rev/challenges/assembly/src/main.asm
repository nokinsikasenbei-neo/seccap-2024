section .data
    input_filename db 'flag.txt', 0            ; フラグが含まれるファイル名
    output_filename db 'encrypted_flag.txt', 0 ; 暗号化後のフラグを保存するファイル名
    buffer times 64 db 0                       ; フラグを格納するバッファ
    shift_value db 3                           ; シフト値
    err_msg db 'Error: FLAG not found.', 0xA ; エラーメッセージ
    err_len equ $-err_msg                    ; エラーメッセージの長さ

section .bss
    fd_in resd 1                               ; 入力ファイルディスクリプタ
    fd_out resd 1                              ; 出力ファイルディスクリプタ

section .text
    global _start

_start:
    ; 入力ファイルをオープン (sys_open)
    mov eax, 5                                 ; sys_open
    mov ebx, input_filename                    ; ファイル名
    mov ecx, 0                                 ; O_RDONLY モード
    int 0x80                                   ; システムコール呼び出し
    mov [fd_in], eax                           ; ファイルディスクリプタを保存
    cmp eax, 0                                  ; eax と 0 を比較
    jl file_open_error                          ; もし eax が負の値ならエラー処理

    ; フラグをファイルから読み込む (sys_read)
    mov eax, 3                                 ; sys_read
    mov ebx, [fd_in]                           ; ファイルディスクリプタ
    lea ecx, [buffer]                          ; バッファ
    mov edx, 64                                ; 読み込むバイト数
    int 0x80                                   ; システムコール呼び出し

    xor edi, edi                               ; インデックスを0に初期化
encrypt_loop:
    mov al, [buffer + edi]                     ; バッファから1バイト取得
    test al, al                                ; バイトが0（終端）か確認
    jz done                                    ; 終了条件
    add al, [shift_value]                      ; シーザーシフトによる暗号化
    ror al, 1                                  ; 右ローテートシフト
    mov [buffer + edi], al                     ; 暗号化されたバイトをバッファに戻す
    inc edi                                    ; インデックスを増加
    jmp encrypt_loop                           ; ループ

done:
    ; 出力ファイルをオープン (sys_open with O_WRONLY | O_CREAT)
    mov eax, 5                                 ; sys_open
    mov ebx, output_filename                   ; ファイル名
    mov ecx, 65                               ; O_WRONLY | O_CREAT | O_TRUNC モード
    mov edx, 64*6+8*4+4                              ; ファイルパーミッション (rw-r--r--)
    int 0x80                                   ; システムコール呼び出し
    mov [fd_out], eax                          ; ファイルディスクリプタを保存

    ; 暗号化されたフラグをファイルに書き込む (sys_write)
    mov eax, 4                                 ; sys_write
    mov ebx, [fd_out]                          ; ファイルディスクリプタ
    lea ecx, [buffer]                          ; バッファ
    mov edx, edi                               ; 書き込むバイト数
    int 0x80                                   ; システムコール呼び出し

    ; ファイルをクローズ (sys_close)
    mov eax, 6                                 ; sys_close
    mov ebx, [fd_in]                           ; 入力ファイルディスクリプタ
    int 0x80                                   ; システムコール呼び出し

    mov eax, 6                                 ; sys_close
    mov ebx, [fd_out]                          ; 出力ファイルディスクリプタ
    int 0x80                                   ; システムコール呼び出し

    ; プログラム終了 (sys_exit)
    mov eax, 1                                 ; sys_exit
    xor ebx, ebx                               ; ステータスコード 0
    int 0x80                                   ; システムコール呼び出し

file_open_error:
    ; エラーメッセージを出力
    mov eax, 4                              ; sys_write システムコール番号
    mov ebx, 1                              ; 標準出力 (fd = 1)
    mov ecx, err_msg                        ; エラーメッセージのアドレス
    mov edx, err_len                        ; エラーメッセージの長さ
    int 0x80                                ; システムコール呼び出し

    ; プログラム終了
    mov eax, 1                              ; sys_exit システムコール番号
    mov ebx, 1                              ; エラー終了コード 1
    int 0x80                                ; システムコール呼び出し