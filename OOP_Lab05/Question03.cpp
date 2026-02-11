#include <iostream>
using namespace std;

class Weapons {
public:
    void WeaponsDescription() {
        cout << "Weapons are used for defense and warfare." << endl;
    }
};

class HotWeapons : public Weapons {
public:
    void HotWeaponsDescription() {
        cout << "Hot weapons use heat, fire, or gunpowder to cause damage." << endl;
    }
};

class Bombs : public HotWeapons {
public:
    void BombsDescription() {
        cout << "Bombs explode and cause large-scale destruction." << endl;
    }
};

class NuclearBombs : public Bombs {
public:
    void NuclearBombsDescription() {
        cout << "Nuclear bombs explode using nuclear fission and fusion, causing massive destruction." << endl;
    }
};

int main() {
    NuclearBombs nb;

    nb.WeaponsDescription();
    nb.HotWeaponsDescription();
    nb.BombsDescription();
    nb.NuclearBombsDescription();

    return 0;
}
