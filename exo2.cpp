#include <iostream>
#include <string>
using namespace std;

// Classe Client
class Client {
private:
    string nom;
    string CIN;
    int idClient;

public:
    Client() {} // constructeur par défaut

    void saisirClient() {
        cout << "Entrer le nom du client : ";
        cin >> nom;
        cout << "Entrer le CIN du client : ";
        cin >> CIN;
        cout << "Entrer l'identifiant du client : ";
        cin >> idClient;
    }

    void afficherClient() {
        cout << "Nom : " << nom << endl;
        cout << "CIN : " << CIN << endl;
        cout << "Identifiant : " << idClient << endl;
    }

    friend class CompteBancaire; // donne accès aux infos au compte
    friend class Banque;         // donne accès pour audit
};

// Classe CompteBancaire
class CompteBancaire {
private:
    int numeroCompte;
    float solde;
    int codeSecret;
    Client proprietaire;

public:
    CompteBancaire() {
        numeroCompte = 0;
        solde = 0;
        codeSecret = 0;
    }

    void creerCompte(Client c, int num, float s, int code) {
        proprietaire = c;
        numeroCompte = num;
        solde = s;
        codeSecret = code;
    }

    void deposer(float montant) {
        solde += montant;
        cout << "Depot de " << montant << " DH effectué avec succès." << endl;
    }

    void retirer(float montant) {
        if (montant <= solde) {
            solde -= montant;
            cout << "Retrait de " << montant << " DH effectué." << endl;
        } else {
            cout << "Solde insuffisant !" << endl;
        }
    }

    void afficherCompte() {
        cout << "Numéro de compte : " << numeroCompte << endl;
        cout << "Solde : " << solde << " DH" << endl;
    }

    friend class AgentBancaire; // accès autorisé
    friend class Banque;        // accès autorisé
};

// Classe AgentBancaire
class AgentBancaire {
private:
    string nomAgent;
    int idAgent;

public:
    void saisirAgent() {
        cout << "Entrer le nom de l'agent : ";
        cin >> nomAgent;
        cout << "Entrer l'identifiant de l'agent : ";
        cin >> idAgent;
    }

    void afficherAgent() {
        cout << "Agent : " << nomAgent << " (ID : " << idAgent << ")" << endl;
    }

    void consulterCodeSecret(CompteBancaire &c) {
        cout << "Code secret du compte " << c.numeroCompte << " : " << c.codeSecret << endl;
    }

    void transferer(CompteBancaire &source, CompteBancaire &destination, float montant) {
        if (montant <= source.solde) {
            source.solde -= montant;
            destination.solde += montant;
            cout << "Transfert de " << montant << " DH effectué avec succès." << endl;
        } else {
            cout << "Transfert échoué : solde insuffisant !" << endl;
        }
    }
};

// Classe Banque
class Banque {
private:
    string nomBanque;
    CompteBancaire comptes[5];
    int nbComptes;

public:
    Banque() {
        nomBanque = "MaBanque";
        nbComptes = 0;
    }

    void ajouterCompte(CompteBancaire c) {
        if (nbComptes < 5) {
            comptes[nbComptes] = c;
            nbComptes++;
        } else {
            cout << "Limite de comptes atteinte !" << endl;
        }
    }

    void afficherAudit() {
        cout << "===== AUDIT INTERNE BANQUE " << nomBanque << " =====" << endl;
        for (int i = 0; i < nbComptes; i++) {
            cout << "Compte " << i + 1 << " :" << endl;
            cout << "Numéro : " << comptes[i].numeroCompte << endl;
            cout << "Solde : " << comptes[i].solde << " DH" << endl;
            cout << "Code secret : " << comptes[i].codeSecret << endl;
            cout << "Propriétaire : " << comptes[i].proprietaire.nom << " (CIN : " << comptes[i].proprietaire.CIN << ")" << endl;
            cout << "--------------------------------------" << endl;
        }
    }
};

// Fonction principale
int main() {
    Client c1, c2;
    cout << "=== Création des clients ===" << endl;
    c1.saisirClient();
    c2.saisirClient();

    CompteBancaire compte1, compte2;
    compte1.creerCompte(c1, 1001, 5000, 1234);
    compte2.creerCompte(c2, 1002, 2000, 4321);

    Banque banque;
    banque.ajouterCompte(compte1);
    banque.ajouterCompte(compte2);

    AgentBancaire agent;
    cout << "\n=== Saisie de l'agent bancaire ===" << endl;
    agent.saisirAgent();
    agent.afficherAgent();

    cout << "\n=== Opérations ===" << endl;
    compte1.deposer(1000);
    compte2.retirer(500);
    agent.transferer(compte1, compte2, 1500);

    cout << "\n=== Audit interne (réservé à la banque) ===" << endl;
    banque.afficherAudit();

    cout << "\n=== Consultation du code secret par l'agent autorisé ===" << endl;
    agent.consulterCodeSecret(compte1);

    return 0;
}
