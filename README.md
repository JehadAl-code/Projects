# Hospital Management System (HMS)

## 🏥 Project Overview
A C++ based management system designed for hospital triage. This project demonstrates the efficient handling of patient records and emergency prioritization using advanced data structures.
## 🚀 Key Features
* **Priority Triage:** Automatically sorts patients based on medical urgency (1: Critical, 5: Normal).
* **Unique Identification:** Ensures no duplicate Patient IDs using tree-based searching.
* **Data Persistence:** Saves and loads patient records from a local text file.
* **Activity Logging:** Tracks operations performed during the session.

## 🛠️ Data Structures Implemented
1.  **Min-Heap (Priority Queue):** Used for the triage queue to provide $O(1)$ access to the most urgent case and $O(\log n)$ insertion/deletion.
2.  **Binary Search Tree (BST):** Used for indexing patient IDs to allow for fast $O(\log n)$ searches and validations.
3.  **Linked List:** Implemented to store a chronological history of system actions.

## 📋 Requirements 
* **File I/O:** Reads from and writes to `patients.txt`.
* **Version Control:** Managed via Git.
* **Memory Management:** Includes a proper destructor to prevent memory leaks and manage dynamic allocation.

## 💻 How to Use
1.  **Compile:**
    ```bash
    g++ main.cpp -o hospital_system
    ```
2.  **Run:**
    ```bash
    ./hospital_system
    ```
3.  **Input:** Follow the on-screen menu to register patients, treat the next case, or view the current queue.
