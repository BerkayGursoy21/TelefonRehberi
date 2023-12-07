#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Bir kiþinin Rehberdeki Bilgileri
struct Kisi {
    char ad[50];
    char soyad[50];
    char numara[15];
};
//Fonksiyonlar
void kisiEkle();
void kisileriGoruntule();
void kisiSil();
void cikisYap();
//Karþýlama Ekraný
int main() {
    printf("**********************************************\n");
    printf("          Telefon Rehberi Uygulamasi       \n");
    printf("**********************************************\n");

    printf("Programa girmek icin Enter'a basin.\n");
    getchar(); 
    
    system("clear || cls");
// ANA REHBER MENÜSÜ
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("          Telefon Rehberi       \n");
    printf("++++++++++++++++++++++++++++++++++++\n");
    int secim;
// YAPIALCAK ÝÞLEM SEÇÝM MENÜSÜ
    while (1) {
        printf("\n1.Kisileri Goruntule\n");
        printf("2. Kisi Ekle\n");
        printf("3. Kisi Sil\n");
        printf("4. Cikis Yap\n");
        printf("\nYapmak istediginiz islemi seciniz: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                kisileriGoruntule();
                break;
            case 2:
                kisiEkle();
                break;
            case 3:
                kisiSil();
                break;
            case 4:
                cikisYap();
                break;
            default:
                printf("Yanlýs Secim!. Tekrar deneyin.\n");
        }
    }
 return 0;
}
//REHBERE KÝÞÝ EKLEME
void kisiEkle() {
    struct Kisi kisi;

    printf("Ad: ");
    scanf("%s", kisi.ad);

    printf("Soyad: ");
    scanf("%s", kisi.soyad);

    printf("Numara: ");
    scanf("%s", kisi.numara);

    FILE *dosya = fopen("rehber.txt", "a");
    if (dosya == NULL) {
        printf("*****Dosya Bulunamadý!*****\n");
        exit(1);
    }

    fprintf(dosya, "%s %s %s\n", kisi.ad, kisi.soyad, kisi.numara);
    fclose(dosya);

    printf("Kisi Rehbere Eklendi.\n");
}
//REHBERDEKÝ KÝÞÝLERÝ GÖRÜNTÜLEME
void kisileriGoruntule() {
    char ad[50], soyad[50], numara[15];
	system("clear || cls");
// "rehber.txt" DOSYASINI OKUYUP EKRANA YAZDIRIR	
    FILE *dosya = fopen("rehber.txt", "r");
    if (dosya == NULL) {
        printf("*****Dosya Bulunamadý!*****\n");
        exit(1);
    }

    fseek(dosya, 0, SEEK_SET);
    printf("TELEFON REHBERINDEKI KISILER:\n");
    while (fscanf(dosya, "%s %s %s", ad, soyad, numara) == 3) {
        printf("%s %s %s\n", ad, soyad, numara);
    }

    fclose(dosya);
}
//REHBERDEN KÝÞÝ SÝLME BÖLÜMÜ
void kisiSil() {
    char ad[50], soyad[50], numara[15];
    char silinecekAd[50], silinecekSoyad[50];

    printf("Silinecek kisinin adini girin: ");
    scanf("%s", silinecekAd);

    printf("Silinecek kisinin soyadini girin: ");
    scanf("%s", silinecekSoyad);
// "rehber.txt" DOSYASINI OKUYUP KONTROL EDER
// GEÇÝCÝ DOSYAYI YAZMAK ÝÇÝN AÇAR
    FILE *dosya = fopen("rehber.txt", "r");
    FILE *geciciDosya = fopen("gecici.txt", "w");

    if (dosya == NULL || geciciDosya == NULL) {
        printf("*****Dosyalar Bulunamadý!*****\n");
        exit(1);
    }

    while (fscanf(dosya, "%s %s %s", ad, soyad, numara) == 3) {
        if (strcmp(ad, silinecekAd) == 0 && strcmp(soyad, silinecekSoyad) == 0) {
            printf("%s %s %s silindi.\n", ad, soyad, numara);
        } else {
            fprintf(geciciDosya, "%s %s %s\n", ad, soyad, numara);
        }
    }

    fclose(dosya);
    fclose(geciciDosya);
    
        
    remove("rehber.txt");
    rename("gecici.txt", "rehber.txt");
}

void cikisYap() {
    printf("*****Programdan cikiliyor...*****\n");
    exit(0);
}

