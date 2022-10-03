/*!
    \file classi.h
    \brief Header per la prototipazione delle classi.
*/
#ifndef CLASSI_H_INCLUDED
#define CLASSI_H_INCLUDED

/*! \file classi.h
    \brief File di Prototipazione.

    Racchiude l'intera struttura prototipata di ogni classe.
*/

class Persona;
class Direttore;
class Addetto;
class Utente;
class Catalogo;
class Libro;
class Pin;
class Registrazione;
class Login;
class Data;
class Prestito;


class Persona{
    char nome[21], cognome[21], pin[5];
    time_t dataRegistrazione;
    public:
        /*! \fn Persona(char*, char*, char*)
            \brief Costruttore Persona.

        Richiede 3 parametri in entrata: nome, cognome, pin.
        */
        /*! \fn ~Persona()
            \brief Distruttore Persona.
        */
        /*! \fn void SetCredenziali(char*, char*, char*)
            \brief Setter delle credenziali.

        Funge da metodo setter per i 3 parametri: Nome, Cognome, Pin.
        */
        /*! \fn void ViewListaPrestiti()
            \brief Visualizzatore della Lista Prestiti.

        Mostra il singolo prestito richiesto dall'Utente ne chiede l'accettazione da parte del relativo Addetto/Direttore.
        */
        /*! \fn void ViewListaPrestitiInCorso()
            \brief Visualizzatore della Lista Prestiti In Corso.

        Mostra la lista dei prestiti in corso indicandone: Titolo Libro, Nome, Cognome, Username Utente,\n
        Data Accettazione, Data Scadenza, Giorni mancanti alla scadenza.
        */
        /*! \fn void ViewListaPrestitiScaduti()
            \brief Visualizzatore della Lista Prestiti Scaduti.

        Mostra il singolo prestito scaduto e ne chiede la conferma del reso da parte del relativo Addetto/Direttore.
        */
        /*! \fn void ViewListaUtenti()
            \brief Visualizzatore della Lista Utenti.

        Mostra la lista degli Utenti indicandone: Nome, Cognome, Username, Pin, Data Registrazione.
        */
        /*! \fn bool RicercaPrestito(int* vett=new int[1000])
            \brief Ricercatore del Prestito.
            \param[out] Conferma booleana presenza record in file.

        Richiede un testo in input, che varra' come parola chiave da ricercare in\n
        Nome, Cognome Utente, Titolo, Autore, Anno, Codice Libro.\n
        Restituisce, come indirizzo, un int*[1000] contenente gli indici dei singoli Prestiti trovati.
        */
        /*! \fn bool RicercaUtente(int* vett=new int[1000])
            \brief Ricercatore del Prestito.
            \param[out] Conferma booleana presenza record in file.

        Richiede un testo in input, che varra' come parola chiave da ricercare in Nome, Cognome, Pin.\n
        Restituisce, come indirizzo, un int*[1000] contenente gli indici dei singoli Utenti trovati.
        */
        /*! \fn void RegistrazioneUtente()
            \brief Registratore dell'Utente.

        Richiede Nome, Cognome e Username da tastiera e fornisce il relativo Pin generato automaticamente.
        */
        /*! \fn void ModificaLibro()
            \brief Modificatore del Libro.

        Richiamando la funzione RicercaLibro() ne chiede la selezione del Libro e, una volta selezionato,\n
        elenca i parametri che si vogliono modificare, a scelta tra Titolo, Autore, Anno, Codice.\n
        La modifica avviene sia nel Catalogo, sia nella Lista Prestiti Scaduti, In Corso e Richiesti.
        */
        /*! \fn void ModificaUtente()
            \brief Modificatore dell'Utente.

        Richiamando la funzione RicercaUtente() ne chiede la selezione dell'Utente e, una volta selezionato,\n
        elenca i parametri che si vogliono modificare, a scelta tra Nome, Cognome, Pin.\n
        La modifica avviene sia nella Lista Utenti, sia nella Lista Prestiti Scaduti, In Corso e Richiesti.
        */
        /*! \fn void UpdateListaPrestiti(Utente*)
            \brief Metodo per la modifica di Utenti in Lista Prestiti Richiesti.
        */
        /*! \fn void UpdateListaPrestiti(Addetto*)
            \brief Metodo per la modifica di Addetti in Lista Prestiti Richiesti.
        */
        /*! \fn void UpdateListaPrestitiInCorso(Utente*)
            \brief Metodo per la modifica di Utenti in Lista Prestiti In Corso.
        */
        /*! \fn void UpdateListaPrestitiInCorso(Addetto*)
            \brief Metodo per la modifica di Addetti in Lista Prestiti In Corso.
        */
        /*! \fn void GetDataRegistrazione()
            \brief Getter per la Data di Registrazione.
            \param[out] time_t dataRegistrazione
        */
        /*! \fn void SetDataRegistrazione()
            \brief Setter per la Data di Registrazione.
        */
        /*! \fn char* GetPin()
            \brief Getter per il Pin.
            \param[out] char* pin
        */
        /*! \fn char* GetNome()
            \brief Getter per il Nome.
            \param[out] char* nome
        */
        /*! \fn char* GetCognome()
            \brief Getter per il Cognome.
            \param[out] char* cognome
        */
        Persona(char*, char*, char*);
        ~Persona() {}
        void SetCredenziali(char*, char*, char*);
        void ViewListaPrestiti();
        void ViewListaPrestitiInCorso(char* username="none");
        void ViewListaPrestitiScaduti();
        void ViewListaUtenti();
        bool RicercaPrestito(int* vett=new int[1000]);
        bool RicercaUtente(int* vett=new int[1000]);
        void RegistrazioneUtente();
        void ModificaLibro();
        void ModificaUtente();
        void UpdateListaPrestiti(Utente*);
        void UpdateListaPrestiti(Libro*);
        void UpdateListaPrestitiInCorso(Utente*);
        void UpdateListaPrestitiInCorso(Libro*);
        time_t GetDataRegistrazione();
        void SetDataRegistrazione();
        char* GetPin();
        char* GetNome();
        char* GetCognome();
};


