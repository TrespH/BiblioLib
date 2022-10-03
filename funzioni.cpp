/*!
    \file funzioni.cpp
    \brief Qua sono implementate tutte le funzioni.
*/
#include <iostream>
#include <string.h>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include "classi.h"
using namespace std;


///////////////////PERSONA

Persona::Persona(char* pin, char* nome, char* cognome){
    strcpy(this->pin, pin);
    strcpy(this->nome, nome);
    strcpy(this->cognome, cognome);
}

void Persona::SetCredenziali(char* pin, char* nome, char* cognome){
    strcpy(this->pin, pin);
    strcpy(this->nome, nome);
    strcpy(this->cognome, cognome);
}

void Persona::ViewListaPrestiti(){
    ifstream f("ListaPrestiti.dat", ios::binary | ios::in);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        cout<<"\nNessun Prestito in Lista\n";
        f.close();
        return;
    }
    f.seekg(0,ios::beg);

    char scelta;
    Libro l;
    Utente u;
    Prestito p;
    Catalogo c;
    ofstream f1("ListaPrestitiTemp.dat", ios::binary | ios::out);
    ofstream f2("ListaPrestitiInCorso.dat", ios::binary | ios::out);
    f.read((char*)&l,sizeof(Libro));
    f.read((char*)&u,sizeof(Utente));
    f.read((char*)&p,sizeof(Prestito));
    while(!f.eof()){
        time_t data1=p.GetDataAccettazione();
        time_t data2=p.GetDataScadenza();
        string dataAccettazione(ctime(&data1));
        string dataScadenza(ctime(&data2));
        cout<<"\nAccetti il prestito del Libro '"<<l.GetTitolo()<<"'";
        cout<<"\nRichiesto dall'utente '"<<u.GetNome()<<" "<<u.GetCognome()<<"'";
        cout<<"\nIn Data "<<dataAccettazione.substr( 0, dataAccettazione.length() -1  );
        cout<<"\nCon Scadenza prevista per Data "<<dataScadenza.substr( 0, dataScadenza.length() -1  )<<"\n";
        do{
            cout<<"(s/n)? ";
            cin>>scelta;
        } while(scelta != 's' && scelta != 'n' && scelta != 'S' && scelta != 'N');
        if(scelta == 'n'){
            f1.write((char*)&l,sizeof(Libro));
            f1.write((char*)&u,sizeof(Utente));
            f1.write((char*)&p,sizeof(Prestito));
        }
        else{
            f2.write((char*)&l,sizeof(Libro));
            f2.write((char*)&u,sizeof(Utente));
            f2.write((char*)&p,sizeof(Prestito));
            l.SetDisponibilita("In Prestito");
            l.SetCodice(p.GetCodice());
            c.UpdateCatalogo(&l);
        }
        f.read((char*)&l,sizeof(Libro));
        f.read((char*)&u,sizeof(Utente));
        f.read((char*)&p,sizeof(Prestito));
    }
    f2.close();
    f1.close();
    f.close();
    remove( "ListaPrestiti.dat" );
    rename( "ListaPrestitiTemp.dat" , "ListaPrestiti.dat" );
}

void Persona::ViewListaPrestitiInCorso(char* username){
    ifstream f("ListaPrestitiInCorso.dat", ios::binary | ios::in);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        cout<<"\nNessun Prestito in Corso in Lista\n";
        f.close();
        return;
    }
    f.seekg(0,ios::beg);

    int i=1;
    Libro l;
    Utente u;
    Prestito p;
    cout<<"\n-------------------------- LISTA PRESTITI --------------------------\n";
    cout<<"     TITOLO     // NOME // COGNOME // DATA RICHIESTA // DATA SCADENZA // GIORNI RIMANENTI\n";
    f.read((char*)&l,sizeof(Libro));
    f.read((char*)&u,sizeof(Utente));
    f.read((char*)&p,sizeof(Prestito));
    while(!f.eof()){
        time_t data1=p.GetDataAccettazione();
        time_t data2=p.GetDataScadenza();
        string dataAccettazione(ctime(&data1));
        string dataScadenza(ctime(&data2));
        if( !strcmp(username,"none") ){
            cout<<"\n"<<i<<") "<<l.GetTitolo()<<"  "<<u.GetNome()<<" "<<u.GetCognome()<<" ("<<u.GetUsername()<<")  ";
            cout<<dataAccettazione.substr( 0, dataAccettazione.length() -1  )<<"  "<<dataScadenza.substr( 0, dataScadenza.length() -1  );
            cout<<"  "<<p.GetDifferenza();
        }
        else if( !strcmp(u.GetUsername(),username) ){
            cout<<"\n"<<i<<") "<<l.GetTitolo()<<"  ";
            cout<<dataAccettazione.substr( 0, dataAccettazione.length() -1  )<<"  "<<dataScadenza.substr( 0, dataScadenza.length() -1  );
            cout<<"  "<<p.GetDifferenza();
        }
        f.read((char*)&l,sizeof(Libro));
        f.read((char*)&u,sizeof(Utente));
        f.read((char*)&p,sizeof(Prestito));
        i++;
    }
    cout<<"\n--------------------------------------------------------------------\n";
    f.close();
}

void Persona::ViewListaPrestitiScaduti(){
    ifstream f("ListaPrestitiScaduti.dat", ios::binary | ios::in);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        cout<<"\nNessun Prestito Scaduto in Lista\n";
        f.close();
        return;
    }
    f.seekg(0,ios::beg);

    char scelta;
    Libro l;
    Utente u;
    Prestito p;
    Catalogo c;
    ofstream f1("ListaPrestitiScadutiTemp.dat", ios::binary | ios::out);
    f.read((char*)&l,sizeof(Libro));
    f.read((char*)&u,sizeof(Utente));
    f.read((char*)&p,sizeof(Prestito));
    while(!f.eof()){
        time_t data1=p.GetDataAccettazione();
        time_t data2=p.GetDataScadenza();
        string dataAccettazione(ctime(&data1));
        string dataScadenza(ctime(&data2));
        cout<<"\nAccetti il Reso del Libro '"<<l.GetTitolo()<<"'";
        cout<<"\nRichiesto dall'utente '"<<u.GetNome()<<" "<<u.GetCognome()<<"'";
        cout<<"\nIn Data "<<dataAccettazione.substr( 0, dataAccettazione.length() -1  );
        cout<<"\nCon Scadenza prevista per Data "<<dataScadenza.substr( 0, dataScadenza.length() -1  )<<"\n";
        do{
            cout<<"(s/n)? ";
            cin>>scelta;
        } while(scelta != 's' && scelta != 'n' && scelta != 'S' && scelta != 'N');
        if(scelta == 'n'){
            f1.write((char*)&l,sizeof(Libro));
            f1.write((char*)&u,sizeof(Utente));
            f1.write((char*)&p,sizeof(Prestito));
        }
        else{
            l.SetDisponibilita("Disponibile");
            l.SetCodice(p.GetCodice());
            c.UpdateCatalogo(&l);
        }
        f.read((char*)&l,sizeof(Libro));
        f.read((char*)&u,sizeof(Utente));
        f.read((char*)&p,sizeof(Prestito));
    }
    f1.close();
    f.close();
    remove( "ListaPrestitiScaduti.dat" );
    rename( "ListaPrestitiScadutiTemp.dat" , "ListaPrestitiScaduti.dat" );
}

void Persona::ViewListaUtenti(){
    ifstream f("CredenzialiUtenti.dat", ios::binary | ios::in);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        cout<<"\nNessun Utente Registrato\n";
        f.close();
        return;
    }
    f.seekg(0,ios::beg);

    int i=1;
    time_t data;
    Utente u;
    cout<<"\n-------------------------- LISTA UTENTI --------------------------\n";
    cout<<"  NOME // COGNOME //  USERNAME  // PIN // DATA REGISTRAZIONE\n";
    f.read((char*)&u,sizeof(Utente));
    while(!f.eof()){
        data=u.GetDataRegistrazione();
        cout<<i<<") "<<u.GetNome()<<"  "<<u.GetCognome()<<" ("<<u.GetUsername()<<") "<<u.GetPin()<<"  "<<ctime(&data);
        f.read((char*)&u,sizeof(Utente));
        i++;
    }
    cout<<"\n------------------------------------------------------------------\n";
    f.close();
}

