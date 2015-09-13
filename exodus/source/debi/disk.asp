; disk.asp
;
; Low-Level Debi Debugger disk-related algorithms
;
;









;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;
; Low-level disk access routines via DT/NP/RP
;
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    iDEBI_open_file         PROC
    ; This routine opens a file by name.
    ;
    ; Upon entry:   ds:[esi] - far ptr to filename
    ;                    ecx - length
    ;
    ; Upon exit:    carry? - CLEAR if opened, SET if error
    ;                  ebx - HANDLE if opened
        ret
    iDEBI_open_file         ENDP




    iDEBI_close_file        PROC
    ; This routine closes a file handle.
    ;
    ; Upon entry:   ebx - handle
    ;               ecx - bytes to read
    ;               edx - starting offset in file
    ;          es:[edi] - far ptr to store read data
    ;
    ; Upon exit:    carry? - CLEAR if read ok, SET if error
    ;
    iDEBI_close_file        ENDP




    iDEBI_read_file         PROC
    ; This routine reads the contents of a file from disk.
    ;
    ; Upon entry:   ebx - handle
    ;               ecx - bytes to read
    ;               edx - starting offset in file
    ;          es:[edi] - far ptr to store read data
    ;
    ; Upon exit:    carry? - CLEAR if read ok, SET if error
    ;
    iDEBI_read_file         ENDP




    iDEBI_write_file        PROC
    ; This routine writes the contents of a file to disk.
    ;
    ; Upon entry:   ebx - handle
    ;               ecx - bytes to write
    ;               edx - starting offset in file
    ;          ds:[esi] - far ptr to write data from
    ;
    ; Upon exit:    carry? - CLEAR if read ok, SET if error
    ;
    iDEBI_write_file        ENDP




    invDEBI_search_file         PROC
    ; This routine finds a file.  It searches the the DT/NP/RP for a match.
    ;
    ; Upon entry:   ds:[esi] - far ptr to filename to find
    ;                    ecx - length
    ;
    ; Upon exit:    carry? - CLEAR if found, SET if error
    ;
        ret
    invDEBI_search_file         ENDP
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;
; Low-level disk access routines via DT/NP/RP
;
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=









;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;
; Internal disk access routines via TRACK/SECTOR/HEAD
;
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    invDEBI_read_sector     PROC
    ; This routine physically reads the contents of a sector
    ;
    ; Upon entry:   es:[edi] - where to store read data
    ;                     cl - track
    ;                     bl - sector
    ;                     al - head
    ;
    ; Upon exit:    carry? - CLEAR if read ok, SET if error
    ;
        ret
    invDEBI_read_sector     ENDP




    invDEBI_write_sector        PROC
    ; This routine physically writes 512 bytes to the contents of a sector
    ;
    ; Upon entry:   ds:[esi] - where to write data from
    ;                     cl - track
    ;                     bl - sector
    ;                     al - head
    ;
    ; Upon exit:    carry? - CLEAR if written ok, SET if error
    ;
        ret
    invDEBI_write_sector        ENDP
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;
; Internal disk access routines via TRACK/SECTOR/HEAD
;
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=