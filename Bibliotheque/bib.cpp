#include "iostream"
#include "cstring"
#include "iomanip"
#include "time.h"
#include "stdio.h"
#include "conio.h"
#include "windows.h"
using namespace std;

long total_book = 0; // Total book in the library
long total_bill = 0;
long total = 0;
char id_temp[50];
int i,p;
int info[10];

//=============================================================================================
//
//  DECLARATION DE STRUCT
//
//=============================================================================================
struct n_DATE{
    int n_day;
    int n_month;
    int n_year;
};

struct BOOK{
    char b_id[50];
    char b_nom[50];
    char b_autor[50];
    char b_categorie[50];
    char b_distributeur[50];
    int b_quantite;
};

struct BILL {
    char bill_nomEtu[50];
    char bill_idEtu[50];
    n_DATE bill_dateEmprunt;
};

struct BILL_DETAIL {
    char detail_idEtu[50];
    char detail_idBook[50];
    char detail_nomBook[50];
    char b_checkReturn[50];
    char b_new_old[50]; // status 

};

typedef BOOK LIST_BOOK[100]; 
typedef BILL LIST_BILL[100];
typedef BILL_DETAIL LIST_DETAIL[100];

LIST_BOOK lst_book; // Array of 50 books
LIST_BILL lst_bill;
LIST_DETAIL lst_detail;

//=============================================================================================
//
//  DECLARATION DE METHODES
//
//=============================================================================================

int days_in_month(int,int);

//_____________________________________________________________________________________________

void bill_load_file();
void bill_save_file();
void bill_input();
void bill_output();
void bill_add();
void bill_del();
int bill_search(char id_temp[]);
void bill_modifie();

//_____________________________________________________________________________________________

void ctbill_input();
void ctbill_output();
void ctbill_load_file();
void ctbill_save_file();

//_____________________________________________________________________________________________
void book_load_file();
void book_save_file();
void book_input();
void book_output();
void book_modifie();
void book_add();
void book_del();
int book_search(char id_temp[]);

//_____________________________________________________________________________________________
void compte_categorie();
void compte_etu_outdate();
void compte_book_ponctuel();
void compte_nombre_book();

//_____________________________________________________________________________________________
void file_info();
void interface_main();
void interface_book_manager();
void interface_bill_manager();
void interface_bill_detail_manager();

//// MAIN.
////===============================================================================================
////===============================================================================================
//                                                                                              //         
    int main()                                                                                 //
    {                                                                                           //
        interface_main();  
        return 1;                                                                     // 
    }                                                                                           //
//                                                                                              // 
////===============================================================================================
////===============================================================================================


////===============================================================================================
//
//  MENU METHODES
//
////===============================================================================================

void interface_book_manager(){
    begin:
    cout << endl << endl;
    cout << "               +-------------------------------------------------+ \n";
    cout << "               |      INTERFACE DE MANAGEMENT DANS LA BIB        | \n";
    cout << "               |-------------------------------------------------| \n";
    cout << "               |                                                 | \n";
    cout << "               |  1. Importer des livres dans la bibliothque.    | \n";
    cout << "               |  2. Supprimer un livre.                         | \n";
    cout << "               |  3. Afficher la liste des livres.               | \n";
    cout << "               |                                                 | \n";
    cout << "               |  4. Ajouter un livre.                           | \n";
    cout << "               |  5. Chercher des livres.                        | \n";
    cout << "               |  6. Modifier un livre.                          | \n";
    cout << "               |                                                 | \n";
    cout << "               |  7. Back.                                       | \n";
    cout << "               |                                                 | \n";
    cout << "               +-------------------------------------------------+ \n";

    char choix;
    bool k = true;

    do
    {
        if(k == false)
            cout << "Veuillez choisir une action entre 1-3 ";
        else
            cout << "Veuillez choisir des actions correspondantes des numeros indiques "; cin >> choix;
        k = false;
    } while((choix < '1') || (choix > '7'));

    switch(choix){
        case '1': book_input();
            break;
        case '2': book_del();
            break;
        case '3': book_output();
            break;
        case '4': book_add();
            break;
        case '5': 
            cin.ignore();
            cout << "Entrer ID Livre doit etre cherche : "; cin.getline(id_temp, 50);
            i = book_search(id_temp);

            if(i == 0)
                cout << "- Ne pouvoir pas trouver le livre qui a le ID ci-dessur!";
            else {
                cout << "\n Trouver le livre : \n";
                cout << setw(13) << ". ID Livre" << setw(13) << "Nom du livre" << setw(13) << "Categorie" << setw(13) << "Quantite" << endl << endl;
                cout << setw(13) << lst_book[i].b_id << setw(13) << lst_book[i].b_nom << setw(13) << lst_book[i].b_categorie << setw(13) << lst_book[i].b_quantite;
                cout << endl;
            }
            break;
        case '6':
            book_modifie();
            break;
        case '7':
            goto end;
            break;
        
    }
    goto begin;
end:;
}