bool Persona::RicercaPrestito(int* vett){
    ifstream f("ListaPrestitiInCorso.dat", ios::binary | ios::in);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        cout<<"\nNessun Prestito in Corso Presente\n";
        f.close();
        return false;
    }
    f.seekg(0,ios::beg);

    unsigned int length=0, i=0, c=0, m=0, trovati=0, scorsi=1;
    char elementoRicerca[51];
    string elmntRcrc;
    bool check=true;
    Libro l;
    Utente u;
    Prestito p;;
    do{
        cout<<"Inserire (Nome, Cognome) Utente, (Titolo, Autore, Anno, Codice) Libro.. "; cin.ignore(); getline(cin,elmntRcrc);
        check=true;
        for(int i=0; i<50 && elmntRcrc[i] != 0; i++)
            if( (elmntRcrc[i] != 32 && elmntRcrc[i] < 48) ||
                (elmntRcrc[i] > 57 && elmntRcrc[i] < 65) ||
                (elmntRcrc[i] > 90 && elmntRcrc[i] < 97) ||
                 elmntRcrc[i] > 122 ) check=false;
    } while( elmntRcrc.length() >= 50 || !check);
    strcpy(elementoRicerca, elmntRcrc.c_str());
    length=strlen(elementoRicerca);
    f.read((char*)&l,sizeof(Libro));
    f.read((char*)&u,sizeof(Utente));
    f.read((char*)&p,sizeof(Prestito));
    while(!f.eof()){
        //cout<<"Entrata, "<<i<<"\n";
        ////RICERA IN NOME UTENTE
        for(c=0; i<length && c<strlen(u.GetNome()); c++)
            for(i=0,m=c; i<length && u.GetNome()[m] == elementoRicerca[i]; i++,m++);
        //cout<<"Nome, "<<i<<"\n";
        ////RICERA IN COGNOME UTENTE
        for(c=0; i<length && c<strlen(u.GetCognome()); c++)
            for(i=0,m=c; i<length && u.GetCognome()[m] == elementoRicerca[i]; i++,m++);
        //cout<<"Cognome, "<<i<<"\n";
        ////RICERA IN TITOLO
        for(c=0; i<length && c<strlen(l.GetTitolo()); c++)
            for(i=0,m=c; i<length && l.GetTitolo()[m] == elementoRicerca[i]; i++,m++);
        //cout<<"Titolo, "<<i<<"\n";
        ////RICERCA IN AUTORE
        if(i<length)
            for(c=0; i<length && c<strlen(l.GetAutore()); c++)
                for(i=0,m=c; i<length && l.GetAutore()[m] == elementoRicerca[i]; i++,m++);
        //cout<<"Autore, "<<i<<"\n";
        ////RICERA IN ANNO
        if(i<length)
            for(c=0; i<length && c<strlen(l.GetAnno()); c++)
                for(i=0,m=c; i<length && l.GetAnno()[m] == elementoRicerca[i]; i++,m++);
        //cout<<"Anno, "<<i<<"\n";
        ////RICERA IN CODICE
        if(i<length)
            for(c=0; i<length && c<strlen(l.GetCodice()); c++)
                for(i=0,m=c; i<length && l.GetCodice()[m] == elementoRicerca[i]; i++,m++);
        //cout<<"Codice, "<<i<<"\n";
        if(i == length){
            vett[trovati]=scorsi;
            time_t data1=p.GetDataAccettazione();
            time_t data2=p.GetDataScadenza();
            string dataAccettazione(ctime(&data1));
            string dataScadenza(ctime(&data2));
            cout<<scorsi<<") ";
            cout<<u.GetNome()<<"\t";
            cout<<u.GetCognome()<<"\t";
            cout<<l.GetTitolo()<<"\t";
            cout<<dataAccettazione.substr( 0, dataAccettazione.length() -1  )<<"\t";
            cout<<dataScadenza.substr( 0, dataScadenza.length() -1  )<<"\t";
            cout<<p.GetDifferenza()<<endl;
            trovati++;
        }
        scorsi++;
        i=0;
        f.read((char*)&l,sizeof(Libro));
        f.read((char*)&u,sizeof(Utente));
        f.read((char*)&p,sizeof(Prestito));
    }
    f.close();
    if(trovati == 0){
        cout<<"Nessun Prestito Trovato..\n";
        return false;
    }
    else {
        cout<<"Prestiti Trovati: "<<trovati<<endl;
        return true;
    }
}

bool Persona::RicercaUtente(int* vett){
    ifstream f("CredenzialiUtenti.dat", ios::binary | ios::in);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        cout<<"\nNessun Utente Registrato\n";
        f.close();
        return false;
    }
    f.seekg(0,ios::beg);

    unsigned int length=0, i=0, c=0, m=0, trovati=0, scorsi=1;
    char elementoRicerca[51];
    string elmntRcrc;
    bool check=true;
    Utente u;
    do{
        cout<<"Inserire Nome, Cognome, Pin.. "; cin.ignore(); getline(cin,elmntRcrc);
        check=true;
        for(int i=0; i<50 && elmntRcrc[i] != 0; i++)
            if( (elmntRcrc[i] != 32 && elmntRcrc[i] < 48) ||
                (elmntRcrc[i] > 57 && elmntRcrc[i] < 65) ||
                (elmntRcrc[i] > 90 && elmntRcrc[i] < 97) ||
                 elmntRcrc[i] > 122 ) check=false;
    } while( elmntRcrc.length() >= 50 || !check);
    strcpy(elementoRicerca, elmntRcrc.c_str());
    length=strlen(elementoRicerca);
    f.read((char*)&u,sizeof(Utente));
    while(!f.eof()){
        ////RICERA IN NOME
        for(c=0; i<length && c<strlen(u.GetNome()); c++)
            for(i=0,m=c; i<length && u.GetNome()[m] == elementoRicerca[i]; i++,m++);
        ////RICERCA IN COGNOME
        if(i<length)
            for(c=0; i<length && c<strlen(u.GetCognome()); c++)
                for(i=0,m=c; i<length && u.GetCognome()[m] == elementoRicerca[i]; i++,m++);
        ////RICERA IN PIN
        if(i<length)
            for(c=0; i<length && c<strlen(u.GetPin()); c++)
                for(i=0,m=c; i<length && u.GetPin()[m] == elementoRicerca[i]; i++,m++);
        if(i == length){
            vett[trovati]=scorsi;
            cout<<scorsi<<") ";
            cout<<u.GetNome()<<"\t";
            cout<<u.GetCognome()<<"\t";
            cout<<u.GetPin()<<endl;
            trovati++;
        }
        scorsi++;
        i=0;
        f.read((char*)&u,sizeof(Utente));
    }
    f.close();
    if(trovati == 0){
        cout<<"Nessun Utente Trovato..\n";
        return false;
    }
    else {
        cout<<"Utenti Trovati: "<<trovati<<endl;
        return true;
    }
}

void Persona::RegistrazioneUtente(){
    Registrazione r;
    r.NewRegistrazione('u');
}

