;;-----------------------------------------------------
;
; CS19B074.asm -- v1.0 -- by Vedant (CS19B074) 
; Objectives: Binary searching an element in a number of elements 
; Inputs: number of elements 'n', n elements and the element to be searched
; Outputs: prints 1 if the element is found, else prints 0
;
;;-----------------------------------------------------     

%include "io.mac"
.DATA
    prompt_msg          db              "Enter the size of the array : ",0
    search_query_msg    db              "Enter the element to be searched : ",0
    prompt_array_msg    db              "Please enter ",0
    prompt_array_msg_2  db              " each on a next line.",10,0
    found_msg           db              "The element was found.",10,0
    not_found_msg       db              "The element was not found.",10,0
    terminate_msg       db              "Do you want to terminate the program (Y/n)",10,0
    Y_char              db              "Y"
    y_char              db              "y"
    result_msg          db              "Result of the binary search is : ",0
.UDATA
    BUF_LEN         equ         30
    WORD_LEN        equ         4  
    array:          resd        BUF_LEN ; 4 * BUF_LEN space allocated starting from array
.CODE
.STARTUP
    PutStr          prompt_msg          ; input prompt message
    GetLInt         ECX                 ; get the size of array in ecx register

    PutStr          prompt_array_msg    ; prompt for getting array elements
    PutLInt         ECX
    PutStr          prompt_array_msg_2
    call            GetArrayElements    ; get all elements of the array in locations starting from "array"

begin_program:
    PutStr          search_query_msg    ; prompt for getting query to search for
    GetLInt         EDX                 ; get the number to be found in edx register

    call            binary_search       ; call binary search procedure
    PutStr          result_msg          ; result message
    PutLInt         EAX                 ; Print EAX
    nwln
    cmp             EAX,1               ; compare result of bianry search with 1
    jne             else                ; if eax is not one, jump to else part
    PutStr          found_msg           ; if eax is 1, print found message
    jmp             end                 ; jump to end 
else:                                   ; else label
    PutStr          not_found_msg       ; if eax is not 1, ie. 0, print not found message
end:                                    ; end label

    PutStr          terminate_msg       ; print terminate message
    GetCh           AL                  ; get the response character in AL register
    cmp             AL,byte[Y_char]     ; compare response character with 'Y'
    je              exit_program        ; jump if equal to exit
    cmp             AL,byte[y_char]     ; compare response character with 'y'
    je              exit_program        ; jump if equal to exit
    jmp             begin_program

exit_program:
.EXIT                                   ; exit the program

;;------------------------------------
; binary_search     --      performs binary search
; args              --      'array' is the starting address of the array and ecx stores the count while edx stores the query     
; returns           --      eax contains 1 or 0 depending on success of finding, or failure respectively
;
; NOTE              --      using this will trash the eax contents, so save the eax before calling this procedure
;;------------------------------------
binary_search:
    ;pushad                              ; save all 32 bit registers
    push            ESI
    push            EDI
    push            EBX     
    mov             EBX,array           ; starting address of the array
    mov             ESI,0               ; this will point to the beg
    mov             EDI,ECX             ; this will point to the end + 1
    dec             EDI                 ; now this points to end

loop_begin:
    cmp             ESI,EDI             ; compare starts and ends of lokking block
    jg              not_found           ; if start is greater than end, element is not found

    mov             EAX,ESI
    add             EAX,EDI             ; calculation of mid ... (1)
    shr             EAX,1               ; calculation of mid ... (2) ...done
    cmp             EDX,[EBX+EAX*WORD_LEN]  ; compare array[mid] with search query
    je              found               ; jump if equal to found block
    cmp             EDX,[EBX+EAX*WORD_LEN]  ; compare array[mid] with search query
    jl              less                ; jump if less than to less block

    ;; value to be is greater than array of mid
    mov             ESI,EAX             ; change the start of looking block to mid       
    inc             ESI                 ; change the start of looking block to mid minus 1
    jmp             loop_begin          ; start search in the new reduced block

less:
    mov             EDI,EAX             ; change the end of looking block to mid
    dec             EDI                 ; change the end of looking block to mid minus 1
    jmp             loop_begin          ; ; start search in the new reduced block

    ;; Element is not found
not_found:
    mov             EAX,0               ; store result of 0 to eax
    jmp             return              ; go to return

    ;; Element is found
found:
    mov             EAX,1               ; store result of 1 to eax

return:
    pop             EBX                 ; restore ebx
    pop             EDI                 ; restore edi
    pop             ESI                 ; restore esi
    ;popad                               ; restore all 32 bit registers
    ret                                 ; return to main program


;;------------------------------------
; GetArrayElements -- get all elements in the memory location starting from label "array"
; args      --      [EDX] number of elements from STDIN
; returns   --      stores each of the element
;;------------------------------------
GetArrayElements:
    push            EBX                 ; save ebx
    push            ECX                 ; save ecx
    mov             EBX,array           ; store starting address of array in ebx
    cmp             ECX,0               ; compare count with 0
    jle             return_get_array    ; if count is 0 or negative (an error entry) return
begin_get_array:             
    GetLInt         [EBX]               ; get a 4 byte number in address pointed to by ebx
    add             EBX,WORD_LEN        ; increment ebx to next address by incrementing by word length
    dec             ECX                 ; decrease the count
    jnz             begin_get_array     ; if count is not zero, repeat
return_get_array:
    pop             ECX                 ; restore ecx
    pop             EBX                 ; restore ebx
    ret                                 ; return to main program





;;-----------------------------------------------------
;
; The End Of File   --      CS19B074.asm
; Created           --      9:19 PM 3/5/2021
; Last Modified     --      2:32 PM 3/5/2021 by Vedant
;
;;-----------------------------------------------------