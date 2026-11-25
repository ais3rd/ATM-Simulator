#include <stdio.h>
#include <string.h>
#include <grphik.h>

// Deklarasi
void authenticateUser(int *authStatus);
void displayMainMenu();
int transfer(int *pBalance);
int tarikTunai(int *pBalance);
int setorTunai(int *pBalance);
void cekSaldo(int *pBalance);

// Fungsi main
int main() {
  int userBalance = 1000000; //saldo saat ini
  int isAuthenticated = 0;
  authenticateUser(&isAuthenticated);

  if (isAuthenticated) {
    while (1) {
        int menuChoice;
        displayMainMenu();
        scanf("%d", &menuChoice);
        switch (menuChoice) {
            case 1:
                cekSaldo(&userBalance);
                break;
            case 2:
                tarikTunai(&userBalance);
                break;
            case 3:
                setorTunai(&userBalance);
                break;
            case 4:
                transfer(&userBalance);
                break;
            case 5:
                printf("\nTerima kasih telah menggunakan ATM.\n");
                return 0;
                break;
            default:
                printf("Pilihan tidak valid!\n");
            }
        }
    } else {
        return 0;
        }
}

//Fungsi autentikasi
void authenticateUser(int *authStatus) {
    char pin[4]; //f1
    int attempts = 0;

    while (attempts < 3) {
        printf("Masukkan PIN (contoh: 1234): ");
        scanf("%s", pin);

        if (strcmp(pin,"1234") == 0) {
            *authStatus = 1;
            printf("Login berhasil!\n");
            return;
        }

        attempts++;
        printf("PIN salah! Sisa percobaan: %d\n", 3 - attempts);
    }
    printf("\nAkun anda terblokir karena salah memasukkan pin sebanyak 3 kali.\n");
    *authStatus = 0;
}

//Fungsi menu utama
void displayMainMenu() {
    printf("\n=== MENU ATM ===\n");
    printf("1. Cek Saldo\n");
    printf("2. Tarik Tunai\n");
    printf("3. Setor Tunai\n");
    printf("4. Transfer\n");
    printf("5. Keluar\n");
}

//Fungsi cek saldo
void cekSaldo(int *pBalance) {
    printf("=== MENU CEK SALDO ===\n");
    printf("Saldo Anda saat ini adalah: Rp%d\n", *pBalance);
}

//Fungsi setor tunai
int setorTunai(int *pBalance){
    int jumlah_setor;
    int pilihan;

    printf("=== MENU SETOR TUNAI ===\n");
    printf("Pilih nominal setoran:\n");
    printf("1. 50.000\n");
    printf("2. 100.000\n");
    printf("3. 200.000\n");
    printf("4. 500.000\n");
    printf("Pilih opsi (1-4): ");

    scanf(" %d", &pilihan);   // spasi di depan -> buang newline otomatis

    switch(pilihan){
        case 1: jumlah_setor = 50000; break;
        case 2: jumlah_setor = 100000; break;
        case 3: jumlah_setor = 200000; break;
        case 4: jumlah_setor = 500000; break;
        default:
            printf("Pilihan tidak valid!\n");
            return 0;
    }

    printf("Masukkan uang ke mesin lalu tekan ENTER...");
    getchar();

    printf("\nUang diterima!\n");

    *pBalance += jumlah_setor;
    printf("Setoran berhasil! Saldo Anda sekarang: Rp %d\n", *pBalance);

}

//Fungsi tarik tunai
int tarikTunai(int *pBalance) {
    int pilihan;
    int jumlahPenarikan = 0;


    const int KELIPATAN_PENARIKAN = 50000;
    const int SALDO_MINIMUM = 50000;
    const int MAX_PENARIKAN = 2500000;

    printf("\n=== MENU TARIK TUNAI ===\n");
    printf("1. Rp 100.000\n");
    printf("2. Rp 300.000\n");
    printf("3. Rp 500.000\n");
    printf("4. Rp 1.000.000\n");
    printf("5. Nominal Lain\n");
    printf("6. Kembali ke Menu Utama\n");
    printf("Pilihan Anda: ");
    scanf("%d", &pilihan);


    switch (pilihan) {
        case 1:
            jumlahPenarikan = 100000;
            break;
        case 2:
            jumlahPenarikan = 300000;
            break;
        case 3:
            jumlahPenarikan = 500000;
            break;
        case 4:
            jumlahPenarikan = 1000000;
            break;
        case 5:
            printf("Masukkan jumlah penarikan (kelipatan 50.000): ");
            scanf("%d", &jumlahPenarikan);

            if (jumlahPenarikan % KELIPATAN_PENARIKAN != 0) {
                printf("Gagal: Jumlah harus kelipatan 50.000.\n");
                return 0; // Keluar fungsi jika kelipatan salah
            }
            break;
        case 6:
            printf("Transaksi dibatalkan.\n");
            return 0;
        default:
            printf("Pilihan tidak valid!\n");
            return 0;
    }


    if (jumlahPenarikan <= 0) {
        printf("Jumlah penarikan tidak valid.\n");
    }

    else if (jumlahPenarikan > MAX_PENARIKAN) {
        printf("Gagal: Penarikan melebihi batas maksimum per transaksi (Maks: Rp %d)\n", MAX_PENARIKAN);
    }

    else if ((*pBalance - jumlahPenarikan) < SALDO_MINIMUM) {
        printf("Gagal: Saldo Anda tidak mencukupi (Harus menyisakan saldo Rp %d).\n", SALDO_MINIMUM);
        printf("Saldo Anda saat ini: Rp %d\n", *pBalance);
    }

    else {
        *pBalance = *pBalance - jumlahPenarikan;
        printf("--------------------------------\n");
        printf("Penarikan Berhasil!\n");
        printf("Silakan ambil uang Anda: Rp %d\n", jumlahPenarikan);
        printf("Sisa saldo Anda: Rp %d\n", *pBalance);
        printf("--------------------------------\n");
    }

    return 1;
}