void Persona::ModificaLibro(){
    int sceltaModifica=0, libroNumber=0, libroPosition=0, sceltaDisponibilita=0, nwnn=0;
    int* vett=new int[1000];
    char newTitolo[51], newAutore[21], newAnno[5], newCodice[4], newDisponibilita[20];
    string nwTtl, nwtr, nwCdc;
    bool check=false;
    Libro l;
    Catalogo c;
    if( !c.RicercaLibro(vett) ) return;
    do{
        cout<<"Numero Libro da Modificare: "; cin>>libroNumber;
        cin.clear();
        cin.ignore(10, '\n');
        check=false;
        for(unsigned int i=0; i<sizeof(vett)/4; i++) check=libroNumber == vett[i];
    } while(cin.fail() || !check);
    libroPosition=(libroNumber-1)*sizeof(Libro);
    fstream f("Catalogo.dat", ios::binary | ios::in | ios::out);
    f.seekp(libroPosition, ios::beg);
    f.read((char*)&l,sizeof(Libro));
    strcpy(newTitolo, l.GetTitolo());
    strcpy(newAutore, l.GetAutore());
    strcpy(newAnno, l.GetAnno());
    strcpy(newCodice, l.GetCodice());
    strcpy(newDisponibilita, l.GetDisponibilita());
    do{
        cout<<"  1)Modifica Titolo\n  2)Modifica Autore\n  3)Modifica Anno\n  4)Modifica Disponibilita'\n  5)Esci\n";
        do{
            cout<<".."; cin>>sceltaModifica;
            cin.clear();
            cin.ignore(10, '\n');
        } while(cin.fail() || sceltaModifica < 1 || sceltaModifica > 5);
        switch(sceltaModifica){
            case 1:do{
                       cout<<"Nuovo Titolo: "; cin.ignore(); getline(cin,nwTtl);
                       check=true;
                       for(int i=0; i<50 && nwTtl[i] != 0; i++)
                         if( (nwTtl[i] != 32 && nwTtl[i] < 48) ||
                             (nwTtl[i] > 57 && nwTtl[i] < 65) ||
                             (nwTtl[i] > 90 && nwTtl[i] < 97) ||
                              nwTtl[i] > 122 ) check=false;
                   } while( nwTtl.length() >= 50 || !check);
                   strcpy(newTitolo, nwTtl.c_str());
                   break;
            case 2:do{
                       cout<<"Nuovo Autore: "; cin.ignore(); getline(cin,nwtr);
                       check=true;
                       for(int i=0; i<20 && nwtr[i] != 0; i++)
                         if( (nwtr[i] != 32 && nwtr[i] < 65) ||
                             (nwtr[i] > 90 && nwtr[i] < 97) ||
                              nwtr[i] > 122 ) check=false;
                   } while( nwtr.length() >= 50 || !check);
                   strcpy(newTitolo, nwtr.c_str());
                   break;
            case 3:do{
                       cout<<"Nuovo Anno: "; cin>>nwnn;
                       cin.clear();
                       cin.ignore(10, '\n');
                   } while(cin.fail() || nwnn < -10000 || nwnn > 2018);
                   itoa(nwnn,newAnno,10);
                   break;
            case 4:cout<<"1)Disponibile\n2)Non Disponibile\n3)In Prestito\n4)In Reso\n5)Prenotato\n";
                   do{
                       cout<<".."; cin>>sceltaDisponibilita;
                       cin.clear();
                       cin.ignore(10, '\n');
                   } while(cin.fail() || sceltaDisponibilita < 1 || sceltaDisponibilita > 5);
                   switch(sceltaDisponibilita){
                       case 1: strcpy(newDisponibilita,"Disponibile"); break;
                       case 2: strcpy(newDisponibilita,"Non Disponibile"); break;
                       case 3: strcpy(newDisponibilita,"In Prestito"); break;
                       case 4: strcpy(newDisponibilita,"In Reso"); break;
                       case 5: strcpy(newDisponibilita,"Prenotato"); break;
                   }
                   break;
            case 5:break;
        }
    } while(sceltaModifica != 5);
    l.SetInformazioni(newTitolo, newAutore, newAnno, newCodice, newDisponibilita);
    f.seekp(libroPosition, ios::beg);
    f.write((char*)&l,sizeof(Libro));
    f.close();
    this->UpdateListaPrestiti(&l);
    this->UpdateListaPrestitiInCorso(&l);
}

void Persona::ModificaUtente(){
    int sceltaModifica=0, userNumber=0, userPosition=0, nwPn=0;
    int* vett=new int[1000];
    char newNome[21], newCognome[21], newPin[5], username[21];
    string nwNm, nwCgnm;
    bool check=false;
    Utente u;
    if( !this->RicercaUtente(vett) ) return;
    do{
        cout<<"\nNumero Utente da Modificare: "; cin>>userNumber;
        cin.clear();
        cin.ignore(10, '\n');
        check=false;
        for(unsigned int i=0; i<sizeof(vett)/4; i++) check=userNumber == vett[i];
    } while(cin.fail() || !check);
    userPosition=(userNumber-1)*sizeof(Utente);
    fstream f("CredenzialiUtenti.dat", ios::binary | ios::in | ios::out);
    f.seekp(userPosition, ios::beg);
    f.read((char*)&u,sizeof(Utente));
    strcpy(newNome, u.GetNome());
    strcpy(newCognome, u.GetCognome());
    strcpy(newPin, u.GetPin());
    strcpy(username, u.GetUsername());
    do{
        cout<<"\n  1)Modifica Nome\n  2)Modifica Cognome\n  3)Modifica Pin\n  4)Esci\n";
        do{
            cout<<".."; cin>>sceltaModifica;
            cin.clear();
            cin.ignore(10, '\n');
        } while(cin.fail() || sceltaModifica < 1 || sceltaModifica > 4);
        switch(sceltaModifica){
            case 1:do{
                       cout<<"Nuovo Nome: "; cin.ignore(); getline(cin,nwNm);
                       check=true;
                       for(int i=0; i<20 && nwNm[i] != 0; i++)
                         if( (nwNm[i] != 32 && nwNm[i] < 65) ||
                             (nwNm[i] > 90 && nwNm[i] < 97) ||
                              nwNm[i] > 122 ) check=false;
                   } while( nwNm.length() >= 20 || !check);
                   strcpy(newNome, nwNm.c_str());
                   break;
            case 2:do{
                       cout<<"Nuovo Cognome: "; cin.ignore(); getline(cin,nwCgnm);
                       check=true;
                       for(int i=0; i<20 && nwCgnm[i] != 0; i++)
                         if( (nwCgnm[i] != 32 && nwCgnm[i] < 65) ||
                             (nwCgnm[i] > 90 && nwCgnm[i] < 97) ||
                              nwCgnm[i] > 122 ) check=false;
                   } while( nwCgnm.length() >= 20 || !check);
                   strcpy(newCognome, nwCgnm.c_str());
                   break;
            case 3:do{
                       cout<<"Nuovo Pin: "; cin>>nwPn;
                       cin.clear();
                       cin.ignore(10, '\n');
                   } while(cin.fail() || nwPn < 1000 || nwPn >= 2000);
                   itoa(nwPn,newPin,10);
                   break;
            case 4:break;
        }
    } while(sceltaModifica != 4);
    u.SetUserCredenziali(newPin, newNome, newCognome, username);
    f.seekg(userPosition, ios::beg);
    f.write((char*)&u,sizeof(Utente));
    f.close();
    this->UpdateListaPrestiti(&u);
    this->UpdateListaPrestitiInCorso(&u);
}

void Persona::UpdateListaPrestiti(Utente* uPointer){
    int listaPosition=sizeof(Libro)+sizeof(Utente)+sizeof(Prestito);
    Libro l;
    Utente u;
    Prestito p;
    fstream f("ListaPrestiti.dat", ios::binary | ios::in | ios::out);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        f.close();
        return;
    }
    f.seekg(0,ios::beg);

    f.read((char*)&l,sizeof(Libro));
    f.read((char*)&u,sizeof(Utente));
    f.read((char*)&p,sizeof(Prestito));
    while(!f.eof()){
        if( !strcmp(u.GetUsername(),uPointer->GetUsername()) ){
            f.seekg(-listaPosition,ios::cur);
            f.write((char*)&l,sizeof(Libro));
            f.write((char*)uPointer,sizeof(Utente));
            f.write((char*)&p,sizeof(Prestito));
        }
        f.read((char*)&l,sizeof(Libro));
        f.read((char*)&u,sizeof(Utente));
        f.read((char*)&p,sizeof(Prestito));
    }
    f.close();
}

