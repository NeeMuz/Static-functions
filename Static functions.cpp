#include <iostream>
#include <vector>
#include <fstream>

class Reservoir {
public:
    std::string name;
    double width, length, maxDepth;

    Reservoir() : width(0), length(0), maxDepth(0) {}

    Reservoir(const std::string& n, double w, double l, double d)
        : name(n), width(w), length(l), maxDepth(d) {
    }

    double getVolume() const {
        return width * length * maxDepth;
    }

    double getSurfaceArea() const {
        return width * length;
    }

    bool isSameType(const Reservoir& other) const {
        return name == other.name;
    }

    bool operator>(const Reservoir& other) const {
        return getSurfaceArea() > other.getSurfaceArea();
    }
};

class ReservoirManager {
public:
    std::vector<Reservoir> reservoirs;

    void addReservoir(const Reservoir& r) {
        reservoirs.push_back(r);
    }

    void removeReservoir(const std::string& name) {
        reservoirs.erase(std::remove_if(reservoirs.begin(), reservoirs.end(),
            [&name](const Reservoir& r) { return r.name == name; }),
            reservoirs.end());
    }

    void saveToTextFile(const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& r : reservoirs) {
            file << "Name: " << r.name << "\tVolume: " << r.getVolume() << "\n";
        }
        file.close();
    }

    void saveToBinaryFile(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        file.write(reinterpret_cast<const char*>(reservoirs.data()), reservoirs.size() * sizeof(Reservoir));
        file.close();
    }
};

int main() {
    ReservoirManager manager;

    manager.addReservoir({ "Black Sea", 580, 1150, 2122 });
    manager.addReservoir({ "Lake Geneva", 80, 200, 15 });

    manager.saveToTextFile("Reservoirs.txt");
    manager.saveToBinaryFile("Reservoirs.bin");

    return 0;
}
