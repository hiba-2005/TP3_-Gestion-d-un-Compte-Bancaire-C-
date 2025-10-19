#include <iostream>
#include <string>
using namespace std;

class CompteBancaire {
private:
    string titulaire;
    double solde;

public:
    // 🔹 Constructeur par défaut
    CompteBancaire() {
        titulaire = "Inconnu";
        solde = 0.0;
        cout << "[Constructeur par defaut] Compte cree pour " << titulaire << endl;
    }

    // 🔹 Constructeur paramétré
    CompteBancaire(const string& nom, double montant) {
        titulaire = nom;
        solde = montant;
        cout << "[Constructeur parametre] Compte cree pour " << titulaire << " avec un solde de " << solde << " DH" << endl;
    }

    // 🔹 Constructeur de copie
    CompteBancaire(const CompteBancaire& autre) {
        titulaire = autre.titulaire;
        solde = autre.solde;
        cout << "[Constructeur de copie] Compte copie depuis " << autre.titulaire << endl;
    }


    void afficher() const {
        cout << "Titulaire : " << titulaire << " | Solde : " << solde << " DH" << endl;
    }

    //  Destructeur
    ~CompteBancaire() {
        cout << "[Destructeur] Compte de " << titulaire << " supprime." << endl;
    }
};

int main() {
    cout << "=== Début du programme ===" << endl;

    CompteBancaire compte1;                         // constructeur par défaut
    CompteBancaire compte2("Alice", 1500.0);        // constructeur paramétré
    CompteBancaire compte3 = compte2;               // constructeur de copie

    cout << "\n--- Affichage des comptes ---" << endl;
    compte1.afficher();
    compte2.afficher();
    compte3.afficher();

    cout << "=== Fin du programme ===" << endl;
    return 0;
}
