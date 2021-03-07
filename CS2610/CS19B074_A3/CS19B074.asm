;;-----------------------------------------------------
;
; CS19B074.asm -- v1.0 -- by Vedant (CS19B074) 
; Objectives: Computing nth Fibonacci number and time calculation 
; Inputs: 'n' (number of integers) and n integers
; Outputs: prints the sum of the integers on the screen
;
; Last Modified: 09:49 AM 3/4/2021 by Vedant
;
;;-----------------------------------------------------     

%include "io.mac"
.DATA
    prompt_msg          db              "Enter a positive number greater than 1 : ",0
    fib_iter_msg        db              "By iterative process, the fibonacci number is : ",0
    fib_recur_msg       db              "By recursive process, the fibonacci number is : ",0
    time_stamp_msg      db              "Current time stamp, in terms of clock cycles := ",10,0
    cycles_iter_msg     db              "Clock cycles taken in iterative process = ",0
    cycles_recur_msg    db              "Clock cycles taken in recursive process = ",0
.UDATA
    counter:        resd     2          ; 8 byte space to hold time stamp information during the program execution
.CODE
.STARTUP
    PutStr          prompt_msg          ; input prompt message
    GetLInt         EDX                 ; get the number in edx register
    
    ;;      reading time stamp
    pushad                              ; save registers on stack
    rdtscp                              ; this loads time stamp information in edx:eax
    mov             [counter], eax      ; store lower order bits 
    mov             [counter+4], edx    ; store higher order bits
    popad                               ; restore register contents

    call fibonacci_iterative            ; call iterative procedure to compute nth fibonacci number

    ;;      reading time stamp
    pushad                              ; save registers on stack
    rdtscp                              ; this loads time stamp information in edx:eax
    sub             eax, [counter]      ; store lower order bits difference of previous and current time stamps in eax
    jnc             next                ; if there is carry in lower 4 bytes, dec edx by one to accomodate borrow
    dec             edx                             
next:
    sub             edx, [counter+4]    ; store higher order bits difference of previous and current time stamps in eax
    PutStr          cycles_iter_msg     ; print message
    PutLInt         edx                 ; print number of cycles higher order bits
    PutLInt         eax                 ; print number of cycles lower order bits
    popad                               ; restore register contents

    nwln                                ; new line, for formatting
    PutStr          fib_iter_msg        ; print result of fibonacci
    PutLInt         EAX                 ; print the result
    nwln

    ;;      reading time stamp
    pushad                              ; save registers on stack
    rdtscp                              ; this loads time stamp information in edx:eax
    mov             [counter], eax      ; store lower order bits 
    mov             [counter+4], edx    ; store higher order bits
    popad                               ; restore register contents

    push            EDX                 ; pass argument for recursive fibonacci by pushing it on stack
    call            fibonacci_recursive ; call recursive fibonacci

    ;;      reading time stamp
    pushad                              ; save registers on stack
    rdtscp                              ; this loads time stamp information in edx:eax
    sub             eax, [counter]      ; store lower order bits difference of previous and current time stamps in eax
    jnc             next2               ; if there is carry in lower 4 bytes, dec edx by one to accomodate borrow
    dec             edx                             
next2:
    sub             edx, [counter+4]    ; store higher order bits difference of previous and current time stamps in eax
    PutStr          cycles_recur_msg    ; print message
    PutLInt         edx                 ; print number of cycles higher order bits
    PutLInt         eax                 ; print number of cycles lower order bits
    popad                               ; restore register contents

    nwln                                ; for formatting

    PutStr          fib_recur_msg       ; print result message
    PutLInt         EAX                 ; print result 
    nwln                                ; for formating

.EXIT                                   ; exit the program

;;------------------------------------
; fibonacci_iterative -- computes nth fibonacci number
; args      --      register edx must hold n
; returns   --      resgiter eax will hold the final result
; temporary usage for register ebx, we save it on stack
;;------------------------------------
%define     LOWER_VAL     dword       [EBP-4]
%define     HIGHER_VAL    dword       [EBP-8]
fibonacci_iterative:
    enter           8,0                 ; prepare for stack, store ebp, decrement esp by 8 bytes to create extra space for 2 4 byte data
    push            EBX                 ; save ebx                    
    push            EDX                 ; save edx
    mov             LOWER_VAL,0         ; intialise LOWER_VAL 
    mov             HIGHER_VAL,1        ; initialise HIGHER_VAL

fib_loop:                               ; loop beginning label
    mov             EAX,HIGHER_VAL      ; get higher value in eax
    mov             EBX,LOWER_VAL       ; get lower value in ebx
    add             EBX,EAX             ; add higher value to lower
    mov             LOWER_VAL,EAX       ; store higher value (now lower) in its place
    mov             HIGHER_VAL,EBX      ; store the sum (now higher) in its place
    dec             EDX                 ; decrement count
    jnz             fib_loop            ; if zero, required count achieved, break; 
                                        ; eax now contains the nth fibonacci number
    pop             EDX                 ; restore edx
    pop             EBX                 ; restore ebx
    leave                               ; leave, restoring values of ebp and bringing esp back to its origional value before entering
    ret                                 ; return to main program

;;------------------------------------
; fibonacci_recursive -- computes nth fibonacci number
; args      --      operand n is in stack
; returns   --      register eax will hold the final result
; temporary usage for register ebx, we save it on stack
;;------------------------------------
%define         N       dword       [EBP+8]
%define         Temp    dword       [EBP-4]
fibonacci_recursive:
    enter           4,0                 ; prepare for stack, create extra space of 4 bytes for temporary variable
    cmp             N,0                 ; if n is 0, simply return
    jne             else_if             ; if not zero, jump to else if part
    mov             EAX,0               ; n = 0 => eax = 0
    leave                               ; leave and return, popping 4 space
    ret             4                   ; 4 bytes operand needs to be released from the stack
else_if:
    cmp             N,1                 ; if n = 1, ret 1
    jne             else                ; if n > 1, jump to else 
    mov             EAX,1               ; n = 1 -> eax = 1
    leave                               ; leave and return, popping the 4 extra space
    ret             4                   ; 4 bytes released to clear the operand from the stack
else:                                   
    push            EBX                 ; save ebx
    mov             EBX,N               ; mov operand to ebx
    dec             EBX                 ; decrease operand by 1
    push            EBX                 ; push operand for recursive call 
    call            fibonacci_recursive ; recursive call
    mov             Temp,EAX            ; store result of the recursive call in temporary location on stack
    dec             EBX                 ; decrease by 1
    push            EBX                 ; push operand for recursive call
    call            fibonacci_recursive ; recursive call
    add             EAX,Temp            ; add results of both recursive call
    pop             EBX                 ; restore ebx
    leave                               ; leave , moving 4 bytes back on the stack
    ret             4                   ; release the 4 byte operand from the stack
    





;;-----------------------------------------------------
;
; The End Of File -- CS19B074.asm
; Created -- 12:43 PM 2/14/2021
; Last Modified -- 8:37 AM 2/15/2021 by Vedant
;
;;-----------------------------------------------------