void Persona::UpdateListaPrestiti(Libro* lPointer){
    int listaPosition=sizeof(Libro)+sizeof(Utente)+sizeof(Prestito);
    Libro l;
    Utente u;
    Prestito p;
    fstream f("ListaPrestiti.dat", ios::binary | ios::in | ios::out);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        f.close();
        return;
    }
    f.seekg(0,ios::beg);

    f.read((char*)&l,sizeof(Libro));
    f.read((char*)&u,sizeof(Utente));
    f.read((char*)&p,sizeof(Prestito));
    while(!f.eof()){
        if( !strcmp(l.GetCodice(),lPointer->GetCodice()) || !strcmp(l.GetTitolo(),lPointer->GetTitolo()) ){
            f.seekg(-listaPosition,ios::cur);
            f.write((char*)lPointer,sizeof(Libro));
            f.write((char*)&u,sizeof(Utente));
            f.write((char*)&p,sizeof(Prestito));
        }
        f.read((char*)&l,sizeof(Libro));
        f.read((char*)&u,sizeof(Utente));
        f.read((char*)&p,sizeof(Prestito));
    }
    f.close();
}

void Persona::UpdateListaPrestitiInCorso(Utente* uPointer){
    int listaPosition=sizeof(Libro)+sizeof(Utente)+sizeof(Prestito);
    Libro l;
    Utente u;
    Prestito p;
    fstream f("ListaPrestitiInCorso.dat", ios::binary | ios::in | ios::out);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        f.close();
        return;
    }
    f.seekg(0,ios::beg);

    f.read((char*)&l,sizeof(Libro));
    f.read((char*)&u,sizeof(Utente));
    f.read((char*)&p,sizeof(Prestito));
    while(!f.eof()){
        if( !strcmp(u.GetUsername(),uPointer->GetUsername()) ){
            f.seekg(-listaPosition,ios::cur);
            f.write((char*)&l,sizeof(Libro));
            f.write((char*)uPointer,sizeof(Utente));
            f.write((char*)&p,sizeof(Prestito));
        }
        f.read((char*)&l,sizeof(Libro));
        f.read((char*)&u,sizeof(Utente));
        f.read((char*)&p,sizeof(Prestito));
    }
    f.close();
}

void Persona::UpdateListaPrestitiInCorso(Libro* lPointer){
    int listaPosition=sizeof(Libro)+sizeof(Utente)+sizeof(Prestito);
    Libro l;
    Utente u;
    Prestito p;
    fstream f("ListaPrestitiInCorso.dat", ios::binary | ios::in | ios::out);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        f.close();
        return;
    }
    f.seekg(0,ios::beg);

    f.read((char*)&l,sizeof(Libro));
    f.read((char*)&u,sizeof(Utente));
    f.read((char*)&p,sizeof(Prestito));
    while(!f.eof()){
        if( !strcmp(l.GetCodice(),lPointer->GetCodice()) || !strcmp(l.GetTitolo(),lPointer->GetTitolo()) ){
            f.seekg(-listaPosition,ios::cur);
            f.write((char*)lPointer,sizeof(Libro));
            f.write((char*)&u,sizeof(Utente));
            f.write((char*)&p,sizeof(Prestito));
        }
        f.read((char*)&l,sizeof(Libro));
        f.read((char*)&u,sizeof(Utente));
        f.read((char*)&p,sizeof(Prestito));
    }
    f.close();
}

time_t Persona::GetDataRegistrazione() {return this->dataRegistrazione;}

void Persona::SetDataRegistrazione() {
    Data d;
    d.SetCurrentDataOra();
    this->dataRegistrazione=d.GetDataOra();
}

char* Persona::GetPin() {return this->pin;}
char* Persona::GetNome() {return this->nome;}
char* Persona::GetCognome() {return this->cognome;}



///////////////DIRETTORE

Direttore::Direttore(char* pin,char* nome,char* cognome) : Persona(pin,nome,cognome){}

void Direttore::ViewListaAddetti(){
    ifstream f("CredenzialiAddetti.dat", ios::binary | ios::in);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        cout<<"\nNessun Addetto Registrato\n";
        f.close();
        return;
    }
    f.seekg(0,ios::beg);

    int i=1;
    time_t data;
    Addetto a;
    cout<<"\n-------------------------- LISTA UTENTI --------------------------\n";
    cout<<"  NOME // COGNOME // PIN // DATA REGISTRAZIONE\n";
    f.read((char*)&a,sizeof(Addetto));
    while(!f.eof()){
        data=a.GetDataRegistrazione();
        cout<<i<<") "<<a.GetNome()<<"  "<<a.GetCognome()<<"  "<<a.GetPin()<<"  "<<ctime(&data);
        f.read((char*)&a,sizeof(Addetto));
        i++;
    }
    cout<<"\n------------------------------------------------------------------\n";
    f.close();
}

bool Direttore::RicercaAddetto(int* vett){
    ifstream f("CredenzialiAddetti.dat", ios::binary | ios::in);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        cout<<"\nNessun Addetto Registrato\n";
        f.close();
        return false;
    }
    f.seekg(0,ios::beg);

    unsigned int length=0, i=0, c=0, m=0, trovati=0, scorsi=1;
    char elementoRicerca[51];
    string elmntRcrc;
    bool check=true;
    Addetto a;
    do{
        cout<<"Inserire Nome, Cognome, Pin.. "; cin.ignore(); getline(cin,elmntRcrc);
        check=true;
        for(int i=0; i<50 && elmntRcrc[i] != 0; i++)
            if( (elmntRcrc[i] != 32 && elmntRcrc[i] < 48) ||
                (elmntRcrc[i] > 57 && elmntRcrc[i] < 65) ||
                (elmntRcrc[i] > 90 && elmntRcrc[i] < 97) ||
                 elmntRcrc[i] > 122 ) check=false;
    } while( elmntRcrc.length() >= 50 || !check);
    strcpy(elementoRicerca, elmntRcrc.c_str());
    length=strlen(elementoRicerca);
    f.read((char*)&a,sizeof(Addetto));
    while(!f.eof()){
        ////RICERA IN NOME
        for(c=0; i<length && c<strlen(a.GetNome()); c++)
            for(i=0,m=c; i<length && a.GetNome()[m] == elementoRicerca[i]; i++,m++);
        ////RICERCA IN COGNOME
        if(i<length)
            for(c=0; i<length && c<strlen(a.GetCognome()); c++)
                for(i=0,m=c; i<length && a.GetCognome()[m] == elementoRicerca[i]; i++,m++);
        ////RICERA IN PIN
        if(i<length)
            for(c=0; i<length && c<strlen(a.GetPin()); c++)
                for(i=0,m=c; i<length && a.GetPin()[m] == elementoRicerca[i]; i++,m++);
        if(i == length){
            vett[trovati]=scorsi;
            cout<<scorsi<<") ";
            cout<<a.GetNome()<<"\t";
            cout<<a.GetCognome()<<"\t";
            cout<<a.GetPin()<<endl;
            trovati++;
        }
        scorsi++;
        i=0;
        f.read((char*)&a,sizeof(Addetto));
    }
    f.close();
    if(trovati == 0){
        cout<<"Nessun Addetto Trovato..\n";
        return false;
    }
    else {
        cout<<"Addetti Trovati: "<<trovati<<endl;
        return true;
    }
}

void Direttore::RegistrazioneAddetto(){
    Registrazione r;
    r.NewRegistrazione('a');
}

