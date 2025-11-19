#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define F 5
#define P 3

typedef struct { char t; int id; } Peca;
Peca f[F], p[P];
int fr=0, tr=0, to=-1, id=1;

Peca g() { char ts[]={'I','O','T','L'}; return (Peca){ts[rand()%4], id++}; }

void e() { 
    printf("Fila: ");
    for(int i=0,ix=fr;i<F;i++,ix=(ix+1)%F) printf("[%d:%c] ",f[ix].id,f[ix].t);
    printf("\nPilha: ");
    for(int i=to;i>=0;i--) printf("[%d:%c] ",p[i].id,p[i].t);
    printf("\n");
}

void j() { 
    printf("Jogando [%d:%c]\n",f[fr].id,f[fr].t);
    fr=(fr+1)%F; f[tr]=g(); tr=(tr+1)%F;
}

void r() { 
    if(to==P-1) { printf("Pilha cheia!\n"); return; }
    p[++to]=f[fr]; printf("Reservando [%d:%c]\n",f[fr].id,f[fr].t);
    fr=(fr+1)%F; f[tr]=g(); tr=(tr+1)%F;
}

void u() {
    if(to==-1) { printf("Pilha vazia!\n"); return; }
    printf("Usando reserva [%d:%c]\n",p[to].id,p[to].t);
    f[tr]=p[to--]; tr=(tr+1)%F;
}

void t() {
    if(to==-1) { printf("Pilha vazia!\n"); return; }
    Peca tmp=f[fr]; f[fr]=p[to]; p[to]=tmp;
    printf("Trocado!\n");
}

void i() {
    if(to!=-1) { printf("Pilha deve estar vazia!\n"); return; }
    for(int i=0;i<F;i++) p[++to]=f[(fr+i)%F];
    for(int i=0;i<F;i++) f[(fr+i)%F]=p[to--];
    printf("Fila invertida!\n");
}

int main() {
    srand(time(NULL));
    for(int i=0;i<F;i++) { f[tr]=g(); tr=(tr+1)%F; }
    int o;
    do {
        e();
        printf("\n1-Jogar 2-Reservar 3-Usar\n4-Trocar 6-Inverter 0-Sair: ");
        scanf("%d",&o);
        if(o==1) j(); else if(o==2) r(); else if(o==3) u();
        else if(o==4) t(); else if(o==6) i();
    } while(o!=0);
    return 0;
}