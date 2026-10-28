// Define Cpu with a model, a core count, and describe().
// Define Ram and Disk with a size in gigabytes and describe().
//
// Define Computer with a constructor that accepts cpuModel, cores, and ramGb.
// It must create its own Cpu, Ram, and 512 GB Disk, and expose describe().
// ComputerWorkshop is provided. Do not modify it.
// Define Cpu with a model, a core count, and describe().
class Cpu{
    private:
    string model;
    int core;
    public:
    string describe(){
        return "CPU: " + model +" (" + toString(core) + " cores)";
    }
};
// Define Ram and Disk with a size in gigabytes and describe().
class Ram{
    private:
    int size;
    public:
    Ram(int size_):size{size_}{

    }
    string describe(){
        return "RAM: " + toString(size) + " GB";
    }
};

class Disk{
    private:
    int size;
    public:
    Disk(int size_):size{size_}{

    }
    string describe(){
        return "Disk: " + toString(size) + " GB";
    }
};
//
// Define Computer with a constructor that accepts cpuModel, cores, and ramGb.
// It must create its own Cpu, Ram, and 512 GB Disk, and expose describe().
// ComputerWorkshop is provided. Do not modify it.
class Computer{
private:
    Cpu cpuMode;
    Ram ram;
    Disk disk;

public: 
    Computer(string model, int cores, int ramGb):cpuMode(model), ram(cores), disk(ramGb){

    }

    string describe(){
        return cpuMode.describe()+" | "+ram.describe()+" | "+disk.describe();
    }
};
class ComputerWorkshop {
private:
    static constexpr int PARTS_PER_COMPUTER = 3;

    unordered_map<int, unique_ptr<Computer>> computers;
    int nextId = 0;

public:
    ComputerWorkshop() = default;

    int build(const string& cpuModel, int cores, int ramGb) {
        int id = nextId++;
        computers.emplace(id, make_unique<Computer>(cpuModel, cores, ramGb));
        return id;
    }

    int computerCount() const {
        return static_cast<int>(computers.size());
    }

    int partCount() const {
        return static_cast<int>(computers.size()) * PARTS_PER_COMPUTER;
    }

    string describe(int id) const {
        auto computerIt = computers.find(id);
        return computerIt == computers.end()
            ? "SCRAPPED"
            : computerIt->second->describe();
    }

    bool scrap(int id) {
        return computers.erase(id) > 0;
    }
};

/**
 * Your ComputerWorkshop object will be instantiated and called as such:
 * ComputerWorkshop obj;
 * int param_1 = obj.build(cpuModel, cores, ramGb);
 * int param_2 = obj.computerCount();
 * int param_3 = obj.partCount();
 * string param_4 = obj.describe(id);
 * bool param_5 = obj.scrap(id);
 */