void Direttore::ModificaPrestito(){
    int  prestitoNumber=0, prestitoPosition=0, giorni=0;
    int* vett=new int[1000];
    bool check=false;
    Libro l;
    Utente u;
    Prestito p;
    Data d;
    if( !this->RicercaPrestito(vett) ) return;
    do{
        cout<<"Numero Prestito da Modificare: "; cin>>prestitoNumber;
        cin.clear();
        cin.ignore(10, '\n');
        check=false;
        for(unsigned int i=0; i<sizeof(vett)/4; i++) check=prestitoNumber == vett[i];
    } while(cin.fail() || !check);
    prestitoPosition=(prestitoNumber-1)*( sizeof(Libro)+sizeof(Utente)+sizeof(Prestito) );
    fstream f("ListaPrestitiInCorso.dat", ios::binary | ios::in | ios::out);
    f.seekp(prestitoPosition, ios::beg);
    f.read((char*)&l,sizeof(Libro));
    f.read((char*)&u,sizeof(Utente));
    f.read((char*)&p,sizeof(Prestito));
    do{
        cout<<"Numero Giorni da Concedere("<<-p.GetDifferenza()<<"/+30): "; cin>>giorni;
        cin.clear();
        cin.ignore(10, '\n');
    } while(cin.fail() || giorni < -p.GetDifferenza() || giorni >30);
    d.SetCurrentDataOra();
    p.SetDataScadenza(d.GetDataOraEstesa(p.GetDataScadenza(),giorni));
    f.seekp(prestitoPosition, ios::beg);
    f.write((char*)&l,sizeof(Libro));
    f.write((char*)&u,sizeof(Utente));
    f.write((char*)&p,sizeof(Prestito));
    f.close();
}

void Direttore::ModificaAddetto(){
    int sceltaModifica=0, agentNumber=0, agentPosition=0, nwPn=0;
    int* vett=new int[1000];
    char newNome[21], newCognome[21], newPin[5];
    string nwNm, nwCgnm;
    bool check=false;
    Addetto a;
    if( !this->RicercaAddetto(vett) ) return;
    do{
        cout<<"Numero Addetto da Modificare: "; cin>>agentNumber;
        cin.clear();
        cin.ignore(10, '\n');
        check=false;
        for(unsigned int i=0; i<sizeof(vett)/4; i++) if(agentNumber == vett[i]) check=true;
    } while(cin.fail() || !check);
    agentPosition=(agentNumber-1)*sizeof(Addetto);
    fstream f("CredenzialiAddetti.dat", ios::binary | ios::in | ios::out);
    f.seekp(agentPosition, ios::beg);
    f.read((char*)&a,sizeof(Addetto));
    strcpy(newNome, a.GetNome());
    strcpy(newCognome, a.GetCognome());
    strcpy(newPin, a.GetPin());
    do{
        cout<<"\n  1)Modifica Nome\n  2)Modifica Cognome\n  3)Modifica Pin\n  4)Esci\n";
        do{
            cout<<".."; cin>>sceltaModifica;
            cin.clear();
            cin.ignore(10, '\n');
        } while(cin.fail() || sceltaModifica < 1 || sceltaModifica > 4);
        switch(sceltaModifica){
            case 1:do{
                       cout<<"Nuovo Nome: "; cin.ignore(); getline(cin,nwNm);
                       check=true;
                       for(int i=0; i<20 && nwNm[i] != 0; i++)
                         if( (nwNm[i] != 32 && nwNm[i] < 65) ||
                             (nwNm[i] > 90 && nwNm[i] < 97) ||
                              nwNm[i] > 122 ) check=false;
                   } while( nwNm.length() >= 20 || !check);
                   strcpy(newNome, nwNm.c_str());
                   break;
            case 2:do{
                       cout<<"Nuovo Cognome: "; cin.ignore(); getline(cin,nwCgnm);
                       check=true;
                       for(int i=0; i<20 && nwCgnm[i] != 0; i++)
                         if( (nwCgnm[i] != 32 && nwCgnm[i] < 65) ||
                             (nwCgnm[i] > 90 && nwCgnm[i] < 97) ||
                              nwCgnm[i] > 122 ) check=false;
                   } while( nwCgnm.length() >= 20 || !check);
                   strcpy(newCognome, nwCgnm.c_str());
                   break;
            case 3:do{
                       cout<<"Nuovo Pin: "; cin>>nwPn;
                       cin.clear();
                       cin.ignore(10, '\n');
                   } while(cin.fail() || nwPn < 1000 || nwPn >= 2000);
                   itoa(nwPn,newPin,10);
                   break;
            case 4:break;
        }
    } while(sceltaModifica != 4);
    a.SetCredenziali(newPin, newNome, newCognome);
    f.seekp(agentPosition, ios::beg);
    f.write((char*)&a,sizeof(Addetto));
    f.close();
}

void Direttore::EliminazioneLibro(){
    int libroNumber=0, libroPosition=0;
    int* vett=new int[1000];
    char codiceLibro[4];
    bool check=false;
    Libro l;
    Catalogo c;
    if( !c.RicercaLibro(vett) ) return;
    do{
        cout<<"Numero Libro da Eliminare: "; cin>>libroNumber;
        cin.clear();
        cin.ignore(10, '\n');
        check=false;
        for(unsigned int i=0; i<sizeof(vett)/4; i++) check=libroNumber == vett[i];
    } while(cin.fail() || !check);
    libroPosition=(libroNumber)*sizeof(Libro);
    ifstream f("Catalogo.dat", ios::binary | ios::in);
    ofstream f1("CatalogoTemp.dat", ios::binary | ios::out);
    f.read((char*)&l,sizeof(Libro));
    while(!f.eof()){
        if(f.tellg() != libroPosition) f1.write((char*)&l,sizeof(Libro));
        else strcpy(codiceLibro, l.GetCodice());
        f.read((char*)&l,sizeof(Libro));
    }
    f1.close();
    f.close();
    remove( "Catalogo.dat" );
    rename( "CatalogoTemp.dat" , "Catalogo.dat" );
    this->EliminazioneInListaPrestiti(codiceLibro);
    this->EliminazioneInListaPrestitiInCorso(codiceLibro);
}

void Direttore::EliminazionePrestito(){
    int  prestitoNumber=0, prestitoPosition=0;
    int* vett=new int[1000];
    bool check=false;
    Catalogo c;
    Libro l;
    Utente u;
    Prestito p;
    Data d;
    if( !this->RicercaPrestito(vett) ) return;
    do{
        cout<<"Numero Prestito da Eliminare: "; cin>>prestitoNumber;
        cin.clear();
        cin.ignore(10, '\n');
        check=false;
        for(unsigned int i=0; i<sizeof(vett)/4; i++) check=prestitoNumber == vett[i];
    } while(cin.fail() || !check);
    prestitoPosition=prestitoNumber*( sizeof(Libro)+sizeof(Utente)+sizeof(Prestito) );
    ifstream f("ListaPrestitiInCorso.dat", ios::binary | ios::in);
    ofstream f1("ListaPrestitiInCorsoTemp.dat", ios::binary | ios::out);
    f.read((char*)&l,sizeof(Libro));
    f.read((char*)&u,sizeof(Utente));
    f.read((char*)&p,sizeof(Prestito));
    while(!f.eof()){
        if(f.tellg() != prestitoPosition){
            f1.write((char*)&l,sizeof(Libro));
            f1.write((char*)&u,sizeof(Utente));
            f1.write((char*)&p,sizeof(Prestito));
        }
        f.read((char*)&l,sizeof(Libro));
        f.read((char*)&u,sizeof(Utente));
        f.read((char*)&p,sizeof(Prestito));
    }
    f1.close();
    f.close();
    remove( "ListaPrestitiInCorso.dat" );
    rename( "ListaPrestitiInCorsoTemp.dat" , "ListaPrestitiInCorso.dat" );
    l.SetDisponibilita("Disponibile");
    c.UpdateCatalogo(&l);
}

void Direttore::EliminazioneInListaPrestiti(char* username, char* codiceLibro){
    Libro l;
    Utente u;
    Prestito p;
    ifstream f("ListaPrestiti.dat", ios::binary | ios::in);
    ofstream f1("ListaPrestitiTemp.dat", ios::binary | ios::out);
    f.read((char*)&l,sizeof(Libro));
    f.read((char*)&u,sizeof(Utente));
    f.read((char*)&p,sizeof(Prestito));
    while(!f.eof()){
        if( strcmp(u.GetUsername(), username) && strcmp(l.GetCodice(), codiceLibro) ){
            f1.write((char*)&l,sizeof(Libro));
            f1.write((char*)&u,sizeof(Utente));
            f1.write((char*)&p,sizeof(Prestito));
        }
        f.read((char*)&l,sizeof(Libro));
        f.read((char*)&u,sizeof(Utente));
        f.read((char*)&p,sizeof(Prestito));
    }
    f1.close();
    f.close();
    remove( "ListaPrestiti.dat" );
    rename( "ListaPrestitiTemp.dat" , "ListaPrestiti.dat" );
}

