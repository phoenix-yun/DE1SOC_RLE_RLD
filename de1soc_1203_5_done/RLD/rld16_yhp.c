#include<stdio.h>
#include<stdlib.h>
//#include<math.h>
#include"./../cnt.h"

typedef union{
    unsigned short pack;
    struct{
        unsigned short length:15;
        unsigned short run:1;
    }field;
}my_16pack;


int main(int argc, char *argv[]){
    FILE *fp;
    FILE *fp_o;
    my_16pack var;

    char *filename;
    char *filename_o;
    
    if (argc < 2) {
        printf("Wrong argment! [ori_file_loc] [ofile loc]\n");
        return -1;
    }
    // for iteration
    int i = 1;
    int val = 0;
    int idx = 0;
    filename = argv[1];
    fp = fopen(filename,"r");
    fseek(fp,0,SEEK_END);
    filename_o = argv[2];
    fp_o = fopen(filename_o,"w");
    
    int size = ftell(fp)/sizeof(unsigned short);
    unsigned short *lsb;
    lsb=(unsigned short *)malloc(sizeof(unsigned short)*size);

    fseek(fp,0,SEEK_SET);
    fread(lsb,sizeof(unsigned short),size,fp);
    // cnt control 1 
    cnt_en_func(0);
    cnt_rst_func(1);
    cnt_rst_func(0);
    cnt_en_func(1);//start

    for(i=0; i<size;i++){
        var.pack=lsb[i];
        for(idx=0;idx<var.field.length;idx++){
            unsigned char run_temp = (unsigned char)var.field.run;
            fwrite(&run_temp,sizeof(unsigned char),1,fp_o);
        }
    }
    printf("%d",sizeof(unsigned short));
    fclose(fp);
    fclose(fp_o);
    free(lsb);

    // stop count
    cnt_en_func(0);
    // get cnt_val
    val=cnt_val_func();

    FILE *fp_cnt_time;
    fp_cnt_time=fopen("./decomp_cnt_time.csv","a");
    fprintf(fp_cnt_time,"16bit,%s,%d\n",filename ,val);
    fclose(fp_cnt_time);
    return 0;

}

