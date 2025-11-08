#include <iostream>
#include <string>
using namespace std;

// Classe de base : Ressource
class Ressource {
protected:
    int id;
    string titre;
    string auteur;
    int annee;

public:
    Ressource(int _id, string _titre, string _auteur, int _annee) {
        id = _id;
        titre = _titre;
        auteur = _auteur;
        annee = _annee;
    }

    virtual void afficherInfos() {
        cout << "ID : " << id << endl;
        cout << "Titre : " << titre << endl;
        cout << "Auteur : " << auteur << endl;
        cout << "Annee : " << annee << endl;
    }

    virtual void telecharger() {
        cout << "Telechargement de la ressource..." << endl;
    }

    int getId() {
        return id;
    }

    string getTitre() {
        return titre;
    }

    string getAuteur() {
        return auteur;
    }

    int getAnnee() {
        return annee;
    }

    bool operator==(Ressource &r) {
        return id == r.id;
    }
};

// Classe Telechargeable
class Telechargeable {
public:
    virtual void telecharger() {
        cout << "Telechargement depuis Telechargeable..." << endl;
    }

    void afficherMessage() {
        cout << "Cette ressource peut etre telechargee." << endl;
    }
};

// Classe Livre
class Livre : public Ressource, public Telechargeable {
private:
    int nbPages;

public:
    Livre(int _id, string _titre, string _auteur, int _annee, int _nbPages)
        : Ressource(_id, _titre, _auteur, _annee) {
        nbPages = _nbPages;
    }

    void afficherInfos() {
        cout << "=== Livre ===" << endl;
        Ressource::afficherInfos();
        cout << "Nombre de pages : " << nbPages << endl;
    }

    void telecharger() {
        cout << "Telechargement du livre \"" << titre << "\" en PDF..." << endl;
    }
};

// Classe Magazine
class Magazine : public Ressource, public Telechargeable {
private:
    int numero;

public:
    Magazine(int _id, string _titre, string _auteur, int _annee, int _numero)
        : Ressource(_id, _titre, _auteur, _annee) {
        numero = _numero;
    }

    void afficherInfos() {
        cout << "=== Magazine ===" << endl;
        Ressource::afficherInfos();
        cout << "Numero : " << numero << endl;
    }

    void telecharger() {
        cout << "Telechargement du magazine \"" << titre << "\" (numero "
             << numero << ") en PDF..." << endl;
    }
};

// Classe Video
class Video : public Ressource, public Telechargeable {
private:
    float duree;

public:
    Video(int _id, string _titre, string _auteur, int _annee, float _duree)
        : Ressource(_id, _titre, _auteur, _annee) {
        duree = _duree;
    }

    void afficherInfos() {
        cout << "=== Video ===" << endl;
        Ressource::afficherInfos();
        cout << "Duree : " << duree << " minutes" << endl;
    }

    void telecharger() {
        cout << "Telechargement de la video \"" << titre << "\" en MP4..." << endl;
    }
};

// Classe Mediatheque (tableau simple)
class Mediatheque {
private:
    Ressource* ressources[10];
    int nbRessources;

public:
    Mediatheque() {
        nbRessources = 0;
    }

    void ajouter(Ressource* r) {
        if (nbRessources < 10) {
            ressources[nbRessources] = r;
            nbRessources++;
        } else {
            cout << "La mediatheque est pleine !" << endl;
        }
    }

    void afficher() {
        for (int i = 0; i < nbRessources; i++) {
            ressources[i]->afficherInfos();
            cout << "------------------------" << endl;
        }
    }

    void rechercher(string titre) {
        cout << "Recherche par titre : " << titre << endl;
        for (int i = 0; i < nbRessources; i++) {
            if (ressources[i]->getTitre() == titre) {
                ressources[i]->afficherInfos();
            }
        }
    }

    void rechercher(int annee) {
        cout << "Recherche par annee : " << annee << endl;
        for (int i = 0; i < nbRessources; i++) {
            if (ressources[i]->getAnnee() == annee) {
                ressources[i]->afficherInfos();
            }
        }
    }

    void rechercher(string auteur, int annee) {
        cout << "Recherche par auteur et annee : " << auteur << ", " << annee << endl;
        for (int i = 0; i < nbRessources; i++) {
            if (ressources[i]->getAuteur() == auteur && ressources[i]->getAnnee() == annee) {
                ressources[i]->afficherInfos();
            }
        }
    }
};

// Fonction principale
int main() {
    Mediatheque m;

    Livre* l1 = new Livre(1, "Le Petit Prince", "Saint-Exupery", 1943, 120);
    Magazine* m1 = new Magazine(2, "Science et Vie", "Collectif", 2023, 487);
    Video* v1 = new Video(3, "Documentaire Nature", "BBC", 2020, 90.5);

    m.ajouter(l1);
    m.ajouter(m1);
    m.ajouter(v1);

    cout << "\n=== Contenu de la mediatheque ===" << endl;
    m.afficher();

    cout << "\n=== Test de recherche ===" << endl;
    m.rechercher("Le Petit Prince");
    m.rechercher(2020);
    m.rechercher("BBC", 2020);

    cout << "\n=== Test de telechargement ===" << endl;
    l1->telecharger();
    m1->telecharger();
    v1->telecharger();

    cout << "\n=== Test de heritage multiple ===" << endl;
    l1->Telechargeable::afficherMessage();

    cout << "\n=== Test de comparaison ===" << endl;
    Livre l2(1, "Autre Livre", "Auteur X", 2000, 200);
    if (*l1 == l2)
        cout << "Les deux ressources ont le meme ID." << endl;
    else
        cout << "Les deux ressources sont differentes." << endl;

    return 0;
}
