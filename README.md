## OBjective 

Rewritting/modyfing ioctl definations and using it


Run it in GDB virtualized addresses (since we are using address specified by gdb and address on runtime can be randomized), to Compile and run:
```
./gdb_compile 

```
expected, 

```
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
93826070893012
niggerd
addr = 93826070893028
[Inferior 1 (process 347791) exited normally     (core dumped) ./main
```

### Problems 

Please checkout the [stackoverflow post](https://stackoverflow.com/questions/73178306/how-to-mprotect-existing-address-to-enable-prot-write-without-using-mmap-i?noredirect=1#comment129242330_73178306)

* mapped memory error (Need to do with mmap) [solved]
* align pages on the system runtime


NOTE
: The ioctl() part is not being worked on as of this commit 