void interface_bill_manager(){
    begin:
    cout << endl << endl;
    cout << "               +-------------------------------------------------+ \n";
    cout << "               |      INTERFACE DE MANAGEMENT DES TICKETS        | \n";
    cout << "               |-------------------------------------------------| \n";
    cout << "               |                                                 | \n";
    cout << "               |  1. Importer ticket.                            | \n";
    cout << "               |  2. Ajouter ticket.                             | \n";
    cout << "               |  3. Supprimer ticket.                           | \n";
    cout << "               |                                                 | \n";
    cout << "               |  4. Afficher ticket.                            | \n";
    cout << "               |  5. Modifier ticket.                            | \n";
    cout << "               |  6. Chercher ticket.                            | \n";
    cout << "               |                                                 | \n";
    cout << "               |  7. Back.                                       | \n";
    cout << "               |                                                 | \n";
    cout << "               +-------------------------------------------------+ \n";

    char choix;
    bool k = true;

    do
    {
        if (k == false)
            cout << "Veuillez choisir une action entre 1-3";
        else
            cout << "Veuillez choisir des actions correspondantes des numeros indiques"; cin >> choix;
        k = false;
    } while((choix < '1') || (choix > '7'));

    switch(choix){
        case '1': 
                system("cls");
                bill_input();
                break;
        case '2': 
                system("cls");
                bill_add();
                break;
        case '3':
                system("cls"); 
                bill_del();
                break;
        case '4': 
                system("cls");
                bill_output();
                break;
        case '5': 
                system("cls");
                bill_modifie();
                break;
        case '6':
                cin.ignore();
                cout <<"Entrer un ticket (ID Etudiant) doit etre cherche: "; cin.getline(id_temp, 50);

                i = bill_search(id_temp);

                if(i == 0)
                    cout << "- Ne pouvoir pas trouver avec le ID ci-dessur";
                else{
                    cout << "\n Deja trouve: \n";
                    cout << setw(13) << ". ID Ticket/ ID Etudiant" << setw(13) << "Nom Etudiant" << endl << endl;
                    cout << setw(13) << lst_bill[i].bill_idEtu << setw(13) << lst_bill[i].bill_nomEtu;
                    cout << endl;
                }
                break;
        case '7':
            goto end;
            break;    
    }
    goto begin;
end:;
}

void interface_bill_detail_manager() {
    begin:
    //system("cls");
    cout << endl << endl;
    cout << "               +-------------------------------------------------+ \n";
    cout << "               |     INTERFACE DE GESTION DETAILLE DU TICKET     | \n";
    cout << "               |-------------------------------------------------| \n";
    cout << "               |                                                 | \n";
    cout << "               |  1. Importer ticket detaille.                   | \n";
    cout << "               |                                                 | \n";
    cout << "               |  2. Afficher ticket detaille.                   | \n";   
    cout << "               |                                                 | \n";
    cout << "               |  3. Back.                                       | \n";
    cout << "               |                                                 | \n";
    cout << "               +-------------------------------------------------+ \n";
 
    char choix;
    bool k = true;
   
    do
    {
        if (k == false)
            cout << "Veuillez choisir une action entre 1-3";
        else
            cout << "Veuillez choisir des actions correspondantes des numeros indiques"; cin >> choix;
        k = false;
    } while((choix < '1') || (choix > '7'));
 
 
    switch (choix) {
        case '1':   system("cls");
                    ctbill_input();
                    break;
        case '2':
                    system("cls");
                    ctbill_output();
                    break;
        case '3':
                    goto end;
                    break;
    }
    goto begin;
end:;
}

