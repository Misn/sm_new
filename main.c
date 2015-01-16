#include <stdio.h>
#include <string.h>
#define _USE_MATHDEFINES
#include <math.h>

double x(double ms)
{
    return 100.0*sin(ms/10.0*M_PI)*sin(ms/10.0*M_PI);
}

double y(double ms)
{
    return 100.0*cos(ms/10.0*M_PI)*cos(ms/10.0*M_PI);
}

double z(double ms)
{
    return 0;
}

struct record{
    int x;
    int y;
    int z;
    int d;
};

int main(int argc, char *argv[])
{
    const int buffer_size=10;//523725
    struct record buffer[buffer_size];
    int proglen,i,ms,lastx,lasty,lastz,newx,newy,newz,lastd;
    FILE *fp;
    size_t res;
    int cycled=0;
    char filename[256]="/home/misn/c_proj/sm_new/pic_file_ll";
    lastd=0;
    lastx=-10000;
    lasty=-10000;
    lastz=-10000;
    for(ms=0,proglen=0;ms<buffer_size;ms++)
    {
        // (int): 1.0->1; 1.1->1; 1.8->1; -1.0->-1; -1.5->-1
        newx=(int)(x((double)ms)+0.5);
        newy=(int)(y((double)ms)+0.5);
        newz=(int)(z((double)ms)+0.5);
        if(newx!=lastx || newy!=lasty || newz!=lastz)
        {
            buffer[proglen].x=newx;
            buffer[proglen].y=newy;
            buffer[proglen].z=newz;
            buffer[proglen].d=1;
            proglen++;
            lastx=newx;
            lasty=newy;
            lastz=newz;
        }
        else
        {
            buffer[proglen-1].d++;
        }
    }
    //printf("@@@");
    //fflush(stdout);
    if(argc>1)
    {
        if(strlen(argv[1])<255)
        {
            strcpy(filename,argv[1]);
        }
        else
        {
            printf("Filename too long, not set!\n");
        }
    }
    else
    {
        printf("No argument specified, default filename used.\n");
    }
    //proglen=0;

    fp=fopen(filename,"wb");
    if(!fp)
    {
        printf("File loading failed!");
        return 1;
    }
    //res=fread(buffer,sizeof(buffer[0]),buffer_size,fp);
//    res=fread(buffer,16,buffer_size,fp);
//    proglen=(int)res;
//    ;
    res=fwrite(buffer,16,proglen,fp);
    fclose(fp);
    if(proglen!=(int)res)
    {
        printf("Unspecified error!\n");
    }

    printf("%d\n", sizeof(buffer[0].x));
    printf("%d\n", sizeof(buffer[0].y));
    printf("%d\n", sizeof(buffer[0].z));
    printf("%d\n", sizeof(buffer[0].d));

    printf("Hello World!\n");
    return 0;
}

