Part 1 
    - Did the real and effective ID values change as you expected for user and group?
        - Only the the euid changed as expected bc of the geteuid() function call
        t0: Init:
        RUID=1000 EUID=0
        RGID=1000 EGID=1000
        Ok, we're effectively running as root! (EUID==0)
        t1: Becoming my original self!
        RUID=1000 EUID=1000
        RGID=1000 EGID=1000
        t2: Switching to privileged state now...
        RUID=1000 EUID=0
        RGID=1000 EGID=1000
        Yup, we're root again!
        t3: Switching back to unprivileged state now ...
        RUID=1000 EUID=1000
        RGID=1000 EGID=1000


Part 2
    - Is the output the same as in Part 1 for both executions?
        - If I modified this program correctly, yes the outcome was the same
        t0: Init:
        RUID=1000 EUID=0
        RGID=1000 EGID=1000
        Ok, we're effectively running as root! (EUID==0)
        t1: Becoming my original self!
        RUID=1000 EUID=0
        RGID=1000 EGID=1000
        t2: Switching to privileged state now...
        RUID=1000 EUID=0
        RGID=1000 EGID=1000
        Yup, we're root again!
        t3: Switching back to unprivileged state now ...
        RUID=1000 EUID=0
        RGID=1000 EGID=1000
