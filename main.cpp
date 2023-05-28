#include <iostream>
#include <winbgim.h>
#include <windows.h>
#include <fstream>
#include <time.h>

#define latime 50

#define stg 75
#define drp 77
#define sus 72
#define jos 80
#define esc 27

#define directieStanga 0
#define directieDreapta 1
#define directieSus 2
#define directieJos 3

#define MAX 20

using namespace std;

int n, ip, jp, is, js, dirSoarece, dirPisica, tasta, i, j, ipPisica,ipSoarece,diamante=0;
int vieti=1;
char sirVieti[10],sirDiamante[10];
char labirint[MAX][MAX];

char car;

ifstream fin("llabirint.txt");

void deseneaza(char car, int i, int j){
    if(car=='1')
                readimagefile("brick.jpg", j*latime, i*latime, (j+1)*latime, (i+1)*latime);
            else if(car=='0')
                readimagefile("blank.jpg", j*latime, i*latime, (j+1)*latime, (i+1)*latime);
                else if(car=='2')
                    readimagefile("cheese.jpg", j*latime, i*latime, (j+1)*latime, (i+1)*latime);
                    else if(car=='3')
                        readimagefile("diamant.jpg", j*latime, i*latime, (j+1)*latime, (i+1)*latime);
}

void deseneazaPisica(){
switch(ipPisica){
   case 1: readimagefile("pisica1.jpg", latime*jp,latime*ip,latime*(jp+1),latime*(ip+1)); break;
case 2:
    readimagefile("pisica2.jpg", latime*jp,latime*ip,latime*(jp+1),latime*(ip+1)); break;
case 3:
    readimagefile("pisica3.jpg", latime*jp,latime*ip,latime*(jp+1),latime*(ip+1)); break;
case 4:
    readimagefile("pisica4.jpg", latime*jp,latime*ip,latime*(jp+1),latime*(ip+1)); break;
}
 }

void deseneazaSoarece(){
switch (ipSoarece){
  case 1:  readimagefile("soarece1.jpg", latime*js,latime*is,latime*(js+1),latime*(is+1)); break;
case 2:
    readimagefile("soarece2.jpg", latime*js,latime*is,latime*(js+1),latime*(is+1)); break;
case 3:
    readimagefile("soarece3.jpg", latime*js,latime*is,latime*(js+1),latime*(is+1)); break;
case 4:
    readimagefile("soarece4.jpg", latime*js,latime*is,latime*(js+1),latime*(is+1)); break;
}
}

void stergeSoarece()
{
    deseneaza(labirint[is][js],is,js);
}

void stergePisica(){

    deseneaza(labirint[ip][jp],ip,jp);
}

void citesteLabirint()
{
    fin>>n>>ip>>jp>>is>>js;

    for(i=0; i < n; i++)
        for(j=0; j < n; j++){
            fin>>car;
            labirint[i][j]=car;
        }
fin.close();
}

void incarcaLabirint()
{int car;
    for(j=0; j<n; j++)
        for(i=0; i<n; i++)
             deseneaza(labirint[i][j],i,j);
}




void dirMisSoarece()
{
    dirSoarece=rand()%4;

    switch(dirSoarece)
    {
        case directieStanga: if(js > 0 && (labirint[is][js-1]=='0' || labirint[is][js-1]=='2') ) js--; break;
        case directieDreapta: if(js < n-1 && (labirint[is][js+1]=='0' || labirint[is][js+1]=='2') ) js++; break;
        case directieSus: if(is > 0 && (labirint[is-1][js]=='0' || labirint[is-1][js]=='2') ) is--; break;
        case directieJos: if(is < n-1 && labirint[is+1][js]=='0' || labirint[is+1][js]=='2') is++; break;
    }
}

void dirMisPisica()
{
    if(kbhit())
    {
        tasta=getch();
        if(tasta==esc){ closegraph(),exit(1);}
        if(tasta==0)
        {
            tasta=getch();
            switch(tasta)
            {
            case stg: dirPisica=directieStanga; break;
            case drp: dirPisica=directieDreapta; break;
            case sus: dirPisica=directieSus; break;
            case jos: dirPisica=directieJos; break;
            }
        }

        switch(dirPisica)
        {
           case directieDreapta: if(jp < n-1 && (labirint[ip][jp+1]=='0' || labirint[ip][jp+1]=='3') ) jp++; break;
           case directieStanga: if(jp > 0 && (labirint[ip][jp-1]=='0' || labirint[ip][jp-1]=='3') )  jp--; break;
           case directieSus: if(ip > 0 && (labirint[ip-1][jp]=='0' || labirint[ip-1][jp]=='3') ) ip--; break;
           case directieJos: if(ip < n-1 && (labirint[ip+1][jp]=='0' || labirint[ip+1][jp]=='3') ) ip++; break;
        }
    }
}