void interface_main() {
begin:
    system("cls");
    cout << endl << endl;
    cout << "               +=================================================+ \n";
    cout << "               |         APPLICATION DE GESTION DE LA BIB        | \n";
    cout << "               |-------------------------------------------------| \n";
    cout << "               |                                                 | \n";
    cout << "               |  1. Gestion des livres dans la bib.             | \n";
    cout << "               |  2. Gestion des tickets  .                      | \n";
    cout << "               |  3. Gestion des tickets detailles.              | \n";
    cout << "               |                                                 | \n";
    cout << "               |  4. Comptabilite des livres par categorie.      | \n";
    cout << "               |  5. Comptabilite des etudiants n'a pas rendu    | \n";
    cout << "               |  des livres.                                    | \n";
    cout << "               |  6. Exit.                                       | \n";
    cout << "               |                                                 | \n";
    cout << "               +-------------------------------------------------+ \n";
 
    char choix;
    bool k = true;
 
    do
    {
        if (k == false)
            cout << "Veuillez choisir une action entre 1-3";
        else
            cout << "Veuillez choisir des actions correspondantes des numeros indiques"; cin >> choix;
        k = false;
    } while((choix < '1') || (choix > '7'));
 
 
    switch (choix) {
        case '1':
                    system("cls");
                    interface_book_manager();
                    break;
        case '2':
                    system("cls");
                    interface_bill_manager();
                    break;
        case '3':
                    system("cls");
                    interface_bill_detail_manager();
                    break;
        case '4':
                    system("cls");
                    compte_categorie();
                    break;
        case '5':
                    system("cls");
                    compte_etu_outdate();
                    break;
        case '6':
                    goto end;
                    break;
    }
    goto begin;
end:;
 
}

////===============================================================================================
//
//  DEFINITION DEs METHODES
//
////===============================================================================================

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DEFINITION DES METHODES BOOKS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void file_info(){
    FILE * f_b;
    info[0] = total_book;
    info[1] = total_bill;
    info[2] = total;
    f_b = fopen("file_info", "wb");
    fwrite(info, sizeof(info), 1, f_b);
    fclose(f_b);
}

void book_load_file(){
    FILE *f_b;
    f_b = fopen("book_file", "rb");
    fread(lst_book, sizeof(lst_book), 1, f_b);
    fclose(f_b);
}

void book_save_file(){
    FILE * f_b;
    f_b = fopen("book_file", "wb");
    fwrite(lst_book, sizeof(lst_book), 1, f_b);
    fclose(f_b);
}

int book_search(char id_temp[]){
    int jump = 1;
    while((jump <= total_book) && (strcmp(lst_book[jump].b_id, id_temp) != 0))
        jump++;
    if(jump > total_book){
        return 0;
    }else{
        return jump;
    }
}

void book_input(){
    char id_temp[50];
    cout << endl;
    cout << "ENTRER LIVRE. \n";
    cout << "Veuillez entrer le totale de livres: "; cin >> total_book;
    cout << endl;

    for(int i = 1; i <= total_book; i++){
        input_id:;
            cin.ignore(1);
            cout << ". ID Book: "; cin.getline(id_temp, 50);

            if(book_search(id_temp) != 0){
                cout <<" ID Book existe!.";
                cout <<" Taper ENTER pour reessayer !";
                goto input_id;
            }

            strcpy(lst_book[i].b_id, id_temp);
            cout << ". Nom du Livre : "; cin.getline(lst_book[i].b_nom, 50);
            cout << ". Auteur : "; cin.getline(lst_book[i].b_autor, 50);
            cout << ". Categorie : "; cin.getline(lst_book[i].b_categorie, 50);
            cout << ". Distributeur : "; cin.getline(lst_book[i].b_distributeur, 50);
            cout << ". Quantite : "; cin >> lst_book[i].b_quantite;
            cin.ignore();
            cout << endl;
    }
    book_save_file();
    file_info();
}

void book_del(){
    char id_temp[50];
    cin.ignore();
    cout << "Entrer ID du Livre doit etre supprime : "; cin.getline(id_temp, 50);

    i = book_search(id_temp);

    if(i == 0){
        cout << "- Ne trouve aucun livre. ";
    } else {
        for(int j = i; j <= total_book; j++)
            lst_book[j] = lst_book[j + 1];
        total_book = total_book - 1;
        cout << "- Supprimé";
    }
    book_save_file();
    file_info();
}

