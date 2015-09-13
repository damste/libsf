; errors.asp

; FDC error codes
_FDC_INVALID_PARAMETERS         EQU 1
_FDC_SEEK_FAILED                EQU 2
_FDC_TIMEOUT                    EQU 3
_FDC_INVALID_DRIVE              EQU 4
_FDC_UNKNOWN_DRIVE_TYPE         EQU 5
_FDC_INVALID_MEDIA              EQU 6
_FDC_SECTOR_NOT_FOUND           EQU 7


; DISK error codes
_DISK_INVALID_DRIVE             EQU 1
_DISK_INVALID_REQUEST           EQU 2
_DISK_INVALID_PARAMETERS        EQU 3


; Requestor error codes, general
_RQ_UNKNOWN_REQUEST             EQU 1


; Requestor error codes, specific
_RQ_iDISK_DRIVE_NOT_FOUND       EQU 1000


; OBJECT system error codes
_TASK_NOT_FOUND                 EQU 0
_OBJECT_NOT_FOUND               EQU 1
_UNKNOWN_OBJECT_TYPE            EQU 2
_UNKNOWN_OBJECT_PROPERTY        EQU 3
_UNKNOWN_OBJECT_EVENT           EQU 4