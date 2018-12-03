#include<stdio.h>
#include"./cnt.h"
void cnt_en_func(int en){
    volatile unsigned int *cnt_en;
    int fd;
    void *virtual_base;
    if( (fd=open( "/dev/mem", ( O_RDWR | O_SYNC) ) ) == -1) {
        printf("ERROR : could not open \"/dev/mem\"...\n");
        return;
    }

    virtual_base = mmap (NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE),MAP_SHARED, fd, HW_REGS_BASE);
    if( virtual_base == MAP_FAILED){
        printf("ERROR : mmap() failed....\n");
        close(fd);
        return;
    }




    cnt_en = (unsigned int *)(virtual_base + ((CNT_EN_BASE) & (HW_REGS_MASK)));

    *cnt_en=en;
    return;
}


void cnt_rst_func(int rst){
    volatile unsigned int *cnt_rst;
    int fd;
    void *virtual_base;
    if( (fd=open( "/dev/mem", ( O_RDWR | O_SYNC) ) ) == -1) {
        printf("ERROR : could not open \"/dev/mem\"...\n");
        return;
    }

    virtual_base = mmap (NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE),MAP_SHARED, fd, HW_REGS_BASE);
    if( virtual_base == MAP_FAILED){
        printf("ERROR : mmap() failed....\n");
        close(fd);
        return;
    }




    cnt_rst = (unsigned int *)(virtual_base + ((CNT_RST_BASE) & (HW_REGS_MASK)));

    *cnt_rst=rst;
    return;
}

int cnt_val_func(){
    volatile unsigned int *cnt_val;
    int fd;
    void *virtual_base;
    if( (fd=open( "/dev/mem", ( O_RDWR | O_SYNC) ) ) == -1) {
        printf("ERROR : could not open \"/dev/mem\"...\n");
        return (1);
    }

    virtual_base = mmap (NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE),MAP_SHARED, fd, HW_REGS_BASE);
    if( virtual_base == MAP_FAILED){
        printf("ERROR : mmap() failed....\n");
        close(fd);
        return (1);
    }




    cnt_val = (unsigned int *)(virtual_base + ((CNT_VAL_BASE) & (HW_REGS_MASK)));

    return *cnt_val;
}

double pow(double n,double m){
    double i=0;
    unsigned int temp_n=0;
    temp_n=(unsigned int)n;

    for(i=0;i<m-1;i++){
        if(m==0){
            return 1;
        }
        if(m==1){
            return n;
        }
        temp_n=temp_n*n;
    }
    n=(double)temp_n;
    return n;

}