void book_output(){
    book_load_file();

    cout << "\n                       LISTE DES LIVRES DANS LA BIBLIOTHEQUE             \n \n";
    cout << setw(13) << ". ID Livre" << setw(13) << "Nom du livre" << setw(13) << "Categorie" << setw(13) << "Quantite" << endl << endl;
    for(int i = 1; i <= total_book; i++){
        cout << setw(13) << lst_book[i].b_id << setw(13) << lst_book[i].b_nom << setw(13) << lst_book[i].b_categorie << setw(13) << lst_book[i].b_quantite;
        cout << endl;
    }
}

void book_add(){
    char id_temp[50];

    total_book = total_book + 1;
    cout << "AJOUTER UN LIVRE. \n";
    input_id:;
        cin.ignore(1);
        cout << ". ID Livre: "; cin.getline(id_temp, 50);

        if(book_search(id_temp) != 0){
            cout <<" ID Livre deja existe. Reessayer!";
            goto input_id;
        }

        cout <<". Nom du Livre : "; cin.getline(lst_book[i].b_nom, 50);
        cout <<". Auteur : "; cin.getline(lst_book[i].b_autor, 50);
        cout <<". Categorie : "; cin.getline(lst_book[i].b_categorie, 50);
        cout <<". Distributeur : "; cin.getline(lst_book[i].b_distributeur, 50);
        cout <<". Quantite : "; cin >> lst_book[i].b_quantite;
    book_save_file();
    file_info();
}

