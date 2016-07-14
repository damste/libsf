Feb.29.2016
-----------

Support and modification to Exodus to provide API-level support for
IBM's published OS/2.  It will be called ES/2 for short.

Jul.14.2016 -- ES/2 will guarantee memory allocation.  If it fails,
the task will be suspended where it is until resources can be freed.
Legacy support will also be given for memory allocation which can
fail, and will need to have NULL pointer tests performed.

Best regards,
Rick C. Hodgin