class Direttore : public Persona{
    public:
        /*! \fn Direttore(char*, char*, char*)
            \brief Costruttore Direttore.
        */
        /*! \fn Direttore()
            \brief Costruttore Direttore.
        */
        /*! \fn void ViewListaAddetti()
            \brief Visualizzatore della Lista Addetti.

        Mostra la lista degli Addetti indicandone: Nome, Cognome, Pin, Data Registrazione.
        */
        /*! \fn bool RicercaAddetto(int* vett=new int[1000])
            \brief Ricercatore dell'Addetto.
            \param[out] Conferma booleana presenza record in file.

        Richiede un testo in input, che varra' come parola chiave da ricercare in Nome, Cognome, Pin.\n
        Restituisce, come indirizzo, un int*[1000] contenente gli indici dei singoli Addetti trovati.
        */
        /*! \fn void RegistrazioneAddetto()
            \brief Registratore dell'Addetto.

        Richiede Nome e Cognome da tastiera e fornisce il relativo Pin generato automaticamente.
        */
        /*! \fn void ModificaPrestito()
            \brief Modificatore del Prestito.

        Richiamando la funzione RicercaPrestito() ne chiede la selezione del Prestito e, una volta selezionato,\n
        chiede al solo Direttore il numero di giorni da concedere al Prestito, da un minimo di 30 fino a -30.\n
        La modifica avviene in Lista Prestiti In Corso, solamente se il Prestito non è ancora scaduto.
        */
        /*! \fn void ModificaAddetto()
            \brief Modificatore dell'Addetto.

        Richiamando la funzione RicercaAddetto() ne chiede la selezione dell'Addetto e, una volta selezionato,\n
        elenca i parametri che si vogliono modificare, a scelta tra Nome, Cognome, Pin.\n
        La modifica avviene sia nella Lista Addetti, sia nella Lista Prestiti Scaduti, In Corso e Richiesti.
        */
        /*! \fn void EliminazioneLibro()
            \brief Eliminatore del Libro.

        Richiamando la funzione RicercaLibro() ne chiede la selezione del Libro e, una volta selezionato,\n
        provvede all'eliminazione, eseguita creando un file temporaneo che verra' poi rinominato.
        */
        /*! \fn void EliminazionePrestito()
            \brief Eliminatore del Prestito.

        Richiamando la funzione RicercaPrestito() ne chiede la selezione del Prestito e, una volta selezionato,\n
        provvede all'eliminazione, eseguita creando un file temporaneo che verra' poi rinominato.
        */
        /*! \fn void EliminazioneInListaPrestiti(char* username="", char* codiceLibro="")
            \brief Eliminatore del Prestito in Lista Prestiti Richiesti.

        Metodo richiamato unicamente dalla funzione EliminazionePrestito().
        */
        /*! \fn void EliminazioneInListaPrestitiInCorso(char* username="", char* codiceLibro="")
            \brief Eliminatore del Prestito in Lista Prestiti In Corso.

        Metodo richiamato unicamente dalla funzione EliminazionePrestito().
        */
        /*! \fn void EliminazioneUtente()
            \brief Eliminatore dell'Utente.

        Richiamando la funzione RicercaUtente() ne chiede la selezione dell'Utente e, una volta selezionato,\n
        provvede all'eliminazione, eseguita creando un file temporaneo che verra' poi rinominato.
        */
        /*! \fn void EliminazioneAddetto()
            \brief Eliminatore dell'Addetto.

        Richiamando la funzione RicercaAddetto() ne chiede la selezione dell'Addetto e, una volta selezionato,\n
        provvede all'eliminazione, eseguita creando un file temporaneo che verra' poi rinominato.
        */
        Direttore(char*, char*, char*);
        Direttore() : Persona("", "", "") {}
        void ViewListaAddetti();
        bool RicercaAddetto(int* vett=new int[1000]);
        void RegistrazioneAddetto();
        void ModificaPrestito();
        void ModificaAddetto();
        void EliminazioneLibro();
        void EliminazionePrestito();
        void EliminazioneInListaPrestiti(char* username="", char* codiceLibro="");
        void EliminazioneInListaPrestitiInCorso(char* username="", char* codiceLibro="");
        void EliminazioneUtente();
        void EliminazioneAddetto();
};


