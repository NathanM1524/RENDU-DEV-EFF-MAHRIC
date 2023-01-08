#include <iostream>
#include <string>
#include <sstream>
#include <array>

using namespace std;

struct Pile {
    int top;
    static const long taillePile = 100;
    array<double, taillePile> data;
};

void push(Pile& pile, double value) {
    if (pile.top < pile.taillePile - 1) {
        pile.top++;
        pile.data[pile.top] = value;
    }
}

double pop(Pile& pile) {
    if (pile.top >= 0) {
        return pile.data[pile.top--];
    }
    return 0;
}

double peek(const Pile& pile) {
    if (pile.top >= 0) {
        return pile.data[pile.top];
    }
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

double calcul(char operation, double operande1, double operande2) {
    switch (operation) {
    case '+':
        return operande1 + operande2;
    case '-':
        return operande1 - operande2;
    case '*':
        return operande1 * operande2;
    case '/':
        return operande1 / operande2;
    default:
        return 0;
    }
}

stringstream initialise()
{
    string entree;
    cout << "Entrez un calcul sous forme de notation polonaise : ";
    getline(std::cin, entree);
    stringstream entreeUtilisateur(entree);
    return entreeUtilisateur;
}

void affichage(Pile pile)
{
    if (pile.top == 0) {
        cout << "Resultat : " << peek(pile) << endl;
    }
    else {
        if (pile.top > 0) {
            cout << "Error: trop d'operandes" << endl;
        }
        else {
            cout << "Erreur: pas asser d'operandes" << endl;
        }
    }
}

Pile ifIsOperateur(Pile pile,string valeure)
{
    if (pile.top < 1) {
        cout << "Erreur: pas asser d'operandes pour l'operateur : " << valeure[0] << endl;
        exit(1);
    }
    double operande2 = pop(pile);
    double operande1 = pop(pile);
    double resultat = calcul(valeure[0], operande1, operande2);
    push(pile, resultat);
    cout << operande1 << " " << valeure[0] << " " << operande2 << " = " << resultat << endl;
    return pile;
}

Pile ifIsOperande(Pile pile, string valeure) {
    double operande;
    try {
        operande = stod(valeure);
    }
    catch (const invalid_argument& e) {
        cout << "Entree invalide " << valeure << endl;
        exit(1);
    }
    push(pile, operande);
    return pile;
}

int main() {
    string valeure;
    Pile pile;
    pile.top = -1;
    stringstream entreeUtilisateur = initialise();
    while (entreeUtilisateur >> valeure) {
        if (isOperator(valeure[0])) {
            pile = ifIsOperateur(pile, valeure);
        }
        else {
            pile = ifIsOperande(pile, valeure);
        }
    }
    affichage(pile);
}
