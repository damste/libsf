; task_eq.asp
;
; Exodus Task System constant equates
;
;

; Task header constants
_TASK_SYSTEM_NEXT_OFFSET            EQU 0                           ; dword, The next offset within the _sTASK_SYSTEM selector
_TASK_SYSTEM_NEXT_HANDLE            EQU 4                           ; word,  Next handle to use (incremented each task)
_TASK_SYSTEM_CURRENT_TASK_TSS       EQU 6                           ; word,  Currently executing TSS
_TASK_SYSTEM_CURRENT_TASK_OFFSET    EQU 8                           ; dword, Currently executing task offset (in _sTASK_SYSTEM)
_TASK_SYSTEM_TOTAL_ENTRIES_BASE_0   EQU 12                          ; dword, stored as base-0 (so 0 actually means 1)
_TASK_SYSTEM_FOCUS_TASK_OFFSET      EQU 16                          ; dword, task that has focus



_FIRST_TASK_ENTRY                   EQU 64                          ; Offset where the first task record is
; Task structure constants
_TASK_ENTRY_HANDLE                  EQU 0
_TASK_ENTRY_GDT_TSS                 EQU 2
_TASK_ENTRY_GDT_LDT                 EQU 4
_TASK_ENTRY_SELECTOR_OBJECTS        EQU 6
_TASK_ENTRY_FOCUS_BO                EQU 8
_TASK_ENTRY_FOCUS_O                 EQU 12
_TASK_ENTRY_TICKS                   EQU 16
_TASK_ENTRY_MODE                    EQU 17
_TASK_ENTRY_USES_FPU                EQU 18
_TASK_ENTRY_TSS_LINEAR_OFFSET       EQU 20
_TASK_ENTRY_TICKS_LEFT              EQU 24

;;----------
;; * NOTE *
;;
_TASK_ENTRY_LENGTH                  EQU 64
;; * NOTE *  If this value changes, the algorithm in invTASK_switch_task() [bios\tasks.asp] must be changed as well.
;;           Presently it uses a SHR x,6 to divide by 64.  If the number changes it must be put into a DIV instruction
;;----------



; Constants used for set-bit meanings
; Refer to INF\TASK.INF for more information
_SUSPENDED                          EQU 10000000b
_IDLE                               EQU  1000000b
_READ_EVENTS                        EQU   100000b
_SLAVE                              EQU       10b
_LINEAR                             EQU        1b


; Constants used for mouse events and task scheduling
_LEFT_SINGLE_CLICK          EQU 0
_LEFT_DOUBLE_CLICK          EQU 1
_LEFT_DRAG_START            EQU 2
_LEFT_DRAG_STOP             EQU 3
_RIGHT_SINGLE_CLICK         EQU 4
_RIGHT_DOUBLE_CLICK         EQU 5
_RIGHT_DRAG_START           EQU 6
_RIGHT_DRAG_STOP            EQU 7
_BOTH_SINGLE_CLICK          EQU 8
_BOTH_DOUBLE_CLICK          EQU 9
_HOVER                      EQU 10
_ABANDON_IF_NOT             EQU 11
_ANY_CLICK                  EQU 12
_IMMEDIATE                  EQU 13