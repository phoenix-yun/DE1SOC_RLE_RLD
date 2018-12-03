#include<stdio.h>
#include<stdlib.h>
//#include<math.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<libgen.h>
#include"./../cnt.h"

int main(int argc, char *argv[]){
    FILE *fp;
    FILE *fp_o;
    char *filename;
    char *filename_temp;
    char temp[99]="/compressed_";
    filename_temp = argv[1];
    filename_temp=basename(filename_temp);
    char *ofile_dir=argv[3];
    char ofile_path[99]="./compressed_";
    char *str_compressed;
    // for iteration
    int i = 1;
    int val=0;

    if (argc < 3) {
        printf("Wrong argment! [ori_file_loc] [length bitwidth] [out file dir]\n");
        return -1;
    }
    filename = argv[1];
    strcat(ofile_path,ofile_dir);
    //strcat(ofile_path,"_compressed");
    mkdir(ofile_path,0777);
    //sprintf(filename_o,"./compressed/compressed_");
    int maxlength_i=atoi(argv[2]);
    fp = fopen(filename,"r");
    if(fp==NULL){
        printf("input file does not exist\n");
        return -1;
    }

    strcat(ofile_path,temp);
    strcat(ofile_path,filename_temp);
    fp_o = fopen(ofile_path,"w");
    if(fp_o==NULL){
        printf("output file does not exist\n");
        return -1;
    }
    // cnt control 1 
    cnt_en_func(0);
    cnt_rst_func(1);
    cnt_rst_func(0);
    cnt_en_func(1);//start
    
    // do rle 
    fseek(fp,0,SEEK_END);
    int size = ftell(fp)/sizeof(unsigned char);
    unsigned char *lsb;
    lsb=(unsigned char *)malloc(sizeof(unsigned char)*size);

    fseek(fp,0,SEEK_SET);
    fread(lsb,sizeof(unsigned char),size,fp);
    unsigned int length =0;
    unsigned int prevalue=0;
    unsigned int f_maxlength=0;
    unsigned int O_tile=0;
    unsigned int Maxlength=0;
    double maxlength_double = (double)maxlength_i;
    Maxlength=((unsigned int)pow(2.0,maxlength_double)-1);


    if(lsb[0]==0){
        prevalue=0;
        length=1;
    }

    else{
        prevalue=1;
        length=1;
    }
    for(i=1;i<size;i++){

        if(f_maxlength==1){
            prevalue=lsb[i];
            f_maxlength=0;
        }
        if(lsb[i]==prevalue){
            prevalue=prevalue;
            length++;
        }

        else{
            O_tile = (prevalue<<31)|length;
            fwrite(&O_tile,sizeof(unsigned int),1,fp_o);
            length=1;
            if(prevalue==0){
                prevalue=1;
            }
            else{
                prevalue=0;
            }
        }

        if(length==Maxlength){
            O_tile = (prevalue<<31)|length;
            fwrite(&O_tile,sizeof(unsigned int),1,fp_o);
            length=0;
            f_maxlength=1;
        }
        if(i==size-1){
            O_tile = (prevalue<<31)|length;
            fwrite(&O_tile,sizeof(unsigned int),1,fp_o);
            length=0;
            break;
        }

    }
    free(lsb);
    fclose(fp);
    fclose(fp_o);
 
    // stop count
    cnt_en_func(0);
    // get cnt_val
    val=cnt_val_func();

    FILE *fp_cnt_time;
    fp_cnt_time=fopen("./comp_cnt_time.csv","a");
    fprintf(fp_cnt_time,"32bit,%s,%d\n",filename ,val);
    fclose(fp_cnt_time);

    return 0;

} 