void ipostazaPisica()
{
    switch(dirPisica)
    {
           case directieDreapta: ipPisica=3; break;
           case directieStanga: ipPisica=4; break;
           case directieSus: ipPisica=1; break;
           case directieJos: ipPisica=2; break;
    }
}

void ipostazaSoarece()
{
    switch(dirSoarece)
    {
        case directieDreapta: ipSoarece=3; break;
        case directieStanga: ipSoarece=4; break;
        case directieSus: ipSoarece=1; break;
        case directieJos: ipSoarece=2; break;
    }
}
void stergeCascaval()
{if(labirint[is][js]=='2')
   {labirint[is][js]='0';
    deseneaza(labirint[is][js],is,js);}
}
void soareceManancaCascaval()
{
   //if(js==j && is==i && labirint[i][j]==2)
  stergeCascaval();

}
void afisareVieti()
{if(vieti>=0)
    {itoa(vieti, sirVieti, 10);
    outtextxy(30,0, sirVieti);}

}

void cresteVieti(){
if(labirint[is][js]=='2') vieti++;}

void stergeDiamant()
{if(labirint[ip][jp]=='3')
   {labirint[ip][jp]='0';
    deseneaza(labirint[ip][jp],ip,jp);}
}

void soarecePisicaManancaDiamant()
{
   //if(js==j && is==i && labirint[i][j]==2)
  stergeDiamant();

}

void afisareDiamanteCulese()
{
    itoa(diamante, sirDiamante, 10);
    outtextxy(114,14, sirDiamante);
}

void cresteDiamante(){
if(labirint[ip][jp]=='3') diamante++;}

int main()
{srand(time(NULL));
HWND consola=GetConsoleWindow();
ShowWindow(consola,SW_HIDE);
citesteLabirint();
initwindow(n*latime, n*latime, "Tom si Jerry");
PlaySound("tomandjerry.wav",NULL,SND_ASYNC | SND_LOOP);
readimagefile("tj.jpg", 0,0,n*latime, n*latime);
getch();
incarcaLabirint();
//ipPisica=4;
setbkcolor(WHITE);
setcolor(BLACK);

itoa(vieti, sirVieti, 10);
itoa(diamante, sirDiamante, 10);

outtextxy(0,30,"Castigi dupa ce colectezi si toate diamantele");

outtextxy(0,0,"Vieti: ");
outtextxy(30,0, sirVieti);
outtextxy(0,14,"Diamante culese: ");
outtextxy(114,14,sirDiamante);

dirPisica=directieStanga;
deseneazaPisica();
ipSoarece=1;
deseneazaSoarece();

 do {
        stergeSoarece();
        dirMisSoarece();
        for (int i=1;i<=2;i++)
            {
                ipostazaSoarece();
                deseneazaSoarece();
                 delay(10);
            }

            do
       { cresteVieti();
           soareceManancaCascaval();
        afisareVieti();
       // if(vieti==0)
           // outtextxy(0,43,"Colecteaza toate diamantele pentru a castiga");
        }
        while(labirint[is][js]=='2');

         do
       { cresteDiamante();
           soarecePisicaManancaDiamant();

                afisareDiamanteCulese();}

        while(labirint[ip][jp]=='3');

          stergePisica();
        dirMisPisica();
        ipostazaPisica();
        deseneazaPisica();

        if (ip==is && jp==js && vieti!=0)
            {vieti--;
            }

        if(ip)
            if(vieti==0 && diamante==9)
            {afisareVieti();
            outtextxy(0,47,"Ai castigat!");
            setcolor(WHITE);
            setbkcolor(BROWN);
                PlaySound("tomlaughing.wav",NULL,SND_SYNC);
                delay(5000);
                closegraph();
                exit(0);
            }
        delay(50);
    } while (tasta!=esc);
    ShowWindow(consola,SW_HIDE);
getch();
closegraph();
    return 0;
}
