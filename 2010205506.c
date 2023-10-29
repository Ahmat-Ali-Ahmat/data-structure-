#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��renci bilgilerini saklamak i�in bir d���m yap�s� olu�turuluyor
struct Ogrenci {
    int numara;
    char isim[50];
    int yas;
    struct Ogrenci* next;
};

// Yeni bir d���m olu�turan fonksiyon
struct Ogrenci* yeniDugum(int numara, char isim[], int yas) {
    struct Ogrenci* temp = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
    temp->numara = numara;
    strcpy(temp->isim, isim);
    temp->yas = yas;
    temp->next = NULL;
    return temp;
}

// D���mleri ekrana yazan ve sayan fonksiyon
void listeyiYaz(struct Ogrenci* head) {
    struct Ogrenci* temp = head;
    int sayac = 1;

    while (temp != NULL) {
        printf("%d- %s %d %d\n", sayac, temp->isim, temp->yas, temp->numara);
        temp = temp->next;
        sayac++;
    }
}

// Listeye d���m ekleyen fonksiyon
void listeEkle(struct Ogrenci** head_ref, int numara, char isim[], int yas) {
    struct Ogrenci* temp = yeniDugum(numara, isim, yas);
    temp->next = *head_ref;
    *head_ref = temp;
}

// Klavyeden -1 girilene kadar i�lem yapan fonksiyon
void klavyeOku(struct Ogrenci** head_ref) {
    int numara, yas;
    char isim[50];

    while (1) {
        printf("Ogrenci numarasi girin (-1 toplama islem icin): ");
        scanf("%d", &numara);

        if (numara == -1) {
            break;
        }

        printf("Ogrenci ismi girin: ");
        scanf("%s", isim);

        printf("Ogrenci yasi girin: ");
        scanf("%d", &yas);

        // Tek say�lar� ba�a, �ift say�lar� sona ekliyoruz
        if (numara % 2 != 0) {
            listeEkle(head_ref, numara, isim, yas);
        } else {
            struct Ogrenci* temp = *head_ref;
            if (temp == NULL) {
                listeEkle(head_ref, numara, isim, yas);
            } else {
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                listeEkle(&(temp->next), numara, isim, yas);
            }
        }
    }
}

// Listeyi b�y�kten k����e s�ralayan ve ekrana yazd�ran fonksiyon
void buyuktenKucugeSiralaveYaz(struct Ogrenci* head) {
    // TODO: Bu k�sm� s�ralama algoritmas�na g�re doldurun
    printf("yapamadim hocam sorry:");
}

// �simlere g�re arama yapan fonksiyon
void ismeGoreAra(struct Ogrenci* head, char isim[]) {
    struct Ogrenci* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->isim, isim) == 0) {
            printf("%d- %s %d %d\n", temp->numara, temp->isim, temp->yas, temp->numara);
        }
        temp = temp->next;
    }
}

// �simlere g�re silme yapan fonksiyon
void ismeGoreSil(struct Ogrenci** head_ref, char isim[]) {
    struct Ogrenci* temp = *head_ref;
    struct Ogrenci* onceki = NULL;

    while (temp != NULL && strcmp(temp->isim, isim) != 0) {
        onceki = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("ogrenci bulunamadi.\n");
        return;
    }

    if (onceki == NULL) {
        *head_ref = temp->next;
    } else {
        onceki->next = temp->next;
    }

    free(temp);
}

// En uzun ismi olan ��renciyi yazd�ran fonksiyon
void enUzunIsimliOgrenci(struct Ogrenci* head) {
    struct Ogrenci* temp = head;
    int enUzun = 0;

    while (temp != NULL) {
        int uzunluk = strlen(temp->isim);
        if (uzunluk > enUzun) {
            enUzun = uzunluk;
        }
        temp = temp->next;
    }

    temp = head;
    while (temp != NULL) {
        if (strlen(temp->isim) == enUzun) {
            printf("Listedeki en uzun isim: %s Uzunluk: %d\n", temp->isim, enUzun);
        }
        temp = temp->next;
    }
}

int main() {
    struct Ogrenci* head = NULL;
    int secim;
    char arananIsim[50];

    do {
        printf("\n\n---------------------MENU--------------------------\n\n");
        printf("1. Ogrenci Bilgilerini Giris\n");
        printf("2. Ogrencileri buyukten kucuge sirala ve yazdir\n");
        printf("3. Ogrenci  Bilgilerini Listele\n");
        printf("4. Ogrenci  Ara\n");
        printf("5. Ogrenci  Sil\n");
        printf("6. En Uzun  isimli Ogrenci Yazdir\n");
        printf("0. cikis\n\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                klavyeOku(&head);
                break;
            case 2:
                buyuktenKucugeSiralaveYaz(head);
                break;
            case 3:
                listeyiYaz(head);
                break;
            case 4:
                printf("Aranan ismi girin: ");
                scanf("%s", arananIsim);
                ismeGoreAra(head, arananIsim);
                break;
            case 5:
                printf("Silinecek ismi girin: ");
                scanf("%s", arananIsim);
                ismeGoreSil(&head, arananIsim);
                break;
            case 6:
                enUzunIsimliOgrenci(head);
                break;
            case 0:
                printf("Program kapatiliyor...\n");
                break;
            default:
                printf("Hatali secim! Lutfen tekrar deneyin.\n");
        }
    } while (secim != 0);

    // Bellek temizleme
    while (head != NULL) {
        struct Ogrenci* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}