class Addetto : public Persona{
    public:
        /*! \fn Addetto(char*, char*, char*)
            \brief Costruttore Addetto.
        */
        /*! \fn Addetto()
            \brief Costruttore Addetto.
        */
        Addetto(char*, char*, char*);
        Addetto() : Persona("", "", "") {}
};


class Utente : public Persona{
    char username[21];
    public:
        /*! \fn Utente(char*, char*, char*, char*)
            \brief Costruttore Utente.
        */
        /*! \fn Utente()
            \brief Costruttore Utente.
        */
        /*! \fn RichiestaPrestito(Utente*)
            \brief Richiesta Prestito da parte dell'Utente.

        Richiamando la funzione RicercaLibro() ne chiede la selezione del Libro e, una volta selezionato,\n
        provvede ad inserire in Lista Prestiti Richiesti il Prestito appena generato.
        */
        /*! \fn void SetUserCredenziali(char*, char*, char*, char*)
            \brief Setter delle credenziali dell'Utente.

        Funge da metodo setter per i 4 parametri: Nome, Cognome, Pin, Username.
        */
        /*! \fn char* GetUsername()
            \brief Getter per l'Username.
            \param[out] char* username
        */
        Utente(char*, char*, char*, char*);
        Utente();
        void RichiestaPrestito(Utente*);
        void SetUserCredenziali(char*, char*, char*, char*);
        char* GetUsername();
};