void Direttore::EliminazioneInListaPrestitiInCorso(char* username, char* codiceLibro){
    Catalogo c;
    Libro l;
    Utente u;
    Prestito p;
    ifstream f("ListaPrestitiInCorso.dat", ios::binary | ios::in);
    ofstream f1("ListaPrestitiInCorsoTemp.dat", ios::binary | ios::out);
    f.read((char*)&l,sizeof(Libro));
    f.read((char*)&u,sizeof(Utente));
    f.read((char*)&p,sizeof(Prestito));
    while(!f.eof()){
        if( strcmp(u.GetUsername(), username) && strcmp(l.GetCodice(), codiceLibro) ){
            f1.write((char*)&l,sizeof(Libro));
            f1.write((char*)&u,sizeof(Utente));
            f1.write((char*)&p,sizeof(Prestito));
        }
        f.read((char*)&l,sizeof(Libro));
        f.read((char*)&u,sizeof(Utente));
        f.read((char*)&p,sizeof(Prestito));
    }
    f1.close();
    f.close();
    remove( "ListaPrestitiInCorso.dat" );
    rename( "ListaPrestitiInCorsoTemp.dat" , "ListaPrestitiInCorso.dat" );
    c.UpdateCatalogo(&l);
}

void Direttore::EliminazioneAddetto(){
    int agentNumber=0, agentPosition=0;
    int* vett=new int[1000];
    bool check=false;
    Addetto a;
    if( !this->RicercaAddetto(vett) ) return;
    do{
        cout<<"Numero Addetto da Eliminare: "; cin>>agentNumber;
        cin.clear();
        cin.ignore(10, '\n');
        check=false;
        for(unsigned int i=0; i<sizeof(vett)/4; i++) check=agentNumber == vett[i];
    } while(cin.fail() || !check);
    agentPosition=(agentNumber)*sizeof(Addetto);
    ifstream f("CredenzialiAddetti.dat", ios::binary | ios::in);
    ofstream f1("CredenzialiAddettiTemp.dat", ios::binary | ios::out);
    f.read((char*)&a,sizeof(Addetto));
    while(!f.eof()){
        if(f.tellg() != agentPosition) f1.write((char*)&a,sizeof(Addetto));
        f.read((char*)&a,sizeof(Addetto));
    }
    f1.close();
    f.close();
    remove( "CredenzialiAddetti.dat" );
    rename( "CredenzialiAddettiTemp.dat" , "CredenzialiAddetti.dat" );
}

void Direttore::EliminazioneUtente(){
    int userNumber=0, userPosition=0;
    int* vett=new int[1000];
    char username[21];
    bool check=false;
    Utente u;
    if( !this->RicercaUtente(vett) ) return;
    do{
        cout<<"Numero Utente da Eliminare: "; cin>>userNumber;
        cin.clear();
        cin.ignore(10, '\n');
        check=false;
        for(unsigned int i=0; i<sizeof(vett)/4; i++) check=userNumber == vett[i];
    } while(cin.fail() || !check);
    userPosition=(userNumber)*sizeof(Utente);
    ifstream f("CredenzialiUtenti.dat", ios::binary | ios::in);
    ofstream f1("CredenzialiUtentiTemp.dat", ios::binary | ios::out);
    f.read((char*)&u,sizeof(Utente));
    while(!f.eof()){
        if(f.tellg() != userPosition) f1.write((char*)&u,sizeof(Utente));
        else strcpy(username, u.GetUsername());
        f.read((char*)&u,sizeof(Utente));
    }
    f1.close();
    f.close();
    remove( "CredenzialiUtenti.dat" );
    rename( "CredenzialiUtentiTemp.dat" , "CredenzialiUtenti.dat" );
    this->EliminazioneInListaPrestiti(username);
    this->EliminazioneInListaPrestitiInCorso(username);
}



///////////////ADDETTO

Addetto::Addetto(char* pin,char* nome,char* cognome)  : Persona(pin,nome,cognome) {this->SetDataRegistrazione();}



///////////////UTENTE

Utente::Utente(char* pin, char* nome, char* cognome, char* username) : Persona(pin, nome, cognome) {
    this->SetDataRegistrazione();
    strcpy(this->username, username);
}

Utente::Utente() : Persona("", "", "") {}

void Utente::RichiestaPrestito(Utente *uPointer){
    int libroNumber=0, libroPosition=0;
    int* vett=new int[1000];
    bool check=false;
    Prestito p;
    Libro l;
    Catalogo c;
    if( !c.RicercaLibro(vett) ) return;
    do{
        cout<<"Numero Libro: "; cin>>libroNumber;
        cin.clear();
        cin.ignore(10, '\n');
        check=false;
        for(unsigned int i=0; i<sizeof(vett)/4; i++) check=libroNumber == vett[i];
    } while(cin.fail() || !check);
    libroPosition=(libroNumber-1)*sizeof(Libro);
    fstream f("Catalogo.dat", ios::binary | ios::in | ios::out);
    f.seekp(libroPosition, ios::beg);
    f.read((char*)&l,sizeof(Libro));
    if( strcmp("Disponibile", l.GetDisponibilita()) ){
        cout<<"\nLibro momentaneamente non disponibile ";
        if( !strcmp("In Prestito", l.GetDisponibilita()) ) cout<<"(In Prestito)";
        if( !strcmp("In Reso", l.GetDisponibilita()) ) cout<<"(In Reso)";
        if( !strcmp("Prenotato", l.GetDisponibilita()) ) cout<<"(Prenotato)";
        return;
    }
    p.SetCodice(l.GetCodice());
    l.SetDisponibilita("Prenotato");
    c.UpdateCatalogo(&l);
    f.close();
    cout<<"\nLibro Prenotato!\n\n";
    p.SetData();
    ofstream f1("ListaPrestiti.dat", ios::binary | ios::app);
    f1.write((char*)&l,sizeof(Libro));
    f1.write((char*)uPointer,sizeof(Utente));
    f1.write((char*)&p,sizeof(Prestito));
    f1.close();
}

void Utente::SetUserCredenziali(char* pin, char* nome, char* cognome, char* username){
    this->SetCredenziali(pin, nome, cognome);
    strcpy(this->username, username);
}

char* Utente::GetUsername() {return this->username;}



////////////////////LIBRO

Libro::Libro(char* titolo, char* autore, char* anno, char* disponibilita, bool cod){
    if(!cod){
        int i=0, endPosition=0;
        string cdcStr;
        ifstream f("CodeCounter.dat", ios::binary | ios::in | ios::app);
        f.seekg(0,ios::end);
        endPosition=f.tellg();
        f.seekg(0,ios::beg);
        if(endPosition > 1) f.read((char*)&i,sizeof(int));
        f.close();
        ofstream f1("CodeCounter.dat", ios::binary | ios::out | ios::trunc);
        i++;
        f1.write((char*)&i,sizeof(int));
        f1.close();
        if(i < 10) cdcStr="00" + to_string(i);
        else if(i < 100) cdcStr="0" + to_string(i);
        else cdcStr=to_string(i);
        strcpy(this->codice, cdcStr.c_str());
    }
    else strcpy(this->codice, "");
    strcpy(this->titolo, titolo);
    strcpy(this->autore, autore);
    strcpy(this->anno, anno);
    strcpy(this->disponibilita, disponibilita);
}

void Libro::Write(Libro *puntInFile){
    ofstream f("Catalogo.dat", ios::binary | ios::app);
    f.write((char*)puntInFile,sizeof(Libro));
    f.close();
}

