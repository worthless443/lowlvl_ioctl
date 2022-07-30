## OBjective 

Rewritting/modyfing ioctl definations and using it

to Compile:
```
./compile 
```
expected, 

```
failed with "ENOMEM"
main: main.c:72: write_memeory: Assertion `ret==0' failed.
./compile: line 3: 327890 Aborted                 (core dumped) ./main
```
### Problems 

Please checkout the [stackoverflow post](https://stackoverflow.com/questions/73178306/how-to-mprotect-existing-address-to-enable-prot-write-without-using-mmap-i?noredirect=1#comment129242330_73178306)

* mapped memory error (Need to do with mmap)


