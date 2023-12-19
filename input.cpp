#include "input.h"
#include <string>
#include <iostream>
#include <fstream>
#include "coord.h"
#include "pigeon.h"

using namespace std;

Vec3Cord InputController::parsePos(string Mystr) { // работает
    Mystr = Mystr + ' ';
    string coord = Mystr.substr(0, Mystr.find(' '));
    Vec3Cord cordtoOut;
    try {
        cordtoOut.x = stof(coord);
    } catch (std::exception const &e) {
        cout << "error : " << e.what() << endl;
        exit(-1);
    }


    Mystr = Mystr.substr(Mystr.find(' ') + 1, string::npos);
    coord = Mystr.substr(0, Mystr.find(' '));

    try {
        cordtoOut.y = stof(coord);
    } catch (std::exception const &e) {
        cout << "error : " << e.what() << endl;
        exit(-1);
    }
    // проверить что может не быть координаты
    Mystr = Mystr.substr(Mystr.find(' ') + 1, string::npos);
    if (Mystr == "") {
        cordtoOut.z = 0;
    } else {
        coord = Mystr.substr(0, Mystr.find(' '));
        try {
            cordtoOut.z = stof(coord);
        } catch (std::exception const &e) {
            cout << "error : " << e.what() << endl;
            exit(-1);
        }
    }
    return cordtoOut;
}


Vec4Cord InputController::parse4Pos(string Mystr) { // работает
    Mystr = Mystr + ' ';
    string coord = Mystr.substr(0, Mystr.find(' '));
    Vec4Cord cordtoOut;
    try {
        cordtoOut.x = stof(coord);
    } catch (std::exception const &e) {
        cout << "error : " << e.what() << endl;
        exit(-1);
    }


    Mystr = Mystr.substr(Mystr.find(' ') + 1, string::npos);
    coord = Mystr.substr(0, Mystr.find(' '));

    try {
        cordtoOut.y = stof(coord);
    } catch (std::exception const &e) {
        cout << "error : " << e.what() << endl;
        exit(-1);
    }
    // проверить что может не быть координаты

    Mystr = Mystr.substr(Mystr.find(' ') + 1, string::npos);
    coord = Mystr.substr(0, Mystr.find(' '));

    try {
        cordtoOut.z = stof(coord);
    } catch (std::exception const &e) {
        cout << "error : " << e.what() << endl;
        exit(-1);
    }


    Mystr = Mystr.substr(Mystr.find(' ') + 1, string::npos);
    coord = Mystr.substr(0, Mystr.find(' '));

    try {
        cordtoOut.r = stof(coord);
    } catch (std::exception const &e) {
        cout << "error : " << e.what() << endl;
        exit(-1);
    }

    return cordtoOut;
}



void InputController::parseFood(string Mystr) {
    string poss = Mystr.substr(Mystr.find('(') + 1, Mystr.find(')') - Mystr.find('(') - 1);
    Vec3Cord cords = parsePos(poss);
    dat.AddFoodStart(cords); //TODO: добавить еду
}

void InputController::parseField(string Mystr) {
    //MarginStruct
    string poss = Mystr.substr(Mystr.find('(') + 1, Mystr.find(')') - Mystr.find('(') - 1);
    poss = poss + ' ';
    string ftwo = poss.substr(0, poss.find(' '));
    poss = poss.substr(poss.find(' ') + 1, string::npos);
    ftwo = ftwo + ' ' + poss.substr(0, poss.find(' '));
    poss = poss.substr(poss.find(' ') + 1, string::npos);
    Vec3Cord UpDown = parsePos(ftwo);
    ftwo = poss.substr(0, poss.find(' '));
    poss = poss.substr(poss.find(' ') + 1, string::npos);
    ftwo = ftwo + ' ' + poss.substr(0, poss.find(' '));
    poss = poss.substr(poss.find(' ') + 1, string::npos);
    Vec3Cord RightLeft = parsePos(ftwo);
//    cout << UpDown.x << UpDown.y << RightLeft.x << RightLeft.y << "adawda" << endl;
  //  cerr<< poss<< endl;
    if(!poss.empty()){
        cerr<< "Error field description" << endl;
        exit(-1);
    }
    Pigeon::Margin = MarginStruct(UpDown.x, UpDown.y, RightLeft.x, RightLeft.y);
};

void InputController::parseCar(std::string Mystr) {
    Vec3Cord cords;
    string poss;
    while ((poss = Mystr.substr(Mystr.find('(') + 1, Mystr.find(')') - Mystr.find('(') - 1)) != "") {
       // cerr << poss << endl;
        cords = parsePos(poss);
      //  cerr << cords.x << " " << cords.y << " "<< cords.z << " car cord" << endl;
        if (cords.z != 0) {
            cerr << "Car with z Coord" << endl;
            exit(-1);
        }
        dat.setCarPoint(cords);
        Mystr = Mystr.substr(Mystr.find(')') + 1, string::npos);
    }

}

void InputController::parseBird(std::string Mystr) { // работает
    string poss = Mystr.substr(Mystr.find('(') + 1, Mystr.find(')') - Mystr.find('(') - 1);
    Vec3Cord cords = parsePos(poss);
    dat.setPigStartPos(cords);
}


void InputController::parseObst(std::string  Mystr){
    string poss = Mystr.substr(Mystr.find('(') + 1, Mystr.find(')') - Mystr.find('(') - 1);

    Vec4Cord cords = parse4Pos(poss);
    dat.setObstStartPos(cords);
}


void InputController::parseComas(string Mystr) {
    cout << "HERE" << endl;
    cout << Mystr << endl;
    size_t found = Mystr.find("name:");
    Mystr = Mystr.substr(found + 5, string::npos);
    found = Mystr.find("\"");
    Mystr = Mystr.substr(found + 1, string::npos);
    found = Mystr.find("\"");
    string name = Mystr.substr(0, found);
    Mystr = Mystr.substr(found + 1, string::npos); // без имени
    if (name == "Food") {
        parseFood(Mystr);
    } else if (name == "Bird") {
        parseBird(Mystr);
    } else if (name == "Car") {
        parseCar(Mystr);
    } else if (name == "Field") {
        parseField(Mystr);
    } else if(name =="Obstacle"){
      parseObst(Mystr);
    } else {
        cerr << "Not Found Name" << endl;
        exit(-1);
    }
    return;
}

int InputController::ReadInputFile(string filename) {
    ifstream inpfile;
    inpfile.open(filename);
    string line, subst;

    if (!inpfile.is_open()) {
        cout << "Error: Bird file wasn't opened." << endl;
        exit(-1);
    }

    int openComaPos = 0;
    int closeComaPos = 0;
    while (getline(inpfile, line)) {
        if (line.find('{') != string::npos) {
            subst = line;
            openComaPos = line.find('{');
            if (line.find('}') != string::npos) {
                closeComaPos = subst.find('}');
                subst = subst.substr(openComaPos + 1, closeComaPos - openComaPos - 1); // убираю фигурные скобки
                parseComas(subst);
                openComaPos = 0;
                closeComaPos = 0;
                continue;
            }
            continue;
        }
        if (line.find('}') != string::npos) {
            subst = subst + line;
            closeComaPos = subst.find('}');
            subst = subst.substr(openComaPos + 1, closeComaPos - openComaPos - 1); // убираю фигурные скобки
            parseComas(subst);
            openComaPos = 0;
            closeComaPos = 0;
            continue;
        }
        subst = subst + line;
    }
    return 1;
}