#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "File_Handling.h"
#include <string.h>


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
 
 /*check type of line*/
bool check_type(char line[255]){
    if(line[0]=='S'&& line[1]>= '0'  && line[1]<='9' && line[1]!= '4'){
        return true;
    }
    return false;
}

/*check byte count*/
bool check_bytecount(char line[225]){
    char buff[3];
    buff[0]=line[2];
    buff[1] = line[3];
    buff[2] = '\0';
    long number = strtoul(buff,NULL,16);
    int i;
    int count=0;
    for(i=4;i<strlen(line);i++){
        if(line[i]==' '){
            return false;
        }
        else{
            count++;
        }
    }
    if(count/2==number){
        return true;
    }
    return false;
}

/*check sum*/
bool check_sum(char line[255]){
    char buff[3];
    int i;
    long number;
    long sum = 0;
    for(i=2;i<strlen(line)-1;i+=2){
        buff[0]=line[i];
        buff[1]=line[i+1];
        buff[2]= '\0';
        number = strtoul(buff,NULL,16);
        sum = sum + number;
    }
    if(sum % 256 == 255){
        return true;
    }
    return false;
}

/*check data line count*/
bool check_datacount(FILE *f_ptr, int style){
    char datacount_line[255];
    char address[style/4]; /*get address size by style*/
    char i = 0;
    long number;
    while(!feof(f_ptr)){
        fgets(datacount_line,255,f_ptr);
        if(datacount_line[1]=='5'||datacount_line[1]=='6'){
            for(i=0;i<style/4;i++){
                address[i]=datacount_line[i+4];
            }
            number = strtoul(address,NULL,16);
        }
    }
    rewind(f_ptr);
    if(number == data_linecount(f_ptr, style)){
        return true;
    }
    return false;
}
/*count data line (line of S1 or S2 or S3)*/
int data_linecount(FILE *f_ptr, int style){
    int count = 0;
    char data_line[255];
    char type;
    if(style == 16){
        type = '1';
    }
    else if(style == 24){
        type = '2';
    }
    else{
        type = '3';
    }
    while(!feof(f_ptr)){
        fgets(data_line,255,f_ptr);
        if(data_line[1] == type){
            count++;
        }
    }
    return count;
}

/*check style of filse Srecord (16-bit, 24-bit, 32-bit)*/
int styleof_file(FILE *f_ptr){
    char line[255];

    while(!feof(f_ptr)){
        fgets(line,255,f_ptr);
        if(line[1]=='9'){
            return 16; /* file is 16 bit*/
        }
        if(line[1]=='8'){
            return 24; /*file is 24 bit*/
        }
        if(line[1]=='7'){
            return 32; /*file is 32 bit*/
        }
    }
}

void read_data2(FILE *fp, int style){
    char line[255];
    char i = 1;
    bool checksum_err = false;
    bool checktype_err = false;
    bool bytecount_err = false;
    bool datacount_err = false;
    bool err_fl;
    int line_count=1;

    while(!feof(fp)){
        fgets(line,255,fp);
        if(line!='\n'){
            if(check_sum(line)==false){
                checksum_err = true;
                err_fl = true;
            }
            if(check_type(line)==false){
                checktype_err = true;
                err_fl = true;
            }
            if(check_bytecount(line)==false){
                bytecount_err = true;
                err_fl = true;
            }
            if(checksum_err == true || checktype_err == true || bytecount_err == true){
                printf("Line %d: %s",line_count, line);
            }
            if(checksum_err == true){
                printf("Error at check sum!\n");
                checksum_err = false;
            }
            if(checktype_err == true){
                printf("Error at check type!\n");
                checktype_err = false;
            }
            if(bytecount_err == true){
                printf("Error at check byte count!\n");
                bytecount_err = false;
            }
            line_count++;
        }
    }
    rewind(fp); /*Resets the file position locator to the beginning of the file*/
    datacount_err = check_datacount(fp,style);
    if(datacount_err == false){
        printf("\nError at data line count!\n");
        err_fl = true;
    }
}

/*Write data to file txt*/
void write_data(){
    FILE *w_file;
    w_file = fopen("Data.txt", "w+");
}


















void read_data(FILE *fp){
    char c;
    char line[255];
    int i=0;
    int j=0;
    bool c_sum;
    while(!feof(fp)){
        c = fgetc(fp);
        i=0;
        while(c!='\n'&&c!=EOF){
            line[i] = c;
            i++;
            c=fgetc(fp);
        }
        line[i]='\0';
        
    }
    return;
}
