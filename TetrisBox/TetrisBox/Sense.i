#line 1 "Sense.cpp"
#line 1 "Sense.h"
#pragma once






class Sense
{
public:
    Sense() = default;
    ~Sense();
public:
    
    void Init();

    
    void Show();

    
    void Down();

    
    void Right();

    
    void Lfet();

    
    void Rotate();

    
    void FixBox();

    
    void DestroyLine();
private:
    int m_SenseX = 3;
    static int m_SenseY ;
    static int sm_Frame[20][12];
};

#line 2 "Sense.cpp"
#line 1 "D:\\VC98\\include\\stdio.h"















#pragma once
#line 18 "D:\\VC98\\include\\stdio.h"






#line 25 "D:\\VC98\\include\\stdio.h"







#pragma pack(push,8)
#line 34 "D:\\VC98\\include\\stdio.h"


extern "C" {
#line 38 "D:\\VC98\\include\\stdio.h"










#line 49 "D:\\VC98\\include\\stdio.h"
#line 50 "D:\\VC98\\include\\stdio.h"






#line 57 "D:\\VC98\\include\\stdio.h"








#line 66 "D:\\VC98\\include\\stdio.h"
#line 67 "D:\\VC98\\include\\stdio.h"



typedef unsigned int size_t;

#line 73 "D:\\VC98\\include\\stdio.h"




typedef unsigned short wchar_t;

#line 80 "D:\\VC98\\include\\stdio.h"



typedef wchar_t wint_t;
typedef wchar_t wctype_t;

#line 87 "D:\\VC98\\include\\stdio.h"
#line 88 "D:\\VC98\\include\\stdio.h"









typedef char *  va_list;
#line 99 "D:\\VC98\\include\\stdio.h"

#line 101 "D:\\VC98\\include\\stdio.h"






#line 108 "D:\\VC98\\include\\stdio.h"

#line 110 "D:\\VC98\\include\\stdio.h"






























#line 141 "D:\\VC98\\include\\stdio.h"





struct _iobuf {
        char *_ptr;
        int   _cnt;
        char *_base;
        int   _flag;
        int   _file;
        int   _charbuf;
        int   _bufsiz;
        char *_tmpfname;
        };
typedef struct _iobuf FILE;

#line 159 "D:\\VC98\\include\\stdio.h"












#line 172 "D:\\VC98\\include\\stdio.h"












#line 185 "D:\\VC98\\include\\stdio.h"




























#line 214 "D:\\VC98\\include\\stdio.h"
#line 215 "D:\\VC98\\include\\stdio.h"





 extern FILE _iob[];
#line 222 "D:\\VC98\\include\\stdio.h"









#line 232 "D:\\VC98\\include\\stdio.h"


typedef __int64 fpos_t;







#line 243 "D:\\VC98\\include\\stdio.h"
#line 244 "D:\\VC98\\include\\stdio.h"


#line 247 "D:\\VC98\\include\\stdio.h"




























 int __cdecl _filbuf(FILE *);
 int __cdecl _flsbuf(int, FILE *);




 FILE * __cdecl _fsopen(const char *, const char *, int);
#line 283 "D:\\VC98\\include\\stdio.h"

 void __cdecl clearerr(FILE *);
 int __cdecl fclose(FILE *);
 int __cdecl _fcloseall(void);




 FILE * __cdecl _fdopen(int, const char *);
#line 293 "D:\\VC98\\include\\stdio.h"

 int __cdecl feof(FILE *);
 int __cdecl ferror(FILE *);
 int __cdecl fflush(FILE *);
 int __cdecl fgetc(FILE *);
 int __cdecl _fgetchar(void);
 int __cdecl fgetpos(FILE *, fpos_t *);
 char * __cdecl fgets(char *, int, FILE *);




 int __cdecl _fileno(FILE *);
#line 307 "D:\\VC98\\include\\stdio.h"

 int __cdecl _flushall(void);
 FILE * __cdecl fopen(const char *, const char *);
 int __cdecl fprintf(FILE *, const char *, ...);
 int __cdecl fputc(int, FILE *);
 int __cdecl _fputchar(int);
 int __cdecl fputs(const char *, FILE *);
 size_t __cdecl fread(void *, size_t, size_t, FILE *);
 FILE * __cdecl freopen(const char *, const char *, FILE *);
 int __cdecl fscanf(FILE *, const char *, ...);
 int __cdecl fsetpos(FILE *, const fpos_t *);
 int __cdecl fseek(FILE *, long, int);
 long __cdecl ftell(FILE *);
 size_t __cdecl fwrite(const void *, size_t, size_t, FILE *);
 int __cdecl getc(FILE *);
 int __cdecl getchar(void);
 int __cdecl _getmaxstdio(void);
 char * __cdecl gets(char *);
 int __cdecl _getw(FILE *);
 void __cdecl perror(const char *);
 int __cdecl _pclose(FILE *);
 FILE * __cdecl _popen(const char *, const char *);
 int __cdecl printf(const char *, ...);
 int __cdecl putc(int, FILE *);
 int __cdecl putchar(int);
 int __cdecl puts(const char *);
 int __cdecl _putw(int, FILE *);
 int __cdecl remove(const char *);
 int __cdecl rename(const char *, const char *);
 void __cdecl rewind(FILE *);
 int __cdecl _rmtmp(void);
 int __cdecl scanf(const char *, ...);
 void __cdecl setbuf(FILE *, char *);
 int __cdecl _setmaxstdio(int);
 int __cdecl setvbuf(FILE *, char *, int, size_t);
 int __cdecl _snprintf(char *, size_t, const char *, ...);
 int __cdecl sprintf(char *, const char *, ...);
 int __cdecl sscanf(const char *, const char *, ...);
 char * __cdecl _tempnam(const char *, const char *);
 FILE * __cdecl tmpfile(void);
 char * __cdecl tmpnam(char *);
 int __cdecl ungetc(int, FILE *);
 int __cdecl _unlink(const char *);
 int __cdecl vfprintf(FILE *, const char *, va_list);
 int __cdecl vprintf(const char *, va_list);
 int __cdecl _vsnprintf(char *, size_t, const char *, va_list);
 int __cdecl vsprintf(char *, const char *, va_list);








#line 363 "D:\\VC98\\include\\stdio.h"




 FILE * __cdecl _wfsopen(const wchar_t *, const wchar_t *, int);
#line 369 "D:\\VC98\\include\\stdio.h"

 wint_t __cdecl fgetwc(FILE *);
 wint_t __cdecl _fgetwchar(void);
 wint_t __cdecl fputwc(wint_t, FILE *);
 wint_t __cdecl _fputwchar(wint_t);
 wint_t __cdecl getwc(FILE *);
 wint_t __cdecl getwchar(void);
 wint_t __cdecl putwc(wint_t, FILE *);
 wint_t __cdecl putwchar(wint_t);
 wint_t __cdecl ungetwc(wint_t, FILE *);

 wchar_t * __cdecl fgetws(wchar_t *, int, FILE *);
 int __cdecl fputws(const wchar_t *, FILE *);
 wchar_t * __cdecl _getws(wchar_t *);
 int __cdecl _putws(const wchar_t *);

 int __cdecl fwprintf(FILE *, const wchar_t *, ...);
 int __cdecl wprintf(const wchar_t *, ...);
 int __cdecl _snwprintf(wchar_t *, size_t, const wchar_t *, ...);
 int __cdecl swprintf(wchar_t *, const wchar_t *, ...);
 int __cdecl vfwprintf(FILE *, const wchar_t *, va_list);
 int __cdecl vwprintf(const wchar_t *, va_list);
 int __cdecl _vsnwprintf(wchar_t *, size_t, const wchar_t *, va_list);
 int __cdecl vswprintf(wchar_t *, const wchar_t *, va_list);
 int __cdecl fwscanf(FILE *, const wchar_t *, ...);
 int __cdecl swscanf(const wchar_t *, const wchar_t *, ...);
 int __cdecl wscanf(const wchar_t *, ...);






 FILE * __cdecl _wfdopen(int, const wchar_t *);
 FILE * __cdecl _wfopen(const wchar_t *, const wchar_t *);
 FILE * __cdecl _wfreopen(const wchar_t *, const wchar_t *, FILE *);
 void __cdecl _wperror(const wchar_t *);
 FILE * __cdecl _wpopen(const wchar_t *, const wchar_t *);
 int __cdecl _wremove(const wchar_t *);
 wchar_t * __cdecl _wtempnam(const wchar_t *, const wchar_t *);
 wchar_t * __cdecl _wtmpnam(wchar_t *);



#line 414 "D:\\VC98\\include\\stdio.h"
#line 415 "D:\\VC98\\include\\stdio.h"


#line 418 "D:\\VC98\\include\\stdio.h"
































 int __cdecl fcloseall(void);
 FILE * __cdecl fdopen(int, const char *);
 int __cdecl fgetchar(void);
 int __cdecl fileno(FILE *);
 int __cdecl flushall(void);
 int __cdecl fputchar(int);
 int __cdecl getw(FILE *);
 int __cdecl putw(int, FILE *);
 int __cdecl rmtmp(void);
 char * __cdecl tempnam(const char *, const char *);
 int __cdecl unlink(const char *);

#line 463 "D:\\VC98\\include\\stdio.h"


}
#line 467 "D:\\VC98\\include\\stdio.h"


#pragma pack(pop)
#line 471 "D:\\VC98\\include\\stdio.h"

#line 473 "D:\\VC98\\include\\stdio.h"
#line 3 "Sense.cpp"



Sense::~Sense()
{
}

void Sense::Init()
{
    for (int i = 0; i < 20; i++)
    {
        sm_Frame[i][0] = 0;
        sm_Frame[i][12 - 1] = 0;
    }
    for (int j = 0; j < 12; j++)
    {
        sm_Frame[20 - 1][j] = 0;
    }
}

void Sense::Show()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (sm_Frame[i][j] == 0 || sm_Frame[i][j] == 1)
            {
                printf("¡ö");
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void Sense::Down()
{

}
