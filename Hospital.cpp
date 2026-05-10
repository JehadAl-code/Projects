#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Patient data representation
struct Patient {
    int id;
    string name;
    int urgency; // 1: Critical, 5: Normal
};

// Binary search tree structure for searching patients by ID
struct BSTNode {
    int id;
    string name;
    BSTNode *left, *right;
    BSTNode(int i, string n) : id(i), name(n), left(NULL), right(NULL) {}
};

// Operations log (Linked List)
struct Log {
    string action;
    Log* next;
};

class HospitalManager {
private:
    BSTNode* root = NULL;       // [Data Structure 1: BST] to ensure no ID duplication and fast search
    vector<Patient*> triage;    // [Data Structure 2: Min-Heap] to schedule patients by severity
    Log* history = NULL;

    // Clean up memory (Destructor helpers)
    void clearBST(BSTNode* node) {
        if (node) {
            clearBST(node->left);
            clearBST(node->right);
            delete node;
        }
    }

    // Heap operations (Priority Queue)
    void heapUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (triage[i]->urgency < triage[p]->urgency) {
                swap(triage[i], triage[p]);
                i = p;
            } else break;
        }
    }

    void heapDown(int i) {
        int n = triage.size();
        while (true) {
            int min = i;
            int l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && triage[l]->urgency < triage[min]->urgency) min = l;
            if (r < n && triage[r]->urgency < triage[min]->urgency) min = r;
            if (min == i) break;
            swap(triage[i], triage[min]);
            i = min;
        }
    }

    bool findID(int id, BSTNode* node) {
        if (!node) return false;
        if (node->id == id) return true;
        return (id < node->id) ? findID(id, node->left) : findID(id, node->right);
    }

    BSTNode* insertBST(BSTNode* node, int id, string name) {
        if (!node) return new BSTNode(id, name);
        if (id < node->id) node->left = insertBST(node->left, id, name);
        else if (id > node->id) node->right = insertBST(node->right, id, name);
        return node;
    }

public:
    ~HospitalManager() {
        for (auto p : triage) delete p;
        clearBST(root);
        while (history) { Log* t = history; history = history->next; delete t; }
    }

    // Read data from file [Requirement: Read from file]
    void loadPatients() {
        ifstream in("patients.txt");
        if (!in) return;
        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            int id, urg; string name;
            if (ss >> id >> urg) {
                ss.ignore(); getline(ss, name);
                Patient* p = new Patient{id, name, urg};
                triage.push_back(p);
                heapUp(triage.size() - 1);
                root = insertBST(root, id, name);
            }
        }
        in.close();
    }

    void registerPatient() {
    int id, urg; string name;
    cout << "Patient ID: "; 
    if (!(cin >> id)) { // Basic check for non-numeric input
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a numeric ID.\n";
        return;
    }

    if (findID(id, root)) { 
        // Instead of exiting, we just tell the user and go back to the menu
        cout << "\n[!] ERROR: Patient ID " << id << " already exists in the system.\n"; 
        return; 
    }
    
    cout << "Name: "; cin.ignore(); getline(cin, name);
    cout << "Urgency (1: Critical - 5: Normal): "; cin >> urg;

    Patient* p = new Patient{id, name, urg};
    triage.push_back(p);
    heapUp(triage.size() - 1);
    root = insertBST(root, id, name);
    
    cout << "Patient " << name << " registered successfully.\n";
}

    void treatPatient() {
        if (triage.empty()) { cout << "No patients in queue.\n"; return; }
        
        Patient* top = triage[0];
        cout << "Treating: " << top->name << " (Urgency: " << top->urgency << ")\n";
        
        // Delete from Heap
        delete top;
        triage[0] = triage.back();
        triage.pop_back();
        if (!triage.empty()) heapDown(0);
    }

    // Save data [Requirement: Write to file]
    void saveAndExit() {
        ofstream out("patients.txt");
        for (auto p : triage) out << p->id << " " << p->urgency << " " << p->name << endl;
        out.close();
        cout << "Data saved. Exiting...\n";
    }

 void viewQueue() {
        if (triage.empty()) {
            cout << "\nQueue is currently empty. No patients waiting.\n"; // Note: Addition here
            return;
        }
        cout << "\n--- Current Triage Queue ---\n";
        for (auto p : triage) {
            cout << "ID: " << p->id << " | Urgency: " << p->urgency << " | Name: " << p->name << endl;
        }
    }};
int main() {
    HospitalManager hospital;
    hospital.loadPatients();
    int c;
    do {
        cout << "\n1. Register Patient\n2. Treat Next (Highest Urgency)\n3. View Queue\n4. Save & Exit\nChoice: ";
        cin >> c;
        if (c == 1) hospital.registerPatient();
        else if (c == 2) hospital.treatPatient();
        else if (c == 3) hospital.viewQueue();
        else if (c == 4) hospital.saveAndExit();
    } while (c != 4);
    return 0;
}