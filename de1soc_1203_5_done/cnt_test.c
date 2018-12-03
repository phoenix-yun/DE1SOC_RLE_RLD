#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#define HW_REGS_BASE (0xff200000)
#define HW_REGS_SPAN (0x00200000)
#define HW_REGS_MASK (HW_REGS_SPAN -1)
#define CNT_RST_BASE 0x0
#define CNT_EN_BASE 0x20
#define CNT_VAL_BASE 0x40
int main(void)
{
    int fd;
    void *virtual_base;
    volatile unsigned int *cnt_rst;
    volatile unsigned int *cnt_en;
    volatile unsigned int *cnt_val;
    int val=0;
    int idx=0;

    if( (fd=open( "/dev/mem", ( O_RDWR | O_SYNC) ) ) == -1) {
        printf("ERROR : could not open \"/dev/mem\"...\n");
        return (1);
    }

    virtual_base = mmap (NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE),MAP_SHARED, fd, HW_REGS_BASE);
    if( virtual_base == MAP_FAILED){
        printf("ERROR : mmap() failed....\n");
        close(fd);
        return(1);
    }




    cnt_rst = (unsigned int *)(virtual_base + ((CNT_RST_BASE) & (HW_REGS_MASK)));
    cnt_en = (unsigned int *)(virtual_base + ((CNT_EN_BASE) & (HW_REGS_MASK)));
    cnt_val = (unsigned int *)(virtual_base + ((CNT_VAL_BASE) & (HW_REGS_MASK)));

    *cnt_en=0;
    *cnt_rst = 1;
    *cnt_rst = 0;
    val=*cnt_val;
    printf("val : %d\n",val);
    *cnt_en=1;
    for(idx=0;idx<77777;idx++){

    }
    val=*cnt_val;
    printf("last val : %d\n",val);

    return(0);




}
