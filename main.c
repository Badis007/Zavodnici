/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Badis
 *
 * Created on 23. dubna 2020, 16:50
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SOUBOR "zavodnici.txt"
#define ODDELOVAC " \n"
#define VYSTUP "listina.txt"
/*
 * 
 */



int main(int argc, char** argv) {
    typedef struct{
        int cislo;
        char prijmeni[20];
        char jmeno[20];
        char cas1[10];
        char cas2[10];
    }ZAVODNIK;
    
    char retezec[100];
    int pocet =0;
    int pocetSloupcu=0;
    char *pch;
    int i;
    int casCelkem=0;
    
    FILE * pFile;
    ZAVODNIK *zavodnici=NULL;
    
    if ((pFile = fopen(SOUBOR,"r"))== NULL){
        printf("Soubor %s nebyl otevren.\n",SOUBOR);
        return EXIT_FAILURE;
    }
    
    while(fgets(retezec,100,pFile)!=NULL){
        if(pocet>0){
            zavodnici = (ZAVODNIK*) realloc(zavodnici,pocet * sizeof(ZAVODNIK));
            pocetSloupcu=1;
            pch = strtok(retezec,ODDELOVAC);
            while(pch !=NULL){
                switch(pocetSloupcu){
                    case 1:
                        zavodnici[pocet-1].cislo=atoi(pch);
                        break;
                    case 2:
                        strcpy(zavodnici[pocet-1].prijmeni,pch);
                        break;
                    case 3:
                        strcpy(zavodnici[pocet-1].jmeno,pch);
                        break;
                    case 4:
                        strcpy(zavodnici[pocet-1].cas1,pch);
                        break;
                    case 5:
                        strcpy(zavodnici[pocet-1].cas2,pch);
                        break;
                }
                pch = strtok(NULL,ODDELOVAC);
                pocetSloupcu++;
            }
        }
        pocet++;
    }
    
    if(fclose(pFile)==EOF){
        printf("Nebyl zavren vas soubor %s.\n",SOUBOR);
    }
    
    printf("STARTOVNI LISTINA - SLALOM ZENY\n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("cislo  |  prijmeni  |   jmeno   |  cas-1  |  cas-2  |   celkem   |\n");
    printf("----------------------------------------------------------------------------------------\n");
    pocet--;
    
    for(i=0;i<pocet;i++){
       // casCelkem += zavodnici[i].cas1+zavodnici[i].cas2;
        printf("%d %15s %10s %12s %10s\n",zavodnici[i].cislo,zavodnici[i].prijmeni,zavodnici[i].jmeno,zavodnici[i].cas1,zavodnici[i].cas2);
    }
    
    if((pFile = fopen(VYSTUP,"w"))==NULL){
        printf("Soubor %s nebyl otevren",VYSTUP);
        return EXIT_FAILURE;
    }
    
    fprintf(pFile,"VYSLEDKOVA LISTINA");
    fprintf(pFile,"----------------------------------------------------------------------------------------\n");
    fprintf(pFile,"cislo  |  prijmeni  |   jmeno   |  cas-1  |  cas-2  |   celkem   |\n");
    fprintf(pFile,"----------------------------------------------------------------------------------------\n");
    for(i=0;i<pocet;i++){
       // casCelkem += zavodnici[i].cas1+zavodnici[i].cas2;
        fprintf(pFile,"%d %15s %10s %12s %10s\n",zavodnici[i].cislo,zavodnici[i].prijmeni,zavodnici[i].jmeno,zavodnici[i].cas1,zavodnici[i].cas2);
    }
    
    if(fclose(pFile)==EOF){
        printf("Nebyl zavren vas soubor %s\n",VYSTUP);
    }else{
        printf("Byl vytvoren soubor %s.\n",VYSTUP);
    }
    return (EXIT_SUCCESS);
}

