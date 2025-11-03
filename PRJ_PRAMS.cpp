#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// Structure for pet details
struct Pet {
    int id;
    string name;
    string species;
    int age;
    string healthStatus;
};

// Structure for adopter details
struct Adopter {
    string adopterName;
    string contact;
    Pet adoptedPet;
};

// Class Definition
class PetRescueAdoptionSystem {
private:
    vector<Pet> rescueList;
    vector<Adopter> adoptionList;
    int nextId = 1;

    const string rescueFile = "Rescue_Records.txt";
    const string adoptionFile = "Adoption_Records.txt";

public:
    PetRescueAdoptionSystem() {
        loadRescueData();
        loadAdoptionData();
        if (!rescueList.empty())
            nextId = rescueList.back().id + 1;
    }

    // Save formatted rescue records
    void saveRescueData() {
        ofstream fout(rescueFile);
        fout << "============================\n";
        fout << "     🐾 RESCUE RECORDS 🐾   \n";
        fout << "============================\n\n";
        if (rescueList.empty()) {
            fout << "No pets available in rescue.\n";
        } else {
            for (const auto &pet : rescueList) {
                fout << "Pet ID        : " << pet.id << "\n";
                fout << "Name          : " << pet.name << "\n";
                fout << "Species       : " << pet.species << "\n";
                fout << "Age           : " << pet.age << "\n";
                fout << "Health Status : " << pet.healthStatus << "\n";
                fout << "-----------------------------------------\n";
            }
        }
        fout.close();
    }

    // Save formatted adoption records
    void saveAdoptionData() {
        ofstream fout(adoptionFile);
        fout << "=============================================\n";
        fout << "     🏡 PET ADOPTION RECORDS 🏡\n";
        fout << "=============================================\n\n";
        if (adoptionList.empty()) {
            fout << "No pets have been adopted yet.\n";
        } else {
            for (const auto &adp : adoptionList) {
                fout << "Adopter Name  : " << adp.adopterName << "\n";
                fout << "Contact No.   : " << adp.contact << "\n";
                fout << "Pet ID        : " << adp.adoptedPet.id << "\n";
                fout << "Pet Name      : " << adp.adoptedPet.name << "\n";
                fout << "Species       : " << adp.adoptedPet.species << "\n";
                fout << "Age           : " << adp.adoptedPet.age << "\n";
                fout << "Health Status : " << adp.adoptedPet.healthStatus << "\n";
                fout << "----------------------------------------------\n";
            }
        }
        fout.close();
    }

    // Load data from Rescue file (basic version)
    void loadRescueData() {
        ifstream fin(rescueFile);
        if (!fin)
            return; // no file yet
        string line;
        Pet pet;
        while (getline(fin, line)) {
            if (line.find("Pet ID") != string::npos) {
                pet = Pet();
                pet.id = stoi(line.substr(line.find(":") + 1));
            } else if (line.find("Name") != string::npos && line.find("Pet Name") == string::npos)
                pet.name = line.substr(line.find(":") + 1);
            else if (line.find("Species") != string::npos)
                pet.species = line.substr(line.find(":") + 1);
            else if (line.find("Age") != string::npos)
                pet.age = stoi(line.substr(line.find(":") + 1));
            else if (line.find("Health Status") != string::npos) {
                pet.healthStatus = line.substr(line.find(":") + 1);
                rescueList.push_back(pet);
            }
        }
        fin.close();
    }

