/*!
    \file main.cpp
    \brief Da qui parte il software
*/

/*!
    \mainpage Gestione Simulata di una Biblioteca

    Questa e' una simulazione per il funzionamento di una Biblioteca.\n
    Tramite il sofware a riga di comando e' possibile accedere al servizio secondo tre modalita':\n
    1) Direttore - ha il controllo totale su Libri, Prestiti, Utenti e Addetti\n
    2) Addetto - rispetto al Direttore, non gestisce gli Addetti e non ha il controllo sull'eliminazione di dati\n
    3) Utente - visualizza e ricerca Libri tramite il Catalogo e controlla i Prestiti da lui effettuati\n
    \author Matteo Pompilio
    \version 1.0
    \date 18/05/2018
 */
#include <iostream>
#include <string.h>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <MMSystem.h>
#include "classi.h"
using namespace std;

void UserMode(){
    int scelta=0;
    bool check=false;
    Login l;
    Utente u;
    Catalogo c;
    do{
        l.NewLogin('u');
        u.SetUserCredenziali(l.GetPin(), l.GetNome(), l.GetCognome(), l.GetUsername());
    } while(!l.GetIsLoggato());
    PlaySound("userTheme.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
    do{
        cout<<"\n1)Richiedi Prestito Libro\n2)Visualizza Prestiti\n3)Ricerca in Catalogo\n4)Esci\n";
        do{
            cout<<".."; cin>>scelta; check=true;
            if (cin.fail()) check=false;
            cin.clear();
            cin.ignore(10, '\n');
        } while(!check || scelta < 1 || scelta > 4);
        switch(scelta){
            case 1:u.RichiestaPrestito(&u); break;
            case 2:u.ViewListaPrestitiInCorso(u.GetUsername()); break;
            case 3:c.RicercaLibro(); break;
            case 4:break;
        }
        if(scelta != 4) system("pause");
        system("CLS");
    } while(scelta!=4);
    PlaySound(NULL, NULL, 0);
}


void AgentMode(){
    int sceltaMenu=0, scelta=0;
    bool check=false;
    Login l;
    Addetto a;
    Catalogo c;
    l.NewLogin('a');
    if(!l.GetIsLoggato()){
        cout<<"\nNessun Addetto Trovato!\n";
        return;
    }
    PlaySound("agentTheme.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
    do{
        cout<<"\n1)Gestione Catalogo\n2)Gestione Prestiti\n3)Gestione Utenti\n4)Esci\n";
        do{
            cout<<".."; cin>>sceltaMenu; check=true;
            if (cin.fail()) check=false;
            cin.clear();
            cin.ignore(10, '\n');
        } while(!check || sceltaMenu < 1 || sceltaMenu > 5);
        switch(sceltaMenu){
            case 1:do{
                       cout<<"  1)Visualizza Catalogo\n  2)Ricerca Libro\n  3)Modifica Libro\n  4)Esci\n";
                       do{
                            cout<<".."; cin>>scelta; check=true;
                            if (cin.fail()) check=false;
                            cin.clear();
                            cin.ignore(10, '\n');
                       } while(!check || scelta < 1 || scelta > 4);
                       switch(scelta){
                           case 1:c.VisualizzaCatalogo(); break;
                           case 2:c.RicercaLibro(); break;
                           case 3:a.ModificaLibro(); break;
                           case 4:break;
                       }
                       if(scelta != 4) system("pause");
                       system("CLS");
                   } while(scelta != 4);
               break;
            case 2:do{
                       cout<<"  1)Vedi Lista Prestiti\n  2)Vedi Lista Prestiti In Corso\n  3)Vedi Lista Resi\n  4)Ricerca Prestito\n  5)Esci\n";
                       do{
                            cout<<".."; cin>>scelta; check=true;
                            if (cin.fail()) check=false;
                            cin.clear();
                            cin.ignore(10, '\n');
                       } while(!check || scelta < 1 || scelta > 5);
                       switch(scelta){
                           case 1:a.ViewListaPrestiti(); break;
                           case 2:a.ViewListaPrestitiInCorso(); break;
                           case 3:a.ViewListaPrestitiScaduti(); break;
                           case 4:a.RicercaPrestito(); break;
                           case 5:break;
                       }
                       if(scelta != 5) system("pause");
                       system("CLS");
                   } while(scelta != 5);
               break;
            case 3:do{
                       cout<<"  1)Vedi Lista Utenti\n  2)Ricerca Utente\n  3)Registra Utente\n  4)Modifica Utente\n  5)Esci\n";
                       do{
                            cout<<".."; cin>>scelta; check=true;
                            if (cin.fail()) check=false;
                            cin.clear();
                            cin.ignore(10, '\n');
                       } while(!check || scelta < 1 || scelta > 5);
                       switch(scelta){
                           case 1:a.ViewListaUtenti(); break;
                           case 2:a.RicercaUtente(); break;
                           case 3:a.RegistrazioneUtente(); break;
                           case 4:a.ModificaUtente(); break;
                           case 5:break;
                       }
                       if(scelta != 5) system("pause");
                       system("CLS");
                   } while(scelta != 5);
               break;
            case 4:break;
        }
        if(sceltaMenu != 4) system("pause");
        system("CLS");
    } while(sceltaMenu != 4);
    PlaySound(NULL, NULL, 0);
}


void DirectorMode(){

    int sceltaMenu=0, scelta=0;
    bool check=false;
    Direttore d;
    Login l;
    Catalogo c;
    l.NewLogin('d');
    if(!l.GetIsLoggato()){
        cout<<"\nDirettore non Trovato!\n";
        return;
    }
    PlaySound("directorTheme.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
    do{
        cout<<"\n1)Gestione Catalogo\n2)Gestione Prestiti\n3)Gestione Utenti\n4)Gestione Addetti\n5)Esci\n";
        do{
            cout<<".."; cin>>sceltaMenu; check=true;
            if (cin.fail()) check=false;
            cin.clear();
            cin.ignore(10, '\n');
        } while(!check || sceltaMenu < 1 || sceltaMenu > 5);
        switch(sceltaMenu){
            case 1:do{
                       cout<<"  1)Visualizza Catalogo\n  2)Ricerca Libro\n  3)Aggiungi Libro\n  4)Modifica Libro\n  5)Elimina Libro\n  6)Esci\n";
                       do{
                            cout<<".."; cin>>scelta; check=true;
                            if (cin.fail()) check=false;
                            cin.clear();
                            cin.ignore(10, '\n');
                       } while(!check || scelta < 1 || scelta > 6);
                       switch(scelta){
                           case 1:c.VisualizzaCatalogo(); break;
                           case 2:c.RicercaLibro(); break;
                           case 3:{
                                  int sceltaDisponibilita=0, nn=0;
                                  char titolo[51], autore[21], anno[5], disponibilita[20];
                                  string ttl, tr;
                                  do{
                                      cout<<"Titolo: "; getline(cin,ttl);
                                      check=true;
                                      for(int i=0; i<50 && ttl[i] != 0; i++)
                                          if( (ttl[i] != 32 && ttl[i] < 48) ||
                                              (ttl[i] > 57 && ttl[i] < 65) ||
                                              (ttl[i] > 90 && ttl[i] < 97) ||
                                               ttl[i] > 122 ) check=false;
                                      cin.clear();
                                  } while( ttl.length() > 50 || !check);
                                  do{
                                      cout<<"Autore: "; getline(cin,tr);
                                      check=true;
                                      for(int i=0; i<20 && tr[i] != 0; i++)
                                          if( (tr[i] != 32 && tr[i] < 65) ||
                                              (tr[i] > 90 && tr[i] < 97) ||
                                               tr[i] > 122 ) check=false;
                                      cin.clear();
                                  } while( tr.length() > 20 || !check);
                                  do{
                                      cout<<"Anno: "; cin>>nn; check=true;
                                      if (cin.fail()) check=false;
                                      cin.clear();
                                      cin.ignore(10, '\n');
                                  } while(!check || nn < -10000 || nn > 2018);
                                  cout<<"1)Disponibile\n2)Non Disponibile\n3)In Prestito\n4)In Reso\n5)Prenotato\n";
                                  do{
                                      cout<<".."; cin>>sceltaDisponibilita; check=true;
                                      if (cin.fail()) check=false;
                                      cin.clear();
                                      cin.ignore(10, '\n');
                                  } while(!check || sceltaDisponibilita < 1 || sceltaDisponibilita > 5);
                                  switch(sceltaDisponibilita){
                                      case 1: strcpy(disponibilita,"Disponibile"); break;
                                      case 2: strcpy(disponibilita,"Non Disponibile"); break;
                                      case 3: strcpy(disponibilita,"In Prestito"); break;
                                      case 4: strcpy(disponibilita,"In Reso"); break;
                                      case 5: strcpy(disponibilita,"Prenotato"); break;
                                  }
                                  strcpy(titolo, ttl.c_str());
                                  strcpy(autore, tr.c_str());
                                  itoa(nn, anno, 10);
                                  Libro l(titolo, autore, anno, disponibilita, false); l.Write(&l);
                             }break;
                           case 4:d.ModificaLibro(); break;
                           case 5:d.EliminazioneLibro(); break;
                           case 6:break;
                       }
                       if(scelta != 6) system("pause");
                       system("CLS");
                   } while(scelta != 6);
               break;
            case 2:do{
                       cout<<"  1)Vedi Lista Prestiti\n  2)Vedi Lista Prestiti In Corso\n  3)Vedi Lista Resi\n  4)Ricerca Prestito\n  5)Modifica Prestito\n  6)Elimina Prestito\n  7)Esci\n";
                       do{
                            cout<<".."; cin>>scelta; check=true;
                            if (cin.fail()) check=false;
                            cin.clear();
                            cin.ignore(10, '\n');
                       } while(!check || scelta < 1 || scelta >7);
                       switch(scelta){
                           case 1:d.ViewListaPrestiti(); break;
                           case 2:d.ViewListaPrestitiInCorso(); break;
                           case 3:d.ViewListaPrestitiScaduti(); break;
                           case 4:d.RicercaPrestito(); break;
                           case 5:d.ModificaPrestito(); break;
                           case 6:d.EliminazionePrestito(); break;
                           case 7:break;
                       }
                       if(scelta != 7) system("pause");
                       system("CLS");
                   } while(scelta != 7);
               break;
            case 3:do{
                       cout<<"  1)Vedi Lista Utenti\n  2)Ricerca Utente\n  3)Registra Utente\n  4)Modifica Utente\n  5)Elimina Utente\n  6)Esci\n";
                       do{
                            cout<<".."; cin>>scelta; check=true;
                            if (cin.fail()) check=false;
                            cin.clear();
                            cin.ignore(10, '\n');
                       } while(!check || scelta < 1 || scelta >6);
                       switch(scelta){
                           case 1:d.ViewListaUtenti(); break;
                           case 2:d.RicercaUtente(); break;
                           case 3:d.RegistrazioneUtente(); break;
                           case 4:d.ModificaUtente(); break;
                           case 5:d.EliminazioneUtente(); break;
                           case 6:break;
                       }
                       if(scelta != 6) system("pause");
                       system("CLS");
                   } while(scelta != 6);
               break;
            case 4:do{
                       cout<<"  1)Vedi Lista Addetti\n  2)Ricerca Addetto\n  3)Registra Addetto\n  4)Modifica Addetto\n  5)Licenzia Addetto\n  6)Esci\n";
                       do{
                            cout<<".."; cin>>scelta; check=true;
                            if (cin.fail()) check=false;
                            cin.clear();
                            cin.ignore(10, '\n');
                       } while(!check || scelta < 1 || scelta >6);
                       switch(scelta){
                           case 1:d.ViewListaAddetti(); break;
                           case 2:d.RicercaAddetto(); break;
                           case 3:d.RegistrazioneAddetto(); break;
                           case 4:d.ModificaAddetto(); break;
                           case 5:d.EliminazioneAddetto(); break;
                           case 6:break;
                       }
                       if(scelta != 6) system("pause");
                       system("CLS");
                   } while(scelta != 6);
               break;
            case 5:break;
        }
        if(sceltaMenu != 5) system("pause");
        system("CLS");
    } while(sceltaMenu != 5);
    PlaySound(NULL, NULL, 0);
}


////////////MAIN//////////
int main(){
    fstream f("CredenzialiDirettore.dat",ios::binary | ios::in | ios::app);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        cout<<"Credenziali direttore non ancora settate\n";
        Registrazione r;
        r.NewRegistrazione('d');
        system("CLS");
    }
    f.close();

    cout<<"   ___  _______  __   ________  __________________  \n";
    cout<<"  / _ )/  _/ _ )/ /  /  _/ __ \\/_  __/ __/ ___/ _ | \n";
    cout<<" / _  |/ // _  / /___/ // /_/ / / / / _// /__/ __ | \n";
    cout<<"/____/___/____/____/___/\\____/ /_/ /___/\\___/_/ |_| \n";
    char accessMode;
    Catalogo c;
    do{
        cout<<"\nScegli come accedere..\na)Addetto\nb)Utente\nd)Direttore\ne)Esci\n";
        cout<<"Oppure\nc)Visualizza Catalogo\n";
        do{
            cout<<".."; cin>>accessMode;
        } while(accessMode < 'a' || accessMode > 'e');
        switch(accessMode){
            case 'a':AgentMode(); break;
            case 'b':UserMode(); break;
            case 'd':DirectorMode(); break;
            case 'c':c.VisualizzaCatalogo(); system("pause"); system("CLS"); break;
            case 'e':break;
        }
    } while(accessMode != 'e');
    cout<<"\nA PRESTO!\n";
    return 0;
}
