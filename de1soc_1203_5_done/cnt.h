#ifndef CNT_H
#define CNT_H
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
void cnt_en_func(int en);
void cnt_rst_func(int rst);
int cnt_val_func();
double pow(double n,double m);

#endif
