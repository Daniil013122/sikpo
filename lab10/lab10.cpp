#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Participant {
    int number;
    string name;
    string start;
    string finish;
    string club;
};

int convertTime(const string& time) {
    int hours, minutes, seconds;
    stringstream ss(time);
    ss >> hours >> noskipws >> minutes >> noskipws >> seconds;
    return hours * 60 * 60 + minutes * 60 + seconds;
}

int main() {
    setlocale(LC_ALL, "Russian");

    ifstream inputFile("data.txt");
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл data.txt" << endl;
        return 1;
    }

    // вектор для хранения данных
    vector<Participant> participants;

    string line;
    while (getline(inputFile, line)) {
        // проходим строку и заполняем структуру Participations
        stringstream ss(line);
        Participant participant;
        ss >> participant.number >> participant.name >> participant.start >> participant.finish >> participant.club;

        // добавляем структуру в вектор
        participants.push_back(participant);
    }
    inputFile.close();

    cout << "Участники из клуба Спартак: " << endl;
    for (const Participant& participant : participants) {
        if (participant.club == "Spartacus") {
            cout << participant.number << " " << participant.name << " " << participant.start << " " << participant.finish << " " << participant.club << endl;
        }
    }


    cout << "\nУчастники с результатом лучше 2:50:00" << endl;
    for (const Participant& participant : participants) {
        // Преобразовать время в секунды
        int startSeconds = convertTime(participant.start);
        int finishSeconds = convertTime(participant.finish);

        // Сравнить время финиша с целевым временем
        if (finishSeconds < 2 * 60 * 60 + 50 * 60) {
            cout << participant.number << " " << participant.name << " " << participant.start << " " << participant.finish << " " << participant.club << endl;
        }
    }

    return 0;
}