void Libro::SetInformazioni(char* titolo, char* autore, char* anno, char* codice, char* disponibilita){
    strcpy(this->titolo, titolo);
    strcpy(this->autore, autore);
    strcpy(this->anno, anno);
    strcpy(this->codice, codice);
    strcpy(this->disponibilita, disponibilita);
}

char* Libro::GetTitolo() {return this->titolo;}
char* Libro::GetAutore() {return this->autore;}
char* Libro::GetAnno() {return this->anno;}
char* Libro::GetCodice() {return this->codice;}
void Libro::SetCodice(char* codice) {strcpy(this->codice, codice);}
char* Libro::GetDisponibilita() {return this->disponibilita;}
void Libro::SetDisponibilita(char* disponibilita) {strcpy(this->disponibilita, disponibilita);}



/////////////////CATALOGO

Catalogo::Catalogo(){
    fstream f("Catalogo.dat", ios::binary | ios::in | ios::out);
    f.seekg(0, ios::end);
    if(f.tellg() < 2){
        f.close();
        return;
    }
    f.seekg(0,ios::beg);

    bool check=true;
    Libro l1;
    Utente u;
    Prestito p;
    f.read((char*)&this->l,sizeof(Libro));
    while(!f.eof()){
        if( !strcmp(this->l.GetDisponibilita(),"In Prestito") ){
            ifstream f1("ListaPrestitiInCorso.dat", ios::binary | ios::in);
            ofstream f2("ListaPrestitiInCorsoTemp.dat", ios::binary | ios::app);
            f1.read((char*)&l1,sizeof(Libro));
            f1.read((char*)&u,sizeof(Utente));
            f1.read((char*)&p,sizeof(Prestito));
            while(!f1.eof()){
                if( !strcmp(l1.GetCodice(),this->l.GetCodice()) ){
                    Data d;
                    d.SetCurrentDataOra();
                    if ( p.GetDifferenza() <= 0 ){
                        check=false;
                        //cout<<"\nAggiornamento Disponibilita' del Libro '"<<this->l.GetTitolo()<<"'\n";
                        l1.SetDisponibilita("In Reso");
                        ofstream f3("ListaPrestitiScaduti.dat", ios::binary | ios::app);
                        f3.write((char*)&l1,sizeof(Libro));
                        f3.close();
                        this->UpdateCatalogo(&l1);
                    }
                    else check=true;
                }
                if(check) f2.write((char*)&l1,sizeof(Libro));
                f1.read((char*)&l1,sizeof(Libro));
                f1.read((char*)&u,sizeof(Utente));
                f1.read((char*)&p,sizeof(Prestito));
            }
            f1.close();
        }
        f.read((char*)&this->l,sizeof(Libro));
    }
    f.close();
    remove( "ListaPrestitiInCorso.dat" );
    rename( "ListaPrestitiInCorsoTemp.dat", "ListaPrestitiInCorso.dat" );
}

void Catalogo::VisualizzaCatalogo(){
    ifstream f("Catalogo.dat", ios::binary | ios::in);
    f.seekg(0, ios::end);
    if(f.tellg() < 2){
        cout<<"\nNessun Libro ancora inserito in Catalogo\n";
        f.close();
        return;
    }
    f.seekg(0,ios::beg);

    cout<<"\n-------------------------- LISTA LIBRI --------------------------\n";
    cout<<"      TITOLO     // AUTORE // ANNO // CODICE // DISPONIBILITA'\n";
    f.read((char*)&this->l,sizeof(Libro));
    while(!f.eof()){
        cout<<this->l.GetTitolo()<<"\t";
        cout<<this->l.GetAutore()<<"\t";
        cout<<this->l.GetAnno()<<"\t";
        cout<<this->l.GetCodice()<<"\t";
        cout<<this->l.GetDisponibilita()<<"\n";
        f.read((char*)&this->l,sizeof(Libro));
    }
    cout<<"\n----------------------------------------------------------------\n";
    f.close();
}

void Catalogo::UpdateCatalogo(Libro* lPointer){
    fstream f("Catalogo.dat", ios::binary | ios::in | ios::out);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        cout<<"\nNessun Libro in Catalogo\n";
        f.close();
        return;
    }
    f.seekg(0,ios::beg);

    int libroSize=sizeof(Libro);
    f.read((char*)&this->l,sizeof(Libro));
    while( !f.eof() && strcmp(this->l.GetCodice(), lPointer->GetCodice()) ) f.read((char*)&this->l,sizeof(Libro));
    f.seekg(-libroSize,ios::cur);
    f.write((char*)lPointer, sizeof(Libro));
    f.close();
}

bool Catalogo::RicercaLibro(int* vett){
    ifstream f("Catalogo.dat", ios::binary | ios::in);
    f.seekg(0,ios::end);
    if(f.tellg() < 2){
        cout<<"\nNessun Libro in Catalogo\n";
        f.close();
        return false;
    }
    f.seekg(0,ios::beg);

    unsigned int length=0, i=0, c=0, m=0, trovati=0, scorsi=1;
    char elementoRicerca[51];
    string elmntRcrc;
    bool check=true;
    do{
        cout<<"Inserire Titolo, Autore, Anno, Codice.. "; cin.ignore(); getline(cin,elmntRcrc);
        check=true;
        for(int i=0; i<50 && elmntRcrc[i] != 0; i++)
            if( (elmntRcrc[i] != 32 && elmntRcrc[i] < 48) ||
                (elmntRcrc[i] > 57 && elmntRcrc[i] < 65) ||
                (elmntRcrc[i] > 90 && elmntRcrc[i] < 97) ||
                 elmntRcrc[i] > 122 ) check=false;
    } while( elmntRcrc.length() >= 50 || !check);
    strcpy(elementoRicerca, elmntRcrc.c_str());
    length=strlen(elementoRicerca);
    f.read((char*)&this->l,sizeof(Libro));
    while(!f.eof()){
        //cout<<"Entrata, "<<i<<"\n";
        ////RICERA IN TITOLO
        for(c=0; i<length && c<strlen(this->l.GetTitolo()); c++)
            for(i=0,m=c; i<length && this->l.GetTitolo()[m] == elementoRicerca[i]; i++,m++);
        //cout<<"Titolo, "<<i<<"\n";
        ////RICERCA IN AUTORE
        if(i<length)
            for(c=0; i<length && c<strlen(this->l.GetAutore()); c++)
                for(i=0,m=c; i<length && this->l.GetAutore()[m] == elementoRicerca[i]; i++,m++);
        //cout<<"Autore, "<<i<<"\n";
        ////RICERA IN ANNO
        if(i<length)
            for(c=0; i<length && c<strlen(this->l.GetAnno()); c++)
                for(i=0,m=c; i<length && this->l.GetAnno()[m] == elementoRicerca[i]; i++,m++);
        //cout<<"Anno, "<<i<<"\n";
        ////RICERA IN CODICE
        if(i<length)
            for(c=0; i<length && c<strlen(this->l.GetCodice()); c++)
                for(i=0,m=c; i<length && this->l.GetCodice()[m] == elementoRicerca[i]; i++,m++);
        //cout<<"Codice, "<<i<<"\n";
        if(i == length){
            vett[trovati]=scorsi;
            cout<<scorsi<<") ";
            cout<<this->l.GetTitolo()<<"\t";
            cout<<this->l.GetAutore()<<"\t";
            cout<<this->l.GetAnno()<<"\t";
            cout<<this->l.GetCodice()<<"\t";
            cout<<this->l.GetDisponibilita()<<endl;
            trovati++;
        }
        scorsi++;
        i=0;
        f.read((char*)&this->l,sizeof(Libro));
    }
    f.close();
    if(trovati == 0){
        cout<<"Nessun Elemento Trovato..\n";
        return false;
    }
    else {
        cout<<"Libri Trovati: "<<trovati<<endl;
        return true;
    }
}



//////////////////////PIN

Pin::~Pin() {/*cout<<"\n---------DISTRUTTORE Pin---------\n";*/}

