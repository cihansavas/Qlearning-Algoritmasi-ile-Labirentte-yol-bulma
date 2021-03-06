//130202098-150202104 YAZLAB-2 QLEARNIN ALGORITMASI ILE LABIRENTTE YOL BULMA
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>
#include <stdio.h>
#include <cstdlib>
#include "bitmap_image.hpp"
#include <iomanip>
void kapiciz(int oda,int komsuluk,int boyut);
void basla_bitir_kapiciz(int oda,int boyut);
void robotciz(int oda,int boyut);
void robotsil(int oda,int boyut);
void cemberciz(int oda,int boyut);
void cembersil(int oda,int boyut);
void Qlearning_kapiciz(int oda,int komsuluk,int boyut);

int yon,ust=0,alt=3,sol=1,sag=2;//ROBOTUN LABIRENNTEKI SON ADIMDAKI CIZIMI ICIN  KULLANILMAKTADIR



using namespace std;
int main()
{
srand(time(NULL));// Birim zamanda random sayi üretir bu kullanılmazsa genelde aynı sayıyı üretir
initwindow(1200, 600,"130202098-150202104 Q LEARNIG ALGORITMASI ILE LABIRENTTE YOL BULMA PROJESI",20,20);
readimagefile("karsilamaekrani.JPG",0,0,1200,600);
//Belirtilen boyutlarda grafik penceresini oluşturuyor.
FILE *inputboyut=fopen("input.txt","r");//İNPUT.TXT DOSYASINI OKUR
char veri[50];
int boyut=0;//LABİRENTİN
//ÝNPUT BOYUTU BELÝRLENÝYOR

     while(!feof(inputboyut))
                {
                  fscanf(inputboyut,"%s",&veri);
                       boyut++;

                 }
                 fclose(inputboyut);
yenidenbaslat:
                 int baslangicodasi,bitisodasi,iterasyonsayisi;
                 printf("\n%d ODAYA SAHIP LABIRENTIN BASLANGIC ODASINI GIRINIZ:",boyut);
                 scanf("%d",&baslangicodasi);
                 printf("\n%d ODAYA SAHIP LABIRENTIN BITIS ODASINI GIRINIZ:",boyut);
                yenidengir:
                 scanf("%d",&bitisodasi);
                 if(bitisodasi>boyut)
                 {
                     printf("\n GIRDINIZ DEGER %d SAYISINDAN BUYUK  VE ESIT OLAMAZ YENI DEGER GIRINIZ:",boyut);

                     goto yenidengir;
                 }
                  printf("\n%d ODAYA SAHIP LABIRENTIN ITERASYON SAYISINI  GIRINIZ:",boyut);
                 scanf("%d",&iterasyonsayisi);
                 int i,j;
cleardevice();
readimagefile("karsilamaekrani2.JPG",610,0,1200,580);
//LABIRENT CIZDIRILDI
setcolor(WHITE);
int dugumsayisi=sqrt(boyut);
 for(i=0;i<=dugumsayisi;i++)//KARE MATRİS TABLO OLUŞTURMA
    {
    line(100,i*50+40,100+dugumsayisi*50,i*50+40);//DİKEY
    line(100+i*50,40,100+i*50,40+dugumsayisi*50);
    }
    setcolor(BLACK);
for(i=0;i<dugumsayisi;i++)  //MATRiSiN DİKEY DUGUM ADI
    {
    char s1[20];
    char s2[20];
    sprintf(s2,"  %d",i);
    sprintf(s1,"  %d",i);
    outtextxy(70,50*i+50,s1);//dikey
    outtextxy(105+i*50,20,s2);//yatay
    }
setcolor(BLACK);
basla_bitir_kapiciz(baslangicodasi,boyut);
basla_bitir_kapiciz(bitisodasi,boyut);

                 int Rmatrisi[boyut][boyut]={};//R MATRÝSÝ TANIMLANDI
                 //R MATRÝSÝNÝN TÜM ELEMANLARI -1 YAPILDI
                 for(i=0;i<boyut;i++)
                 {
                         for(j=0;j<boyut;j++)
                     {
                         Rmatrisi[i][j]=-1;
                         //printf("%d,%d:%d\n",i,j,Rmatrisi[i][j]);
                     }
                 }

int oda_index=0;
int verisatir,verisutun;//okunan veriye mod işlemi uygulayarak bulucaz


                 FILE *input=fopen("input.txt","r");
                 while(!feof(input)){
                      fscanf(input,"%s",&veri);



                      // printf("%s\n",veri);
/*
dosyadan okunan verinin tek bir kapýdan mý yoksa çok kapýdan mý oluþtuðu kýyaslanýyor
*/
if(strstr(veri,",")!=NULL)
{//virgul varsa birden fazla kapý var demektir.
              char *ayrac;

          ayrac = strtok (veri,",");
           while (ayrac!= NULL)
          {
            //printf ("%s\n",ayrac);
            if(atoi(ayrac)==bitisodasi)
            {
              Rmatrisi[oda_index][atoi(ayrac)]=100;
              kapiciz(oda_index,atoi(ayrac),boyut);
            }
            else
            {
              Rmatrisi[oda_index][atoi(ayrac)]=0;
              kapiciz(oda_index,atoi(ayrac),boyut);
            }

            //printf("%d,%d:%d\n",oda_index,atoi(ayrac),Rmatrisi[oda_index][atoi(ayrac)]);
            ayrac = strtok (NULL, ",");
        }
}
else
{//virgul yoksa tek veriden olusuyodur.
        if(atoi(veri)==bitisodasi)
        {
          Rmatrisi[oda_index][atoi(veri)]=100;
          kapiciz(oda_index,atoi(veri),boyut);
        }
        else
        {
          kapiciz(oda_index,atoi(veri),boyut);
          Rmatrisi[oda_index][atoi(veri)]=0;
          verisatir=atoi(veri)/sqrt(boyut);
          verisutun=atoi(veri)-verisatir*sqrt(boyut);

        }
        //printf("Virgulyok:%d,%d:%d\n",oda_index,atoi(veri),Rmatrisi[oda_index][atoi(veri)]);
}

        oda_index++;

}
                 fclose(input);
Rmatrisi[bitisodasi][bitisodasi]=100;

printf("\n\n\tR MATRISI YAZDIRILIYOR:\n\n");
 printf("\t");
                  for(i=0;i<boyut;i++)
                 {
                     printf("[%d]\t",i);
                 }
                 printf("\n\n");
                  for(i=0;i<boyut;i++)
                 {
                     printf("[%d]\t",i);
                     for(j=0;j<boyut;j++)
                 {
                     //Rmatrisi[i][j]=-1;
                     printf("%d\t",Rmatrisi[i][j]);
                 }
                 printf("\n");
                 }


                  FILE *Rmat;           /* dosya göstericisi */


    Rmat = fopen("OuthR.txt", "w");

    if(  Rmat == NULL )
      puts("OuthR.txt dosyasi acilmadi. !\n"), exit(1);

                for(i=0;i<boyut;i++)
                 {
                     printf("[%d]\t",i);
                 }
                 fprintf(Rmat,"\n\n");
                for(i=0;i<boyut;i++)
                 {
                     fprintf(Rmat,"[%d]\t",i);
                        for(j=0;j<boyut;j++)
                         {

                             fprintf(Rmat,"%d\t",Rmatrisi[i][j]);
                         }
                 fprintf(Rmat,"\n");
                 }

fclose(Rmat);


    float Qmatrisi[boyut][boyut]={};

                 int iterasyon=0;
Odabaslangickodu:
                  int Random_Oda;
                //  srand(time(NULL));
                   Random_Oda=rand()%boyut;//RASTGELE BİR BAŞLANGIÇ NOKTASI SEÇTİK
                   printf("\nRandomoda:%d",Random_Oda);
                   int  komsulukadeti=0,randomodabilgisi[boyut];
for(i=0;i<boyut;i++)//RASTGELE SEÇİLEN BAŞLANGIÇ İÇİN BİR AKSİYON SEÇİYORUZ
{
    if(Rmatrisi[Random_Oda][i]==0||Rmatrisi[Random_Oda][i]==100)
    {
        randomodabilgisi[komsulukadeti]=i;
        printf("\nkomsuluklar:%d",i);
        komsulukadeti++;
    }
}
cembersil(Random_Oda,boyut);
int Random_kapi;
 //srand(time(NULL));
Random_kapi=randomodabilgisi[rand()%komsulukadeti]  ;//RANDOM ODA İÇİN RANDOM AKSİYON SEÇTİK;
//printf("\nSecilenOda:[%d][%d]\n",Random_Oda,Random_kapi);

iterasyon:
cemberciz(Random_Oda,boyut);
float maxdeger=0.0;
//ŞİMDİ AKSİYON İÇİN FORMULDE MAX(Q değerleri komşuluklarına bakıyoruz)
komsulukadeti=0;
for(i=0;i<boyut;i++)//RASTGELE SEÇİLEN BAŞLANGIÇ İÇİN BİR AKSİYON SEÇİYORUZ
{
    if(Rmatrisi[Random_kapi][i]==0||Rmatrisi[Random_kapi][i]==100)
    {
        randomodabilgisi[komsulukadeti]=i;
       // printf("\nsonrakikomsuluklar:%d",i);
        komsulukadeti++;


    }
}
for(i=0;i<komsulukadeti;i++)//RASTGELE SEÇİLEN BAŞLANGIÇ İÇİN BİR AKSİYON SEÇİYORUZ
{
   if(maxdeger<=Qmatrisi[Random_kapi][randomodabilgisi[i]])
   {
       maxdeger=Qmatrisi[Random_kapi][randomodabilgisi[i]];
   }

}


Qmatrisi[Random_Oda][Random_kapi]=Rmatrisi[Random_Oda][Random_kapi]*1.0+0.8*maxdeger;
printf("\nQ[%d][%d]=R[%d][%d]+0,8*Max(Q[%d][%d]",Random_Oda,Random_kapi,Random_Oda,Random_kapi,Random_kapi, randomodabilgisi[0]);
if(komsulukadeti>1)
{
    for(i=1;i<komsulukadeti;i++)
    {
    printf("+Q[%d][%d]",Random_kapi, randomodabilgisi[i]);

    }
}
printf(")=%0.2f\n",Qmatrisi[Random_Oda][Random_kapi]);


if(Rmatrisi[Random_Oda][Random_kapi]==100)// SEÇİLEN ODA ÇIKIŞ KAPISIMI
{
char s1[20];
sprintf(s1,"TAMAMLANAN ITERASYON:%d",iterasyon);
outtextxy(10,580,s1);
cembersil(Random_Oda,boyut);
printf("\nBULDU");
cemberciz(bitisodasi,boyut);
//Sleep(1000);
cembersil(bitisodasi,boyut);
}
else
{
// printf("\nBULAMADI");
cembersil(Random_Oda,boyut);
Random_Oda=Random_kapi;
Random_kapi=randomodabilgisi[rand()%komsulukadeti];
 goto iterasyon;
}








if(iterasyon==iterasyonsayisi)
{

    printf("\n %d itirasyon tamamlandı ",iterasyonsayisi);
//Mehmet

                 FILE *Qmat;           /* dosya göstericisi */

  Qmat = fopen("OutQ.txt", "w");

    if(  Qmat == NULL )
      puts("OutQ.txt dosyasi acilmadi. !\n"), exit(1);


     fprintf(Qmat,"\tQ Matrisi\n",i);

                  for(i=0;i<boyut;i++)
                 {

                     fprintf(Qmat,"[%d] ",i);
                     for(j=0;j<boyut;j++)
                 {
                     //Rmatrisi[i][j]=-1;

                    fprintf(Qmat,"%0.3f ",Qmatrisi[i][j]);
                 }
                 fprintf(Qmat,"\n");
                 }
                 fclose(Qmat);
  /* dosyayı kapat */

    //Mehmet

}
else
{
    iterasyon++;
    goto Odabaslangickodu;
}


 printf("\n\n\tQ MATRISI YAZDIRILIYOR:\n\n");
 printf("\t");
                  for(i=0;i<boyut;i++)
                 {
                     printf("[%d]\t",i);
                 }
                 printf("\n\n");
                  for(i=0;i<boyut;i++)
                 {
                     printf("[%d]\t",i);
                     for(j=0;j<boyut;j++)
                 {
                     //Rmatrisi[i][j]=-1;
                     printf("%0.3f\t",Qmatrisi[i][j]);
                 }
                 printf("\n");
                 }
cembersil(Random_Oda,boyut);


 FILE *Path;
 /* dosya göstericisi */
   Path = fopen("OutPath.txt", "w");

    if( Path == NULL )
      puts("OuthPath.txt dosyasi acilmadi. !\n"), exit(1);


    // fprintf(Path,"\tQ Matrisi\n",i);



setcolor(WHITE);
int cizimsayaci=0;
outtextxy(270,580,"YOL HARITASI:");
printf("\nYOL HARITASI:%d-->",baslangicodasi);
fprintf(Path,"%d-->",baslangicodasi);
char s1[100];
sprintf(s1,"%d->>",baslangicodasi);
outtextxy(375+cizimsayaci*45,580,s1);
cizimsayaci++;

int Path_kapi=baslangicodasi;
setlinestyle(0,0,4);
int yolciz=baslangicodasi;
int Yolindeksi;
yoladevam:
komsulukadeti=0;
maxdeger=0;
for(i=0;i<boyut;i++)//RASTGELE SEÇİLEN BAŞLANGIÇ İÇİN BİR AKSİYON SEÇİYORUZ
{
   if(maxdeger<=Qmatrisi[Path_kapi][i])
   {
       maxdeger=Qmatrisi[Path_kapi][i];
       Yolindeksi=i;

   }

}


if(Yolindeksi==bitisodasi)
{
robotciz(yolciz,boyut);
    printf("%d OLARAK BULUNDU",Yolindeksi);
    fprintf(Path,"%d",Yolindeksi);
    sprintf(s1,"%d->>OLARAK BULUNDU",Yolindeksi);
    outtextxy(375+cizimsayaci*45,580,s1);


}
else{
        printf("%d-->",Yolindeksi);
        fprintf(Path,"%d-->",Yolindeksi);
         sprintf(s1,"%d->>",Yolindeksi);
         outtextxy(375+cizimsayaci*45,580,s1);
        cizimsayaci++;
       Path_kapi=Yolindeksi;
       robotciz(yolciz,boyut);
        Sleep(1000);
       robotsil(yolciz,boyut);
       Qlearning_kapiciz(yolciz,Yolindeksi,boyut);

   yolciz=Yolindeksi;
    goto yoladevam;
}

fclose(Path);
Sleep(1000);

robotsil(yolciz,boyut);
robotciz(bitisodasi,boyut);
Sleep(1000);
robotsil(bitisodasi,boyut);
Qlearning_kapiciz(yolciz,bitisodasi,boyut);
int sutun=bitisodasi/sqrt(boyut);
int satir=bitisodasi%(int)sqrt(boyut);
if(yon==alt)
{
robotciz(bitisodasi+sqrt(boyut),boyut);
}
else if(yon==ust)
{

readimagefile("robot.bmp",105+satir*50,0,145+satir*50,45);
}
else if(yon==sol)
{

readimagefile("robot.bmp",50+satir*50,45+sutun*50,100+satir*50,85+sutun*50);
}
else if(yon==sag)
{

readimagefile("robot.bmp",150+satir*50,45+sutun*50,200+satir*50,85+sutun*50);
}


int secim;
printf("\nLABIRENTI YENI GIRIS DEGERLERIYLE DENEMEK ISTIYORMUSUNUZ? EVET ICIN 1 e BASINIZ:");
scanf("%d",&secim);
if(secim==1)
{
setlinestyle(0,0,0);
cleardevice();
goto yenidenbaslat;

}
else
{
    return 0;
}
getch();
    return 0;

}
/*
input.txt den okunan degerlere gore kare matriste kapı cizme işlemi yapar.
*/
void kapiciz(int oda,int komsuluk,int boyut)
{
    setcolor(BLACK);
    degistir:
    int odasutun,komsuluksutun;
    odasutun=oda%(int)sqrt(boyut);
    komsuluksutun=komsuluk%(int)sqrt(boyut);
    int odasatir=oda/sqrt(boyut);
    int komsuluksatir=komsuluk/sqrt(boyut);


    if(odasatir==komsuluksatir)//ODA ILE KOMSU AYNI SATIRDA ISE
    {
        if(oda<komsuluk)//ODALARIN KESISTIGI KENARI CIKIS YAPISI YAP
        {
        line(100+50*(odasutun+1),40+50*odasatir,100+50*(odasutun+1),40+50*(komsuluksatir+1));//DİKEYİN FORMULU
        }
        else//CIZIM ODA<KOMSULUK'A GORE YAPILMAKTA BU NEDENLE UYMUYORSA KOMSULUKLA ODA YER DEGISTIRIP CIZIM GERCEKLESTIRILIR
        {
            int degis;
            degis=oda;
            oda=komsuluk;
            komsuluk=degis;
            goto degistir;
        }
    }
    else//ODA ILE KOMSU AYNI SATIRDA DEGIL ISE(DOLAYISIYLA AYNI SUTUNDADIR)
    {

        if(oda<komsuluk)//ODALARIN KESISTIGI KENARI CIKIS YAPISI YAP
        {
        line(100+50*(odasutun),40+50*(odasatir+1),100+50*(odasutun+1),40+50*(odasatir+1));//YATAY FORMULU
        }
        else//CIZIM ODA<KOMSULUK'A GORE YAPILMAKTA BU NEDENLE UYMUYORSA KOMSULUKLA ODA YER DEGISTIRIP CIZIM GERCEKLESTIRILIR
        {
            int degis;
            degis=oda;
            oda=komsuluk;
            komsuluk=degis;
        goto degistir;
        }



    }

}
/*
KULLANICININ GIRDIGI BASLANGIC VE BITIS KAPISINI LABIRENTTE CIZER
*/
void basla_bitir_kapiciz(int oda,int boyut)
{

    int satir=oda/(int)sqrt(boyut);
    int sutun=oda%(int)sqrt(boyut);
    setcolor(BLACK);
    setlinestyle(0,0,4);
    boyut=sqrt(boyut);

    if(satir!=0&&sutun==0&&satir!=boyut-1)//LABIRENTIN SOL DUVARINI TEMSIL EDER 0 VE SONUNCU SATIRLARI HARIC
    {
    line(100+50*(sutun),40+satir*50,100+50*(sutun),40+(satir+1)*50);
    //printf("Girdi:1\n");
    yon=sol;
    }
    else if(satir==0)//LABIRENTIN UST DUVARINI TEMSIL EDER
    {
    yon=ust;
    line(100+50*(sutun),40+satir*50,100+50*(sutun+1),40+(satir)*50);

    }
    else if(satir!=0&&sutun!=0&&satir!=boyut-1)//LABIRENTIN SAG DUVARINI TEMSIL EDER 0 VE SONUNCU SATIR HARIC
    {
    line(100+50*(sutun+1),40+satir*50,100+50*(sutun+1),40+(satir+1)*50);

    yon=sag;
    }


    if(satir==boyut-1)//LABIRENTIN ALT DUVARINI TEMSIL EDER
    {
    yon=alt;

    line(100+50*(sutun),40+(satir+1)*50,100+50*(sutun+1),40+(satir+1)*50);

    }

}
/*
ITERASYON SONUCU OLUŞAN Q MATRISINDE BAŞLANGIC ODASINDAN BAŞLAYARAK CIKIS
KAPISINA GIDEN YOLDA LABIRENTTE ROBOT CIZME ISLEMI YAPAR
*/
void robotciz(int oda,int boyut)
{

    int sutun=oda/sqrt(boyut);
    int satir=oda%(int)sqrt(boyut);
    readimagefile("robot.bmp",105+satir*50,45+sutun*50,145+satir*50,85+sutun*50);
}
//ROBOT ODA DEGISTIRDIGINDE BIR ONCEKI ODADAN ROBOT GORUNTUSUNU SILER
void robotsil(int oda,int boyut)
{

    int sutun=oda/sqrt(boyut);
    int satir=oda%(int)sqrt(boyut);
    readimagefile("robotsil.bmp",105+satir*50,45+sutun*50,145+satir*50,85+sutun*50);
}
//ITERASYON ADIMINDA RASTGELE SECILEN ODALARIN ICERISINE CEMBER SEKLI CIZER
void cemberciz(int oda,int boyut)
{
setcolor(WHITE);
int sutun=oda/sqrt(boyut);
int satir=oda%(int)sqrt(boyut);
circle(abs(125+satir*50),abs(65+sutun*50),abs(4));
}
//ITERASYON ODA DEGISTIRDIGINDE BIR ONCEKI ODADAN CEMBER SEKLINI SILER
void cembersil(int oda,int boyut)
{
setcolor(BLACK);
int sutun=oda/sqrt(boyut);
int satir=oda%(int)sqrt(boyut);
circle(abs(125+satir*50),abs(65+sutun*50),abs(4));
}


