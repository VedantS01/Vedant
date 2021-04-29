%include "io.mac"
%define BUF_SIZE 256

.DATA
    in_prompt               db          "Enter the input 32 bit number: ",0
    is_not_prime            dw          1
    is_prime                dw          0
    parent_msg              db          "THIS IS PARENT",10,0
    child_msg               db          "THIS IS CHILD",10,0
    file_name               db          "input.txt",0

.UDATA
    in_file_name            resb        30
    out_file_name           resb        30
    fd                      resd        1
    in_buf                  resd        1
    rev                     resd        1
    prime_result            resd        1
    string_buffer           resb        10
    temp                    resd        1
    mmap_address            resb        256

.CODE
    .STARTUP
    PutStr                  in_prompt
    GetLInt                 [in_buf]
    ;test
    ;jmp                     child
    ;end_test

    mov                     eax,8
    mov                     ebx,file_name
    mov                     ecx,0
    mov                     edx,0q0777
    int                     0x80
    mov                     [fd],eax
    cmp                     eax,0
    jge                     write_in_file
    jmp                     done

;done
write_in_file:
    mov                     eax,[in_buf]
    mov                     esi,string_buffer
    call                    int_to_string
    mov                     ecx,eax
    mov                     edx,30
    mov                     ebx,[fd]
    ;mov                     ecx, in_buf
    mov                     eax,4
    int                     0x80
    ;jmp                     mmap

mmap:
    mov                     ebx, mmap_address      ;address
    mov                     ecx, 256   ;size
    mov                     edx, 0q777    ;protection
    mov                     esi, 0x22   ;flags
    mov                     edi, [fd]   ;fd
    mov                     ebp, 0      ;offset
    mov                     eax, 0x5a
    int                     0x80
    ;PutStr                  mmap_address
    ;nwln
    ;return to main code block
    ;jmp                     fork

fork:
    mov                     eax, 2
    int                     0x80
    cmp                     eax,0
    je                      child

parent:
    ;PutStr                  parent_msg
    pushad
    mov                     eax, [in_buf]
    mov                     ebx, 10
    xor                     ecx,ecx
repeat:
    cmp                     eax,0
    je                      end
    xor                     edx,edx
    div                     ebx 
    imul                    ecx,ebx
    add                     ecx,edx
    jmp                     repeat
end:
    ;return
    mov                     [rev],ecx
    popad
    jmp                     close_exit      

child:
    ;PutStr                  child_msg
    pushad
    mov                     eax, [in_buf]
    mov                     ecx, 2
repeatc:
    cmp                     ecx,eax
    jge                     endc
    xor                     edx,edx
    mov                     ebx,eax
    div                     ecx
    cmp                     edx, 0
    je                      composite
    mov                     eax, ebx
    inc                     ecx
    jmp                     repeatc
endc:
    mov                     eax,0
    mov                     [prime_result],eax
    ;PutInt                  [is_prime]
    jmp                     done
composite:
    mov                     eax,1
    mov                     [prime_result],eax
    ;PutInt                  [is_not_prime]
    jmp                     done

close_exit:
    mov                     eax,6
    mov                     ebx,[fd]
    int                     0x80
wait_t:
    mov                     eax,7
    mov                     ebx,0
    int                     0x80
    cmp                     eax,0
    jge                     wait_t

    
    PutLInt                 [prime_result]
    nwln
    PutLInt                 [rev]
    nwln
done:
    .EXIT



; Input:
; eax = integer value to convert
; esi = pointer to buffer to store the string in (must have room for at least 10 bytes)
; Output:
; eax = pointer to the first character of the generated string
; ecx = length of the generated string
int_to_string:
  add esi,9
  mov byte [esi],0    ; String terminator

  mov ebx,10
.next_digit:
  xor edx,edx         ; Clear edx prior to dividing edx:eax by ebx
  div ebx             ; eax /= 10
  add dl,'0'          ; Convert the remainder to ASCII 
  dec esi             ; store characters in reverse order
  mov byte[esi],dl
  test eax,eax            
  jnz .next_digit     ; Repeat until eax==0

  ; return a pointer to the first digit (not necessarily the start of the provided buffer)
  mov eax,esi
  ret






