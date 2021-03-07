;;-----------------------------------------------------
;
; CS19B074.asm -- v1.0 -- by Vedant (CS19B074) 
; Objectives: Adding n integers and printing the sum 
; Inputs: 'n' (number of integers) and n integers
; Outputs: prints the sum of the integers on the screen
;
;;-----------------------------------------------------

%include "io.mac"             ;Include the relevant io file
.DATA                         ;Initailized data -- we don't need any, so this is empty

.UDATA                        ;Uninitailized data -- we don't need any, so this is empty

.CODE
    .STARTUP                  ;Setup
    GetInt    CX              ;Get input count in CX register (we want to use loop instruction)
    and    EAX,EAX            ;Empty the AX register
GetTheNumbers:                ;Label -- A do-while loop
    GetInt  DX                ;Store number temporarily in DX register
    add    EAX,EDX            ;Add DX to AX; which contains the running sum
    loop    GetTheNumbers     ;Go back to label GetTheNumbers if there are more numbers, else exit the loop
    PutInt    AX              ;Print the final result
    nwln                      ;New line -- for formatting
    .EXIT                     ;Returns control

;;-----------------------------------------------------
;
; The End Of File -- CS19B074.asm
; Created -- 12:43 PM 2/14/2021
; Last Modified -- 8:37 AM 2/15/2021 by Vedant
;
;;-----------------------------------------------------