/*
QLEARNING MATRISINDE GIRISTEN CIKISA DOGRU GIDERKEN IZLENEN YOLU KIRMIZI OLARAK CIZER
*/
void Qlearning_kapiciz(int oda,int komsuluk,int boyut)// path sonucunu çizer
{
    setcolor(RED);
    degistir:
    int odasutun,komsuluksutun;
    odasutun=oda%(int)sqrt(boyut);
    komsuluksutun=komsuluk%(int)sqrt(boyut);
    int odasatir=oda/sqrt(boyut);
    int komsuluksatir=komsuluk/sqrt(boyut);


    if(odasatir==komsuluksatir)//AYNI SATIRDAYSA
    {
        if(oda<komsuluk)
        {
            line(125+50*(odasutun),70+50*(odasatir),125+50*(odasutun+1),70+50*(odasatir));//YATAY FORMULU
        }
        else
        {
            int degis;
            degis=oda;
            oda=komsuluk;
            komsuluk=degis;
            goto degistir;

        }
    }
    else//FARKLI SATIRDAYSA
    {
        if(oda<komsuluk)
        {
            line(125+50*(odasutun),70+50*odasatir,125+50*(odasutun),70+50*(komsuluksatir));//DİKEYİN FORMULU
        }
        else
        {
            int degis;
            degis=oda;
            oda=komsuluk;
            komsuluk=degis;
            goto degistir;
        }

    }
setcolor(WHITE);
}
