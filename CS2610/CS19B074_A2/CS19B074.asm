;;-----------------------------------------------------
;
; CS19B074.asm -- v 1.0 -- by Vedant (CS19B074) 
; Objectives: Encoding a text of n characters 
; Inputs: 'n' (length of string) followed by string characters 
; Outputs: prints the encoded string
;
;;-----------------------------------------------------

; NAIVE SOLUTION IN PROGRESS

%include "io.mac"                   ;Include the relevant io file
%include "encode.mac"               ;Include the file encode.mac - that contains the encoding procedure
BUFFER_LEN              equ     20
.DATA                               ;Initailized data -- we don't need any, so this is empty
    prompt_msg          db      "Enter the string to be encrypted here :",10,0
    prompt_re           db      "Do you want to continue encrypting a new string? (Y/n)",10,0
    Y_char              db      "Y"
    y_char              db      "y"
    answer_msg          db      "Your encrypted string is:",10,0
.UDATA                              ;Uninitailized data -- string and the nunber of elements
    string:     resb    BUFFER_LEN
.CODE
    .STARTUP                        ;Setup
BeginNewEncoding:                   ;Begins the encoding process
    PutStr      prompt_msg          ;Prompt user to input a string
    xor         EAX,EAX             ;Empty the AX register
    GetStr      string, BUFFER_LEN
    mov         EBX, string         ;pointer to the array starting address
LoopEncode:                         ;Label -- A do-while loop
    mov         AL, [EBX]           ;Get the byte in AL
    cmp         AL, 0               ;compare with end of string characcter (null character)
    je          LoopExit            ;jump if end of string
    Encode                          ;Encode
    mov         [EBX], AL           ;Move encoded byte back in the memory
    inc         EBX                 ;Increment index register
    jmp         LoopEncode          ;Go back to label GetTheNumbers if there are more numbers, else exit the loop
LoopExit:
    PutStr      answer_msg          ;Print the answer message
    PutStr      string              ;Print the final result
    nwln                            ;New line -- for formatting
    nwln                            ;New line -- for formatting
    PutStr      prompt_re           ;prompt to ask for resetting the program
    GetCh       AL                  ;get response character ascii in AL
    cmp         AL, byte[Y_char]    ;compare with Y
    je          BeginNewEncoding    ;go to starting point
    cmp         AL, byte[y_char]    ;compare with Y
    je          BeginNewEncoding    ;go to starting point
    .EXIT                           ;Returns control

;;-----------------------------------------------------
;
; The End Of File -- CS19B074.asm
; Created -- 12:39 PM 2/20/2021
; Last Modified -- 12:39 PM 2/20/2021 by Vedant
;
;;-----------------------------------------------------