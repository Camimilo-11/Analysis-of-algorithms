#include <iostream>
#include <vector>

enum SlotState { EMPTY, OCCUPIED, DELETED };

struct HashSlot {
    int key;
    SlotState state = EMPTY;
};

class ClosedHashTable {
private:
    int capacity;
    int size;
    std::vector<HashSlot> table;

    int hashFunction(int key) const {
        int h = key % capacity;
        if (h < 0) h += capacity;
        return h;
    }

public:
    ClosedHashTable(int cap) : capacity(cap), size(0), table(cap) {}

    bool insert(int key) {
        if (size >= capacity) return false;
        int index = hashFunction(key);
        int firstDeleted = -1;

        for (int i = 0; i < capacity; ++i) {
            int probe = (index + i) % capacity;
            if (table[probe].state == OCCUPIED) {
                if (table[probe].key == key) return false;
            } else if (table[probe].state == DELETED) {
                if (firstDeleted == -1) firstDeleted = probe;
            } else {
                int target = (firstDeleted != -1) ? firstDeleted : probe;
                table[target].key = key;
                table[target].state = OCCUPIED;
                size++;
                return true;
            }
        }
        if (firstDeleted != -1) {
            table[firstDeleted].key = key;
            table[firstDeleted].state = OCCUPIED;
            size++;
            return true;
        }
        return false;
    }

    bool search(int key) const {
        int index = hashFunction(key);
        for (int i = 0; i < capacity; ++i) {
            int probe = (index + i) % capacity;
            if (table[probe].state == OCCUPIED) {
                if (table[probe].key == key) return true;
            } else if (table[probe].state == EMPTY) {
                return false;
            }
        }
        return false;
    }

    bool remove(int key) {
        int index = hashFunction(key);
        for (int i = 0; i < capacity; ++i) {
            int probe = (index + i) % capacity;
            if (table[probe].state == OCCUPIED) {
                if (table[probe].key == key) {
                    table[probe].state = DELETED;
                    size--;
                    return true;
                }
            } else if (table[probe].state == EMPTY) {
                return false;
            }
        }
        return false;
    }

    void display() const {
        for (int i = 0; i < capacity; ++i) {
            std::cout << "Slot " << i << ": ";
            if (table[i].state == OCCUPIED) {
                std::cout << table[i].key;
            } else if (table[i].state == DELETED) {
                std::cout << "[DELETED]";
            } else {
                std::cout << "[EMPTY]";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    ClosedHashTable ht(7);
    ht.insert(10);
    ht.insert(17);
    ht.insert(24);

    std::cout << "Estado de la Tabla Hash (M=7):\n";
    ht.display();

    std::cout << "\nBusqueda de 17: " << (ht.search(17) ? "Encontrado" : "No encontrado") << "\n";
    std::cout << "Eliminando 17...\n";
    ht.remove(17);
    ht.display();

    return 0;
}
