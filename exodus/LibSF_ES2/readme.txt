Feb.29.2016
-----------

Support and modification to Exodus to provide API-level support for
IBM's published OS/2.  It will be called ES/2 for short.

Jul.14.2016 -- ES/2 will guarantee memory allocation.  If it fails,
the task will be suspended where it is until resources can be freed.
Legacy support will also be given for memory allocation which can
fail, and will need to have NULL pointer tests performed.

Jul.14.2016 -- ES/2 will bring back functionality of the pause button.
It will suspend the current task if it's suspendable (as by protocol
with the OS), and if not it will suspend all screen output even as it
continues to run in the background.

Best regards,
Rick C. Hodgin