char* Pin::GetPin(){
    srand (time(NULL));
    int pin_intero=rand() % 999+1000;
    itoa(pin_intero,pin,10);
    return pin;
}



///////////////////////REGISTRAZIONE

Registrazione::Registrazione() {this->isRegistrato=false;}

void Registrazione::NewRegistrazione(char registrationMode){
    string nm, cgnm;
    bool check=true;
    do{
        cout<<"Inserire Nome: "; getline(cin,nm);
        check=true;
        for(int i=0; i<20 && nm[i] != 0; i++)
            if( (nm[i] != 32 && nm[i] < 65) ||
                (nm[i] > 90 && nm[i] < 97) ||
                 nm[i] > 122 ) check=false;
        cin.clear();
    } while( nm.length() >= 20 || !check);
    do{
        cout<<"Inserire Cognome: "; getline(cin,cgnm);
        check=true;
        for(int i=0; i<20 && cgnm[i] != 0; i++)
            if( (cgnm[i] != 32 && cgnm[i] < 65) ||
                (cgnm[i] > 90 && cgnm[i] < 97) ||
                 cgnm[i] > 122 ) check=false;
        cin.clear();
    } while( cgnm.length() >= 20 || !check);
    strcpy(this->nome, nm.c_str());
    strcpy(this->cognome, cgnm.c_str());
    strcpy(this->pin, this->p.GetPin());
    cout<<"Pin Generato: "<<this->pin<<endl;

    //SCRITTURA SU VARI FILE
    switch(registrationMode){
        case 'd':{
                 Direttore d(this->pin,this->nome,this->cognome);
                 ofstream f("CredenzialiDirettore.dat",ios::binary | ios::app);
                 f.write((char*)&d,sizeof(Direttore));
                 f.close();
           }break;
        case 'a':{
                 Addetto a(this->pin,this->nome,this->cognome);
                 ofstream f("CredenzialiAddetti.dat",ios::binary | ios::app);
                 f.write((char*)&a,sizeof(Addetto));
                 f.close();
           }break;
        case 'u':{
                 cout<<"\nUsername: "; cin>>username;
                 Utente u(this->pin,this->nome,this->cognome, this->username);
                 ofstream f("CredenzialiUtenti.dat",ios::binary | ios::app);
                 f.write((char*)&u,sizeof(Utente));
                 f.close();
           }break;
    }
    this->isRegistrato=true;
}

char* Registrazione::GetNome() {return this->nome;}
char* Registrazione::GetCognome() {return this->cognome;}
char* Registrazione::GetPin() {return this->pin;}
char* Registrazione::GetUsername() {return this->username;}
bool Registrazione::GetIsRegistrato() {return this->isRegistrato;}



////////////LOGIN

Login::Login() {this->isLoggato=false;}

void Login::NewLogin(char loginMode){
    int pin=0;
    char pinLogin[5], usernameLogin[21];
    bool check=true;
    switch(loginMode){
        case 'd':{
                 Direttore d;
                 do{
                    cout<<"Inserire Pin: "; cin>>pin;
                    cin.clear();
                    cin.ignore(10, '\n');
                 } while(cin.fail() || pin<1000 || pin>=2000);
                 itoa(pin,pinLogin,10);
                 ifstream f("CredenzialiDirettore.dat",ios::binary | ios::in);
                 f.read((char*)&d,sizeof(Direttore));
                 f.close();
                 this->isLoggato=!strcmp(pinLogin , d.GetPin());
                 if(this->isLoggato) cout<<"\nSalve "<<d.GetNome()<<" "<<d.GetCognome()<<" !\n";
           }break;
        case 'a':{
                 Addetto a;
                 do{
                    cout<<"Inserire Pin: "; cin>>pin;
                    cin.clear();
                    cin.ignore(10, '\n');
                 } while(cin.fail() || pin<1000 || pin>=2000);
                 itoa(pin,pinLogin,10);
                 ifstream f("CredenzialiAddetti.dat",ios::binary | ios::in);
                 do{
                    f.read((char*)&a,sizeof(Addetto));
                    this->isLoggato=!strcmp(pinLogin,a.GetPin());
                 } while(!f.eof() && !this->isLoggato);
                 f.close();
                 if(this->isLoggato) cout<<"\nSalve "<<a.GetNome()<<" "<<a.GetCognome()<<"!\n";
                 strcpy(this->nome, a.GetNome());
                 strcpy(this->cognome, a.GetCognome());
                 strcpy(this->pin, a.GetPin());
           }break;
        case 'u':{
                 string usnLgn;
                 Utente u;
                 do{
                     cout<<"Inserire Username: "; cin.ignore(); getline(cin,usnLgn);
                     check=true;
                     for(int i=0; i<20 && usnLgn[i] != 0; i++)
                         if( (usnLgn[i] != 32 && usnLgn[i] < 48) ||
                             (usnLgn[i] > 57 && usnLgn[i] < 65) ||
                             (usnLgn[i] > 90 && usnLgn[i] < 97) ||
                              usnLgn[i] > 122 ) check=false;
                 } while( usnLgn.length() >= 20 || !check);
                 strcpy(usernameLogin, usnLgn.c_str());
                 do{
                    cout<<"Inserire Pin: "; cin>>pin;
                    cin.clear();
                    cin.ignore(10, '\n');
                 } while(cin.fail() || pin<1000 || pin>=2000);
                 itoa(pin,pinLogin,10);
                 ifstream f("CredenzialiUtenti.dat",ios::binary | ios::in);
                 f.read((char*)&u,sizeof(Utente));
                 while(!f.eof()){
                    if( strcmp(usernameLogin,u.GetUsername()) ){
                        cout<<"Username Errato!";
                        this->isLoggato=false;
                        return;
                    }
                    else if( strcmp(pinLogin,u.GetPin()) ){
                        cout<<"Pin Errato!";
                        this->isLoggato=false;
                        return;
                    }
                    f.read((char*)&u,sizeof(Utente));
                 }
                 this->isLoggato=true;
                 f.close();
                 cout<<"\nSalve "<<u.GetNome()<<" "<<u.GetCognome()<<" ("<<u.GetUsername()<<")\n";
                 strcpy(this->nome, u.GetNome());
                 strcpy(this->cognome, u.GetCognome());
                 strcpy(this->pin, u.GetPin());
                 strcpy(this->username, u.GetUsername());
           }break;
    }
}

char* Login::GetNome() {return this->nome;}
char* Login::GetCognome() {return this->cognome;}
char* Login::GetPin() {return this->pin;}
char* Login::GetUsername() {return this->username;}
bool Login::GetIsLoggato() {return this->isLoggato;}



///////DATA

Data::Data() {}

void Data::SetCurrentDataOra() {this->dataOra = time(0);}

time_t Data::GetDataOra() {return this->dataOra;}

time_t Data::GetDataOra30Days(time_t data){
    struct tm* tm = localtime(&data);
    tm->tm_mday += 30;
    return mktime(tm);
}

time_t Data::GetDataOraEstesa(time_t scadenza, int giorni){
    struct tm* tm = localtime(&scadenza);
    tm->tm_mday += giorni;
    return mktime(tm);
}



////////////PRESTITO

Prestito::Prestito() {}

void Prestito::SetData(){
    Data d;
    d.SetCurrentDataOra();
    this->dataAccettazione=d.GetDataOra();
    this->dataScadenza=d.GetDataOra30Days(this->dataAccettazione);
}

int Prestito::GetDifferenza(){
    Data d;
    d.SetCurrentDataOra();
    return difftime(this->dataScadenza, d.GetDataOra()) / (60*60*24) ;
}

char* Prestito::GetCodice() {return this->codiceLibro;}
void Prestito::SetCodice(char* codice) {strcpy(this->codiceLibro, codice);}
time_t Prestito::GetDataAccettazione() {return this->dataAccettazione;}
time_t Prestito::GetDataScadenza() {return this->dataScadenza;}
void Prestito::SetDataScadenza(time_t newDataScadenza) {this->dataScadenza=newDataScadenza;}