void book_modifie(){
    char id_temp[50];

    cin.ignore();
    cout << "Entrer ID Livre doit etre modifie : "; cin.getline(id_temp, 50);

    i = book_search(id_temp);

    if(i == 0)
        cout << "- Ne pouvoir pas trouver le livre qui doit etre modifie.";
    else{
        cout << ". ID Livre : "; cin.getline(lst_book[i].b_id, 50);
        cout << ". Nom du livre : "; cin.getline(lst_book[i].b_nom, 50);
        cout << ". Auteur : "; cin.getline(lst_book[i].b_autor, 50);
        cout << ". Categorie : "; cin.getline(lst_book[i].b_categorie,50);
        cout << ". Distributeur : "; cin.getline(lst_book[i].b_distributeur, 50);
        cout << ". Quantite : "; cin >> lst_book[i].b_quantite;
    }
    book_save_file();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DEFINITION DES METHODES TICKETS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void bill_load_file() {
    FILE *f_b;
    f_b = fopen("bill_file","rb");
    fread(lst_bill, sizeof(lst_bill), 1, f_b);
    fclose(f_b);
}
 
void bill_save_file() {
    FILE * f_b;
    f_b = fopen("bill_file", "wb");
    fwrite(lst_bill, sizeof(lst_bill), 1, f_b);
    fclose(f_b);
}
 
int bill_search(char id_temp[]) {
    int jump = 1;
 
    while ((jump <= total_bill) && (strcmp(lst_bill[jump].bill_idEtu, id_temp) != 0))
        jump++;
   
    if (jump > total_bill)
        return 0;
    else
        return jump;
 
}
 
void bill_input() {
    char id_temp[50];
 
    cout << "La premiere fois faire l'inscription \n";
    cout << "Combien de tickets vont etre inscrits  : "; cin >> total_bill;
    cout << endl;
 
    for (int i = 1; i <= total_bill; i++) {
    id_input:;
        cin.ignore();
        cout << ". ID Ticket: "; cin.getline(id_temp, 50);
 
        if (bill_search(id_temp) != 0) {
            cout << "   Deje existe. Reessayer!";
            goto id_input;
        }
 
        strcpy(lst_bill[i].bill_idEtu, id_temp);
        cout << ". Nom du Etudiant : "; cin.getline(lst_bill[i].bill_nomEtu, 50);
 
        cout << ". Date d'emprunt     : \n";
        cout << " \tJour "; cin >> lst_bill[i].bill_dateEmprunt.n_day;
        cout << " \tMois: "; cin >> lst_bill[i].bill_dateEmprunt.n_month;
        cout << " \tAnnee: "; cin >> lst_bill[i].bill_dateEmprunt.n_year;
        cout << endl;
    }
    bill_save_file();
    file_info();
}
 
void bill_add() {
    char id_temp[50];
 
    total_bill = total_bill + 1;
 
    id_input:;
        cin.ignore();
        cout << ". ID Ticket: "; cin.getline(id_temp, 50);
 
        if (bill_search(id_temp) != 0) {
            cout << "   ID livre deja existe. Reessayer!";
            goto id_input;
        }
 
        strcpy(lst_bill[i].bill_idEtu, id_temp);
        cout << ". Nom du Etudiant : "; cin.getline(lst_bill[i].bill_nomEtu, 50);
 
        cout << ". Date d'emprunt     : \n";
        cout << " Jour: "; cin >> lst_bill[i].bill_dateEmprunt.n_day;
        cout << " Mois: "; cin >> lst_bill[i].bill_dateEmprunt.n_month;
        cout << " Annee: "; cin >> lst_bill[i].bill_dateEmprunt.n_year;
        cout << endl;
 
    bill_save_file();
    file_info();
}
 
void bill_del() {
    char id_temp[50];
 
    cin.ignore();
    cout << "ID Ticket va etre supprime : "; cin.getline(id_temp, 50);
   
    i = bill_search(id_temp);
 
    if (i == 0)
        cout << "- Ne pouvoir pas trouver!. ";
    else {
        for (int j = i; j <= total_bill; j++)
            lst_bill[j] = lst_bill[j+1];
 
        total_bill = total_bill - 1;
        cout << "- Deja Supprime.";
    }
    bill_save_file();
    file_info();
}
 
void bill_output() {
    bill_load_file();
 
    cout << "\n                      LISTE DES TICKETS D'EMPRUNT          \n \n";
    cout << setw(15) << ".ID Ticket/ ID Etudiant" << setw(15) << "Nom du Etudiant" << endl << endl;
    for(int i = 1; i <= total_bill; i++) {
        cout << setw(15) << lst_bill[i].bill_idEtu << setw(15) << lst_bill[i].bill_nomEtu;
        cout << endl;
    }
}
 
 
 
void bill_modifie() {
    char id_temp[50];
 
    cin.ignore();
    cout << "Entrer ID Ticket va etre modifie: "; cin.getline(id_temp, 50);
       
    i = bill_search(id_temp);
 
    if (i == 0)
        cout << "- Pas trouver!. ";
    else {
        //cin.ignore();
        cout << ". Ma phieu/Ma SV: "; cin.getline(lst_bill[i].bill_idEtu, 50);
        cout << ". Ten Sinh Vien : "; cin.getline(lst_bill[i].bill_nomEtu, 50);
 
        cout << ". Ngay Muon     : \n";
        cout << " Ngay "; cin >> lst_bill[i].bill_dateEmprunt.n_day;
        cout << " thang: "; cin >> lst_bill[i].bill_dateEmprunt.n_month;
        cout << " nam: "; cin >> lst_bill[i].bill_dateEmprunt.n_year;
        cout << endl;
    }
    bill_save_file();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DEFINITION METHODES POUR TICKET DETAILLE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ctbill_load_file() {
    FILE *f_b;
    f_b = fopen("bill_detail_file","rb");
    fread(lst_detail, sizeof(lst_detail), 1, f_b);
    fclose(f_b);
}
void ctbill_save_file() {
    FILE * f_b;
    f_b = fopen("bill_detail_file", "wb");
    fwrite(lst_detail, sizeof(lst_detail), 1, f_b);
    fclose(f_b);
}
 
void ctbill_input() {
    char book_temp[50];
    char bill_temp[50];
    char t;
    int total_temp;                  
 
    emprunt:;
    cin.ignore(1);
    cout << ". Nombre de livre doit etre emprunte : "; cin >> total_temp;
   
    if (total + total_temp > 5) {
        cout << "- Maximum 5 livres. \n";
        cout << "  Vous pourriez emprunter encore  " << 5 - total << "  livres.";
        goto emprunt;
    }
 
    for (int i = 1; i <= total_temp; i++) {
        cin.ignore(1);
        cout << endl;
        cout << ". Entrez ID Ticket : "; cin.getline(bill_temp, 50);
 
        if (bill_search(bill_temp) == 0) {
            cout << "- Trouver pas votre ticket.";
            break;
        }
       
        idBook_input:;
        cin.ignore(1);
        cout << ". Entrer ID Livre : "; cin.getline(book_temp, 50);
 
        t = book_search(book_temp);
 
        if (t == 0) {
            cout << ". Trouver pas le livre que vous voulez.";
            cout << "  Emprunter un autre livre (y/n) : "; cin >> t;
            if (t == 'y' || t == 'Y')
                goto idBook_input;
            else
                break;
        }
 
        strcpy(lst_detail[i].detail_idEtu, bill_temp);   
        strcpy(lst_detail[i].detail_idBook, book_temp);
        strcpy(lst_detail[i].detail_nomBook, lst_book[p].b_nom);
 
        cin.ignore(1);
        cout << ". Statut : "; cin.getline(lst_detail[i].b_new_old, 50);
        cout << ". Rendu / Non : "; cin.getline(lst_detail[i].b_checkReturn, 50);
 
        if (strcmp(lst_detail[i].b_checkReturn, "Non") == 0)
            lst_book[p].b_quantite = lst_book[p].b_quantite - 1;
        else
            lst_book[p].b_quantite = lst_book[p].b_quantite + 1;
    }
    ctbill_save_file();
    file_info();
 
}
 
void ctbill_output() {
    ctbill_load_file();
 
    char bill_temp[50];
    //char t;
    p = 0;
 
    cin.ignore(1);
    cout << ". Entrer ID Ticket : "; cin.getline(bill_temp, 50);
 
    cout << setw(13) << ".ID Livre" << setw(13) << "Nom du livre" << setw(13) << "Old / New" << setw(13) << "Rendu / Non" << endl << endl;
    for(int i = 1; i <= total; i++)
        if (strcmp(lst_detail[i].detail_idEtu, bill_temp) == 0) {
            cout << setw(13) << lst_detail[i].detail_idBook << setw(13) << lst_detail[i].detail_nomBook << setw(13) << lst_detail[i].b_new_old << setw(13) << lst_detail[i].b_checkReturn;
            p = 1;
        }
    if (p == 0) printf("\n- Pas Trouver. ");
}

void compte_categorie() {
    char book_categorie_temp[50];
    p = 0;
 
    cin.ignore(1);
    cout << ". Entrer categorie doit etre comptabilise: "; cin.getline(book_categorie_temp, 50);
    cout << endl;
   
    cout << setw(13) << ".ID Book" << setw(13) << "Nom du livre" << setw(13) << "Categorie" << setw(13) << "Quantite.";
    for (int i = 1; i <= total_book ;i++)
        if (strcmp(lst_book[i].b_categorie, book_categorie_temp) == 0)
        {   cout << setw(13) << lst_book[i].b_id << setw(13) << lst_book[i].b_nom<< setw(13) << lst_book[i].b_categorie << setw(13) << lst_book[i].b_quantite;
            p = p + 1;
        }
    cout << endl << "- Yes " << p << " Livre est dans la categorie : " << book_categorie_temp;
    if( p == 0)
        cout << endl << "- Il n'y a de livre dans cette categorie : " << book_categorie_temp;
}
 
void compte_etu_outdate() {
    SYSTEMTIME d;
    int n_d, n_m, n_y;
    int d_quahan;
 
    n_d = d.wDay;
    n_m = d.wMonth;
    n_y = d.wYear;
   
    cout << endl;
    cout << setw(15) << "Nombre de ticket" << setw(15) << "Nom d'etudiant" << endl << endl;
 
    for (int i = 1; i <= total_bill; i++) {
        if ((lst_bill[i].bill_dateEmprunt.n_year == n_y) && (lst_bill[i].bill_dateEmprunt.n_month == n_m))
            d_quahan = n_d - lst_bill[i].bill_dateEmprunt.n_day;
        if ((lst_bill[i].bill_dateEmprunt.n_year == n_y) && (lst_bill[i].bill_dateEmprunt.n_month != n_m))
            d_quahan = n_d + days_in_month(n_m,n_d);
        if (d_quahan >= 30)
            cout << endl;
            cout << setw(15) << lst_bill[i].bill_idEtu << setw(15) << lst_bill[i].bill_nomEtu << endl;
    }
}


// Calculer jours dans le mois.
int days_in_month(int md, int dd ) {
    switch (md)
    {
    case '1':
                return (31 - dd);
    case '2':
                return (28 - dd);
    case '3':
                return (31 - dd);
    case '4':
                return (30 - dd);
    case '5':
                return (31 - dd);
    case '6':
                return (30 - dd);
    case '7':
                return (31 - dd);
    case '8':
                return (31 - dd);
    case '9':
                return (30 - dd);
    case '10':
                return (31 - dd);
    case '11':
                return (30 - dd);
    case '12':
                return (31 - dd);
    }
}