class Libro{
    char titolo[51], autore[21], anno[5], codice[4];
    char disponibilita[20];//DISPONIBILE //NON DISPONIBILE //IN PRESTITO //IN RESO //PRENOTATO
    public:
        /*! \fn Libro(char*, char*, char*, char*, bool cod=true)
            \brief Costruttore Libro.

        Richiede 4 parametri in entrata: Titolo, Autore, Anno, Disponibilita.\n
        In più se richiamato con valore booleano settato true (essendo parametro di default), provvede a generare\n
        un nuovo Codice, calcolato mediante l'incremento di un contatore stampato su file binario, riscrivendolo aggiornato.
        */
        /*! \fn Libro()
            \brief Costruttore Libro.
        */
        /*! \fn ~Libro()
            \brief Distruttore Libro.
        */
        /*! \fn void SetInformazioni(char*, char*, char*, char*, char*)
            \brief Setter delle credenziali.

        Funge da metodo setter per i 5 parametri: Titolo, Autore, Anno, Codice, Disponibilita'.
        */
        /*! \fn void Write(Libro*)
            \brief Writer per il nuovo Libro

        Tramite il puntatore a Libro ricevuto come parametro, provvede a stampare le informazioni in Catalogo.
        */
        /*! \fn char* GetTitolo()
            \brief Getter per il Titolo.
            \param[out] char* titolo
        */
        /*! \fn char* GetAutore()
            \brief Getter per l'Autore.
            \param[out] char* autore
        */
        /*! \fn char* GetAnno()
            \brief Getter per l'Anno.
            \param[out] char* anno
        */
        /*! \fn char* GetCodice()
            \brief Getter per il Codice.
            \param[out] char* codice
        */
        /*! \fn void SetCodice(char*)
            \brief Setter per il Codice.
        */
        /*! \fn char* GetDisponibilita()
            \brief Getter per la Disponibilita.
            \param[out] char* disponibilita
        */
        /*! \fn void SetDisponibilita(char*)
            \brief Setter per la Disponibilita.
        */
        Libro(char*, char*, char*, char*, bool cod=true);
        Libro() : Libro("", "", "", "") {}
        ~Libro() {}
        void SetInformazioni(char*, char*, char*, char*, char*);
        void Write(Libro*);
        char* GetTitolo();
        char* GetAutore();
        char* GetAnno();
        char* GetCodice();
        void SetCodice(char*);
        char* GetDisponibilita();
        void SetDisponibilita(char*);
};


class Catalogo{
    Libro l;
    public:
        /*! \fn Catalogo()
            \brief Costruttore Catalogo.

        Provvede ad inserire in Lista Prestiti Scaduti tutti quei Prestiti con Data di Scadenza <= 0.
        */
        /*! \fn ~Catalogo()
            \brief Distruttore Catalogo.
        */
        /*! \fn bool VisualizzaCatalogo()
            \brief Visualizzatore del Catalogo.

        Mostra la lista dei Libri indicandone: Titolo, Autore, Anno, Codice, Disponibilita'.
        */
        /*! \fn void UpdateCatalogo(Libro*)
            \brief Metodo per la modifica di Libri in Catalogo.
        */
        /*! \fn bool RicercaLibro(int* vett=new int[1000])
            \brief Ricercatore del Libro.
            \param[out] Conferma booleana presenza record in file.

        Richiede un testo in input, che varra' come parola chiave da ricercare in Titolo, Autore, Anno, Codice.\n
        Restituisce, come indirizzo, un int*[1000] contenente gli indici dei singoli Libri trovati.
        */
        Catalogo();
        ~Catalogo() {}
        void VisualizzaCatalogo();
        void UpdateCatalogo(Libro*);
        bool RicercaLibro(int* vett=new int[1000]);
};


class Pin{
    char pin[5];
    public:
        /*! \fn ~Pin()
            \brief Distruttore Pin.
        */
        /*! \fn char* GetPin()
            \brief Getter per il nuovo Pin generato.
            \param[out] char* pin

        Restutuisce un pin generato pseudocausalmente covertito in char*, compreso tra 999 e 2000, estremi esclusi.
        */
        ~Pin();
        char* GetPin();
};


class Registrazione{
    char nome[21], cognome[21], pin[5], username[21];
    bool isRegistrato;
    Pin p;
    public:
        /*! \fn Registrazione()
            \brief Costruttore Registrazione.
        */
        /*! \fn ~Registrazione()
            \brief Distruttore Registrazione.
        */
        /*! \fn void NewRegistrazione(char)
            \brief Setter nuova Registrazione.

        Come parametro di ingresso è richiesto un char ('u':modalita' Utente, 'a':Addetto, 'd':Direttore).\n
        Richiede Nome, Cognome e (se Utente) Username da tastiera e fornisce il relativo Pin generato automaticamente.\n
        Le credenziali sono salvate in Credenziali Utenti/Addetti/Direttore.
        */
        /*! \fn char* GetNome()
            \brief Getter per il Nome.
            \param[out] char* nome
        */
        /*! \fn char* GetCognome()
            \brief Getter per il Cognome.
            \param[out] char* cognome
        */
        /*! \fn char* GetPin()
            \brief Getter per il Pin.
            \param[out] char* pin
        */
        /*! \fn char* GetUsername()
            \brief Getter per l'Username.
            \param[out] char* username
        */
        /*! \fn bool GetIsRegistrato()
            \brief Getter per la conferma di Registrazione.
            \param[out] bool isRegistrato
        */
        Registrazione();
        ~Registrazione() {}
        void NewRegistrazione(char);
        char* GetNome();
        char* GetCognome();
        char* GetPin();
        char* GetUsername();
        bool GetIsRegistrato();
};