    // Load adoption data from file
    void loadAdoptionData() {
        ifstream fin(adoptionFile);
        if (!fin)
            return;
        string line;
        Adopter adp;
        while (getline(fin, line)) {
            if (line.find("Adopter Name") != string::npos)
                adp.adopterName = line.substr(line.find(":") + 1);
            else if (line.find("Contact No") != string::npos)
                adp.contact = line.substr(line.find(":") + 1);
            else if (line.find("Pet ID") != string::npos)
                adp.adoptedPet.id = stoi(line.substr(line.find(":") + 1));
            else if (line.find("Pet Name") != string::npos)
                adp.adoptedPet.name = line.substr(line.find(":") + 1);
            else if (line.find("Species") != string::npos)
                adp.adoptedPet.species = line.substr(line.find(":") + 1);
            else if (line.find("Age") != string::npos)
                adp.adoptedPet.age = stoi(line.substr(line.find(":") + 1));
            else if (line.find("Health Status") != string::npos) {
                adp.adoptedPet.healthStatus = line.substr(line.find(":") + 1);
                adoptionList.push_back(adp);
            }
        }
        fin.close();
    }

    // Add a rescued pet
    void addRescuedPet() {
        Pet pet;
        pet.id = nextId++;
        cin.ignore();
        cout << "\nEnter Pet Name: ";
        getline(cin, pet.name);
        cout << "Enter Species (Dog/Cat/etc): ";
        getline(cin, pet.species);
        cout << "Enter Age: ";
        cin >> pet.age;
        cin.ignore();
        cout << "Enter Health Status: ";
        getline(cin, pet.healthStatus);

        rescueList.push_back(pet);
        saveRescueData();
        cout << "\nPet added successfully and saved to file!\n";
    }

    // Display all rescued pets
    void viewRescuePets() {
        if (rescueList.empty()) {
            cout << "\nNo rescued pets available.\n";
            return;
        }
        cout << "\nList of Rescued Pets:\n";
        cout << "---------------------------------------------\n";
        for (const auto &pet : rescueList) {
            cout << "ID: " << pet.id
                 << " | Name: " << pet.name
                 << " | Species: " << pet.species
                 << " | Age: " << pet.age
                 << " | Health: " << pet.healthStatus << endl;
        }
    }

    // Adopt a pet
    void adoptPet() {
        if (rescueList.empty()) {
            cout << "\nNo pets available for adoption.\n";
            return;
        }

        int id;
        cout << "\nEnter Pet ID to Adopt: ";
        cin >> id;
        bool found = false;

        for (auto it = rescueList.begin(); it != rescueList.end(); ++it) {
            if (it->id == id) {
                Adopter adopter;
                cin.ignore();
                cout << "Enter Adopter Name: ";
                getline(cin, adopter.adopterName);
                cout << "Enter Contact Number: ";
                getline(cin, adopter.contact);
                adopter.adoptedPet = *it;

                adoptionList.push_back(adopter);
                rescueList.erase(it);

                saveRescueData();
                saveAdoptionData();

                cout << "\nAdoption Successful! Records updated in files.\n";
                found = true;
                break;
            }
        }

        if (!found)
            cout << "\nPet ID not found!\n";
    }

    // View adopted pets
    void viewAdoptedPets() {
        if (adoptionList.empty()) {
            cout << "\nNo pets have been adopted yet.\n";
            return;
        }
        cout << "\nList of Adopted Pets:\n";
        cout << "---------------------------------------------\n";
        for (const auto &a : adoptionList) {
            cout << "Adopter: " << a.adopterName
                 << " | Contact: " << a.contact
                 << " | Pet: " << a.adoptedPet.name
                 << " (" << a.adoptedPet.species << ")\n";
        }
    }
};

// Main Function
int main() {
    PetRescueAdoptionSystem system;
    int choice;

    do {
        cout << "\n=====Pet Rescue & Adoption Management System=====";
        cout << "\n1. Add Rescued Pet";
        cout << "\n2. View Rescued Pets";
        cout << "\n3. Adopt a Pet";
        cout << "\n4. View Adoption Records";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system.addRescuedPet();
            break;
        case 2:
            system.viewRescuePets();
            break;
        case 3:
            system.adoptPet();
            break;
        case 4:
            system.viewAdoptedPets();
            break;
        case 5:
            cout << "\nExiting... Thank you for supporting animal rescue!\n";
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
