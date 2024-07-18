#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <termios.h>
using namespace std;

int STDIN_FILENO = 0;

vector<vector<int>> historicBinaryResults;

vector<int> InverterBinarios(vector<int> Binaries) {
    reverse(Binaries.begin(), Binaries.end());
    return Binaries;
}

vector<int> BinaryResult(int Binary) {
    vector<int> Binaries;
    int conta = 0;

    while (Binary >= 2) {
        Binaries.push_back(Binary % 2);
        Binary = Binary / 2;
    }

    Binaries.push_back(Binary);

    for (int i = 0; i < Binaries.size(); i++) {
        if (Binaries[i] == 1) {
            conta = conta + 1;
        }
    }

    if (conta % 2 == 0) {
        Binaries.push_back(0);
    } else {
        Binaries.push_back(1);
    }

    Binaries = InverterBinarios(Binaries);
    return Binaries;
}

void HistoricBinary(vector<int> Binary) {
    historicBinaryResults.push_back(Binary);
}

bool Regras(vector<int> Binary) {
    if (Binary[0] == 1 && Binary[4] == 1) {
        return true;
    } else {
        return false;
    }
}

int main() {
    vector<vector<int>> historicBinaryResults;
    bool exit = true;
    char inputChar;
    int contador = 0;
    int repetindoCodigo = 0;


    // Obtém as configurações atuais do terminal
    struct termios tty_settings;
    tcgetattr(STDIN_FILENO, &tty_settings);

    // Desabilita o bit ICANON
    tty_settings.c_lflag &= ~ICANON;

    // Aplica as novas configurações do terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_settings);

    // Lê um caractere sem pressionar Enter
    char input_char = getchar();

    // Imprime o caractere
    std::cout << input_char << std::endl;

    // Restaura as configurações originais do terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_settings);


    while (exit == true) {
        repetindoCodigo++;

        cout << "Digite uma letra ou numero: ";
        cin >> inputChar;
        int Inter = inputChar;

     
        cout << "Valor escolhido: " << inputChar << endl;

        vector<int> binaryResult = BinaryResult(Inter);
        HistoricBinary(binaryResult);

        if (Regras(binaryResult) == true) {
            contador++;
        }
        cout << "--------------------------------------------------------------" << endl;
        cout << "Digite outra letra para continuar" << endl;

        if (repetindoCodigo == 8 && contador == 8) {
            cout << "Parabéns Você acertou  :) " << endl;
            exit = false;
        }

        if (repetindoCodigo >= 9) {
            cout << "Para sair digite S" << endl;
            cout << "Para COMEÇAR DO 0 digite X" << endl;
        }

        cin >> inputChar;
        if (inputChar == 'X') {
            historicBinaryResults.clear();
            exit = true;
        }

        cin >> inputChar;
        if (inputChar == 'S') {
            historicBinaryResults.clear();
            exit = false;
        }
    }

    cout << "Historic Binary Results: ";
    for (int i = 0; i < historicBinaryResults.size(); i++) {
        cout << "[";
        for (int j = 0; j < historicBinaryResults[i].size(); j++) {
            cout << historicBinaryResults[i][j];
            if (j != historicBinaryResults[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << "]";
        if (i != historicBinaryResults.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    return 0;
}