class Login{
    char nome[21], cognome[21], pin[5], username[21];
    bool isLoggato;
    public:
        /*! \fn Login()
            \brief Costruttore Login.
        */
        /*! \fn ~Login()
            \brief Distruttore Login.
        */
        /*! \fn void NewLogin(char)
            \brief Setter nuovo Login.

        Come parametro di ingresso è richiesto un char ('u':modalita' Utente, 'a':Addetto, 'd':Direttore).\n
        Se Utente, richiede Username e Pin; se Addetto/Direttore, richiede solamente il Pin.
        */
        /*! \fn char* GetNome()
            \brief Getter per il Nome.
            \param[out] char* nome
        */
        /*! \fn char* GetCognome()
            \brief Getter per il Cognome.
            \param[out] char* cognome
        */
        /*! \fn char* GetPin()
            \brief Getter per il Pin.
            \param[out] char* pin
        */
        /*! \fn char* GetUsername()
            \brief Getter per l'Username.
            \param[out] char* username
        */
        /*! \fn bool GetIsLoggato()
            \brief Getter per la conferma di Login.
            \param[out] bool isLoggato
        */
        Login();
        ~Login() {}
        void NewLogin(char);
        char* GetNome();
        char* GetCognome();
        char* GetPin();
        char* GetUsername();
        bool GetIsLoggato();
};


class Data{
    time_t dataOra;
    public:
        /*! \fn Data()
            \brief Costruttore Data.
        */
        /*! \fn ~Data()
            \brief Distruttore Data.
        */
        /*! \fn void SetCurrentDataOra()
            \brief Setter Data e Ora correnti.

        Mediante la funzione time() viene settato un valore time_t che contiene Data e Ora correnti.
        */
        /*! \fn time_t GetDataOra()
            \brief Getter Data e Ora.
            \param[out] time_t dataOra

        Restituisce Data e Ora settati mediante la funzione SetCurrentDataOra().
        */
        /*! \fn time_t GetDataOra30Days(time_t)
            \brief Getter Data e Ora sommati di 30 giorni.
            \param[out] Data e Ora + 30 giorni

        Restituisce Data e Ora sommati di 30 giorni al parametro time_t in ingresso.
        */
        /*! \fn time_t GetDataOraEstesa(time_t, int)
            \brief Getter Data e Ora estesi.
            \param[out] Data e Ora + giorni di estensione

        Restituisce Data e Ora sommati di [parametro int in ingresso] giorni al parametro time_t in ingresso.
        */
        Data();
        ~Data() {}
        void SetCurrentDataOra();
        time_t GetDataOra();
        time_t GetDataOra30Days(time_t);
        time_t GetDataOraEstesa(time_t, int);
};


class Prestito{
    char codiceLibro[4];
    time_t dataAccettazione, dataScadenza;
    public:
        /*! \fn Prestito()
            \brief Costruttore Prestito.
        */
        /*! \fn ~Prestito()
            \brief Distruttore Prestito.
        */
        /*! \fn void SetData()
            \brief Setter Data Accettazione e Data Scadenza Prestito.
        */
        /*! \fn int GetDifferenza()
            \brief Getter differenza tra Data Scadenza e Data Corrente.
            \param[out] Differenza in giorni
        */
        /*! \fn char* GetCodice()
            \brief Getter Codice del Libro.
            \param[out] char* codiceLibro
        */
        /*! \fn void SetCodice(char*)
            \brief Setter Codice del Libro.
        */
        /*! \fn time_t GetDataAccettazione()
            \brief Getter Data di Accettazione Prestito.
            \param[out] time_t dataAccettazione
        */
        /*! \fn time_t GetDataScadenza()
            \brief Getter Data di Scadenza Prestito.
            \param[out] time_t dataScadenza
        */
        /*! \fn void SetDataScadenza(time_t)
            \brief Setter Data di Scadenza Prestito.
        */
        Prestito();
        ~Prestito() {}
        void SetData();
        int GetDifferenza();
        char* GetCodice();
        void SetCodice(char*);
        time_t GetDataAccettazione();
        time_t GetDataScadenza();
        void SetDataScadenza(time_t);
};

#endif // CLASSI_H_INCLUDED
