#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Öğrenci bilgilerini tutan bir yapı tanımlıyoruz
struct ogrenci
{
    int numara;              // Öğrenci numarası
    char isim[20];           // Öğrenci ismi
    int yas;                 // Öğrenci yaşı
    struct ogrenci *sonraki; // Sonraki düğümü gösteren bir işaretçi
};

// Bağlı listeyi başlatan bir işaretçi tanımlıyoruz
struct ogrenci *bas = NULL;

// Bağlı listeye yeni bir düğüm ekleyen bir fonksiyon tanımlıyoruz
void ekle(int numara, char isim[], int yas)
{
    // Yeni bir düğüm için bellek ayırıyoruz
    struct ogrenci *yeni = (struct ogrenci *)malloc(sizeof(struct ogrenci));
    // Yeni düğüme verileri kopyalıyoruz
    yeni->numara = numara;
    strcpy(yeni->isim, isim);
    yeni->yas = yas;
    // Yeni düğümü listenin başına ekliyoruz
    yeni->sonraki = bas;
    bas = yeni;
}

// Bağlı listeyi dolaşan ve öğrenci bilgilerini ekrana yazan ve sayan bir fonksiyon tanımlıyoruz
void yazdir()
{
    // Geçici bir işaretçi tanımlıyoruz
    struct ogrenci *gecici = bas;
    // Bir sayaç tanımlıyoruz
    int sayac = 0;
    // Listeyi sonuna kadar dolaşıyoruz
    while (gecici != NULL)
    {
        // Sayaç değerini artırıyoruz
        sayac++;
        // Öğrenci bilgilerini ekrana yazdırıyoruz
        printf("%d- %s %d %d\n", sayac, gecici->isim, gecici->yas, gecici->numara);
        // Geçici işaretçiyi sonraki düğüme ilerletiyoruz
        gecici = gecici->sonraki;
    }
    // Toplam öğrenci sayısını ekrana yazdırıyoruz
    printf("Toplam %d öğrenci var.\n", sayac);
}

// Bağlı listede öğrenci ismine göre arama yapan bir fonksiyon
struct ogrenci *ara(struct ogrenci *bas, char isim[])
{
    // Geçici bir işaretçi tanımlıyoruz
    struct ogrenci *gecici = bas;
    // Listeyi sonuna kadar dolaşıyoruz
    while (gecici != NULL)
    {
        // Eğer isim öğrencinin ismiyle eşleşirse
        if (strcmp(gecici->isim, isim) == 0)
        {
            // O öğrenciyi döndürüyoruz
            return gecici;
        }
        // Eşleşmezse sonraki düğüme geçiyoruz
        gecici = gecici->sonraki;
    }
    // Listenin sonuna gelirsek NULL döndürüyoruz
    return NULL;
}

// Bağlı listede aranan öğrenci adının yer aldığı düğümden bir sonraki düğümü silen bir fonksiyon
void sil(struct ogrenci *bas, char isim[])
{
    // Eğer listenin başındaki düğümün ismi aranan isimse
    if (strcmp(bas->isim, isim) == 0)
    {
        struct ogrenci *silinecek = bas;
        bas = bas->sonraki;
        free(silinecek);
    }
    else
    {
        // Geçici bir işaretçi tanımlıyoruz
        struct ogrenci *gecici = bas;
        // Listenin sonuna kadar dolaşıyoruz
        while (gecici != NULL && gecici->sonraki != NULL)
        {
            if (strcmp(gecici->sonraki->isim, isim) == 0)
            {
                struct ogrenci *silinecek = gecici->sonraki;
                gecici->sonraki = silinecek->sonraki;
                free(silinecek);
                break;
            }
            gecici = gecici->sonraki;
        }
    }
}