//Fungsi transfer
int transfer(int *pBalance){
    int jumlah_transfer;
    char rek_tujuan[20];
    int pilihan_bank;
    int saldo_minimum = 50000;
    int biaya_admin = 6500;
    char decision;
    int ToF = 0;
    typedef struct{
        char kode_bank[4];
        char rek[20];
        char nama[10];
    } contoh;

    printf("=== MENU TRANSFER ===\n");
    printf("Pilih bank tujuan:\n");
    printf("1. Sesama Bank (Gratis)\n");
    printf("2. Bank Lain (Biaya Admin Rp. 6500)\n");
    printf("3. Kembali ke Menu Utama\n");
    scanf("%d", &pilihan_bank);

    if(pilihan_bank == 1){
        contoh sesama_bank[3] = {
            {"", "502605987654321", "Anindya"},
            {"", "502606987654321", "Gilang"},
            {"", "502607987654321", "Tasya"}
        };
        printf("Masukkan Nomor Rekening Tujuan: \n");
        scanf("%s", rek_tujuan);
        printf("Masukkan Jumlah Transfer: \n");
        scanf("%d", &jumlah_transfer);

        if(jumlah_transfer < 0){
            printf("Jumlah transfer tidak valid\n");
        }
        else if ((*pBalance - jumlah_transfer) <= saldo_minimum){
            printf("Saldo anda tidak mencukupi untuk transfer ini\n");
        }
        else {
            for(int i = 0; i < 3; i++){
                if(strcmp(rek_tujuan, sesama_bank[i].rek) == 0){
                    ToF = 1;
                    printf("Apakah anda yakin ingin transfer ke:\nNama = %s\nNomor Rekening = %s\nJumlah Uang = %d\nKetik Y untuk lanjut dan N untuk henti transaksi\n", sesama_bank[i].nama, rek_tujuan, jumlah_transfer);
                    scanf(" %c", &decision);
                if(decision == 'Y' || decision == 'y'){
                    *pBalance = *pBalance - jumlah_transfer;
                    printf("Transfer ke %s sejumlah %d berhasil\n", rek_tujuan, jumlah_transfer);
                    printf("Sisa saldo: %d\n", *pBalance);
                }
                else if(decision == 'N' || decision == 'n'){
                    printf("Transaksi dibatalkan");
                }
                else{
                    printf("Pilihan tidak valid!");
                }
                    break;
                }
            }

            if(ToF == 0){
                printf("Rekening yang Anda tuju tidak terdaftar!");
            }
        }
    }


    else if(pilihan_bank == 2){
        contoh beda_bank[3] = {
            {"009", "502325987654321", "Reyhan"},
            {"008", "502324987654321", "Viona"},
            {"002", "502323987654321", "Arvin"}
        };
        char kode_bank[4];
        printf("Daftar bank yang bisa dituju:\n");
        printf("1. Bank Mandiri (009)\n");
        printf("2. Bank BNI (008)\n");
        printf("3. Bank BRI (002)\n");
        printf("Masukkan 3 digit kode bank yang ingin dituju: \n");
        scanf("%s", kode_bank);
        printf("Masukkan nomor rekening tujuan: \n");
        scanf("%s", rek_tujuan);
        printf("Masukkan Jumlah Transfer: \n");
        scanf("%d", &jumlah_transfer);

        if(jumlah_transfer <= 0){
            printf("Jumlah transfer tidak valid\n");
        }
        else if ((*pBalance - jumlah_transfer - biaya_admin) < saldo_minimum){
            printf("Saldo anda tidak mencukupi untuk transfer ini\n");
        }
        else {
            for(int i = 0; i < 3; i++){
                if(strcmp(rek_tujuan, beda_bank[i].rek) == 0 && strcmp(kode_bank, beda_bank[i].kode_bank) == 0){
                    ToF = 1;
                    printf("Apakah anda yakin ingin transfer ke:\nNama = %s\nNomor Rekening = %s\nJumlah Uang = %d\nKetik Y untuk lanjut dan N untuk henti transaksi\n", beda_bank[i].nama, rek_tujuan, jumlah_transfer);
                    scanf(" %c", &decision);

                    if(decision == 'Y' || decision == 'y'){
                      *pBalance = *pBalance - jumlah_transfer - biaya_admin;
                      printf("Transfer ke %s sejumlah %d berhasil\n", rek_tujuan, jumlah_transfer);
                      printf("Sisa saldo: %d\n", *pBalance);
                    }
                    else if(decision == 'N' || decision == 'n'){
                      printf("Transaksi dibatalkan");
                    }
                    else{
                      printf("Pilihan tidak valid!");
                    }
                    break;
                }
            }

            if(ToF == 0){
                printf("Rekening yang Anda tuju tidak terdaftar!");
            }
        }
    } else if(pilihan_bank == 3){
      printf("Kembali ke Menu Utama...");
      return 0;
    }

    else{
        printf("Pilihan bank tidak valid\n");
    }
    }
