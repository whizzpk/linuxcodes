#include <stdio.h>  
 #include <stdlib.h>  
 #include <string.h>  
 #include <sys/types.h>  
 #include <sys/stat.h>  
 #include <sys/ioctl.h>  
 #include <asm/mtrr.h>  
 #include <fcntl.h>  
   
 #define LONGSZ    ((int)(sizeof(long)<<1))  
   
 int main(int argc, char *argv[])  
 {  
     struct mtrr_gentry gentry;  
     int fd;  
   
     static char *mtrr_type[] = {  
         "Uncachable",  
         "Write Combining",  
         "Unknown",  
         "Unknown",  
         "Write Through",  
         "Write Protect",  
         "Write Back"  
     };  
   
     if ((fd = open("/proc/mtrr", O_RDONLY, 0)) < 0) {  
         fprintf(stderr, "Cannot open /proc/mtrr!\n");  
         exit(EXIT_FAILURE);  
     }  
           
     memset(&gentry, 0, sizeof(gentry));  
   
     while (!ioctl(fd, MTRRIOC_GET_ENTRY, &gentry)) {  
         if (gentry.size < 1)   
             printf("%u: Disabled\n", gentry.regnum);  
         else  
             printf("%u: 0x%*.*lx..0x%*.*lx %s\n", gentry.regnum,  
                 LONGSZ, LONGSZ, gentry.base,   
                 LONGSZ, LONGSZ, gentry.base + gentry.size,  
                 mtrr_type[gentry.type]);  
         gentry.regnum++;  
     }  
     close(fd);  
   
     exit(EXIT_SUCCESS);  
 }