// Bağlı listede en uzun ismin olduğu kaydı yazdıran bir fonksiyon
void en_uzun_isim(struct ogrenci *bas)
{
    // Geçici bir işaretçi tanımlıyoruz
    struct ogrenci *gecici = bas;
    // En uzun ismi ve uzunluğunu tutacak değişkenler tanımlıyoruz
    char en_uzun[20] = "";
    int uzunluk = 0;
    // Listeyi sonuna kadar dolaşıyoruz
    while (gecici != NULL)
    {
        // Eğer öğrencinin isminin uzunluğu en uzun değişkeninin uzunluğundan büyükse
        if (strlen(gecici->isim) > strlen(en_uzun))
        {
            // En uzun değişkenine öğrencinin ismini kopyalıyoruz
            strcpy(en_uzun, gecici->isim);
            // Uzunluk değişkenine öğrencinin isminin uzunluğunu atıyoruz
            uzunluk = strlen(gecici->isim);
        }
        // Sonraki düğüme geçiyoruz
        gecici = gecici->sonraki;
    }
    // En uzun ismi ve uzunluğunu ekrana yazdırıyoruz
    printf("Listedeki en uzun isim: %s\n", en_uzun);
    printf("Uzunluk: %d\n", uzunluk);
}

// Sayıları sıralamak için bir fonksiyon
void sort_ascending(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Dinamik dizi ve ekleme fonksiyonu
void add_numbers(int *list, int *index, int size)
{
    int num;
    int odd = 0;
    int even = size - 1;
    do
    {
        printf("Bir sayi giriniz (-1 cikis): ");
        scanf("%d", &num);
        if (num != -1)
        {
            if (num % 2 == 0)
            {
                list[even] = num;
                even--;
            }
            else
            {
                list[odd] = num;
                odd++;
            }
            (*index)++;
        }
    } while (num != -1 && *index < size);
}

int main()
{
    int choice;

    while (1)
    {
        printf("\nMenü:\n");
        printf("1. Öğrenci Ekle\n");
        printf("2. Öğrenci Ara\n");
        printf("3. Öğrenci Sil\n");
        printf("4. Öğrenci Listele\n");
        printf("5. En Uzun İsmi Bul\n");
        printf("6. Rastgele Sayıları Sırala\n");
        printf("7. Sayı Ekleme\n");
        printf("8. Çıkış\n");
        printf("Seçiminizi yapın: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int numara, yas;
            char isim[20];
            printf("Öğrenci numarası: ");
            scanf("%d", &numara);
            printf("Öğrenci ismi: ");
            scanf("%s", isim);
            printf("Öğrenci yaşı: ");
            scanf("%d", &yas);
            ekle(numara, isim, yas);
            printf("Öğrenci eklendi.\n");
            break;
        }
        case 2:
        {
            char isim[20];
            printf("Aramak istediğiniz ismi giriniz: ");
            scanf("%s", isim);
            struct ogrenci *sonuc = ara(bas, isim);
            if (sonuc != NULL)
            {
                printf("Öğrencinin numarası: %d\n", sonuc->numara);
                printf("Öğrencinin ismi: %s\n", sonuc->isim);
                printf("Öğrencinin yaşı: %d\n", sonuc->yas);
            }
            else
            {
                printf("Aradığınız isimde bir öğrenci bulunamadı.\n");
            }
            break;
        }
        case 3:
        {
            char isim[20];
            printf("Silmek istediğiniz ismi giriniz: ");
            scanf("%s", isim);
            sil(bas, isim);
            printf("Öğrenci silindi.\n");
            break;
        }
        case 4:
            yazdir();
            break;
        case 5:
            en_uzun_isim(bas);
            break;
        case 6:
        {
            int numbers[100];
            int n = sizeof(numbers) / sizeof(numbers[0]);
            srand(time(0));
            for (int i = 0; i < n; i++)
            {
                numbers[i] = rand() % (102 - 54 + 1) + 54;
            }
            sort_ascending(numbers, n);
            printf("Sıralanmış Sayılar: ");
            for (int i = 0; i < n; i++)
            {
                printf("%d", numbers[i]);
                if (i < n - 1)
                {
                    printf("->");
                }
            }
            printf("\n");
            break;
        }
        case 7:
        {
            int size = 10;
            int *list = (int *)malloc(size * sizeof(int));
            int index = 0;
            add_numbers(list, &index, size);
            printf("Listedeki elemanlar:\n");
            for (int i = 0; i < index; i++)
            {
                printf("%d ", list[i]);
            }
            printf("\n");
            free(list);
            break;
        }
        case 8:
            exit(0);
        default:
            printf("Geçersiz seçenek!\n");
            break;
        }
    }

    return 0;
}
