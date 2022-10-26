#include <iostream>
#include <assert.h>
using namespace std;

/*
class: Computer
fields:
id(static)
object_Id
model(char*)
vendor(char*)
videocard(char*)
monitor(char*)
cpu_hz
core
ram
disk_size
isSSD(bool)
cin, cout overload
constructors
destructor
*/
/*
class: ComputerStore
store_name(char*)
store_address(char*)
Computer** computers; (array)
addComputer();
deleteComputer(int id);
cin, cout overload
constructors
destructor
*/
class Computer {
	static int staticId;
	int id;
	char* vendor = nullptr;
	char* model = nullptr;
	char* videoCard = nullptr;
	char* monitor = nullptr;
	double cpuHz;
	int core;
	int ram;
	int discSize;
	bool isSSD;
public:
	void SetVendor(const char* vendor1) {
		delete[] vendor;
		int len = strlen(vendor1) + 1;
		vendor = new char[len];
		strcpy_s(vendor, len, vendor1);
	}
	void SetModel(const char* model1) {
		delete[] model;
		int len = strlen(model1) + 1;
		model = new char[len];
		strcpy_s(model, len, model1);
	}
	void SetVideoCard(const char* videocard1) {
		delete[] videoCard;
		int len = strlen(videocard1) + 1;
		videoCard = new char[len];
		strcpy_s(videoCard, len, videocard1);
	}
	void SetMonitor(const char* monitor1) {
		delete[] monitor;
		int len = strlen(monitor1) + 1;
		monitor = new char[len];
		strcpy_s(monitor, len, monitor1);
	}
	void SetCpuHz(double cpu1) {
		cpuHz = cpu1;
	}
	void SetCore(int core1) {
		core = core1;
	}
	void SetRam(int ram1) {
		ram = ram1;
	}
	void SetDiscSize(int discSize1) {
		discSize = discSize1;
	}
	void SetIsSSD(bool isSSD1) {
		isSSD = isSSD1;
	}

	int GetId() const { return id; }
	const char* GetVendor() const { return vendor; }
	const char* GetModel() const { return model; }
	const char* GetVideoCard() const { return videoCard; }
	const char* GetMonitor() const { return monitor; }
	double GetCpuHz() const { return cpuHz; }
	int GetCore() const { return core; }
	int GetRam() const { return ram; }
	int GetDiscSize() const { return discSize; }
	bool GetIsSSD() const { return isSSD; }

	Computer() {
		id = staticId++;
		vendor = nullptr;
		model = nullptr;
		videoCard = nullptr;
		monitor = nullptr;
		SetCpuHz(0);
		SetCore(0);
		SetRam(0);
		SetDiscSize(0);
		SetIsSSD(0);
	}

	Computer(const char* vendor, const char* model, const char* videoCard, const char* monitor, double cpuHz, int core, int ram, int discSize, bool isSsd) {
		id = staticId++;
		SetVendor(vendor);
		SetModel(model);
		SetVideoCard(videoCard);
		SetMonitor(monitor);
		SetCpuHz(cpuHz);
		SetCore(core);
		SetRam(ram);
		SetDiscSize(discSize);
		SetIsSSD(isSSD);
	}

	Computer(const Computer& comp) {
		id = comp.id;
		SetVendor(comp.vendor);
		SetModel(comp.model);
		SetVideoCard(comp.videoCard);
		SetMonitor(comp.monitor);
		SetCpuHz(comp.cpuHz);
		SetCore(comp.core);
		SetRam(comp.ram);
		SetDiscSize(comp.discSize);
		SetIsSSD(comp.isSSD);
	}

	Computer& operator=(const Computer& comp) {
		SetVendor(comp.vendor);
		SetModel(comp.model);
		SetVideoCard(comp.videoCard);
		SetMonitor(comp.monitor);
		SetCpuHz(comp.cpuHz);
		SetCore(comp.core);
		SetRam(comp.ram);
		SetDiscSize(comp.discSize);
		SetIsSSD(comp.isSSD);
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Computer& obj) {
		out << "=============== Computer Info ===============\n";
		out << "ObjectId:" << obj.id;
		out<< "\nVendor: " << obj.vendor;
		out << "\nModel: " << obj.model;
		out << "\nMonitor: " << obj.monitor;
		out << "\nCpu-Hz: " << obj.cpuHz;
		out << "\nCore: " << obj.core;
		out << "\nRam: " << obj.ram;
		out << "\nDiskSize: " << obj.discSize;
		out << "\nSSD: " << obj.isSSD;
		return out;
	}

	friend istream& operator>>(istream& in, Computer& obj) {
		char* bf = new char[40];
		cout << "Model: ";
		in.getline(bf, 40);
		obj.SetModel(bf);

		cout << "Vendor: ";
		in.getline(bf, 40);
		obj.SetVendor(bf);

		cout << "Videocard: ";
		in.getline(bf, 40);
		obj.SetVideoCard(bf);

		cout << "Monitor: ";
		in.getline(bf, 40);
		obj.SetMonitor(bf);

		cout << "Cpu-Hz: ";
		double hz;
		cin >> hz;
		obj.SetCpuHz(hz);

		cout << "Core: ";
		int c;
		cin >> c;
		obj.SetCore(c);

		cout << "Ram: ";
		int r;
		cin >> r;
		obj.SetRam(r);

		cout << "Disc Size: ";
		int d;
		cin >> d;
		obj.SetDiscSize(d);

		cout << "is SSD ? (1 = Yes, 0 = No) : ";
		int i;
		cin >> i;
		obj.SetIsSSD(i);

		delete[] bf;
		return in;
	}

	~Computer() {
		delete[] vendor;
		delete[] model;
		delete[] videoCard;
		delete[] monitor;
	}
};
int Computer::staticId = 100;

class CompStore {
	char* name;
	char* address;
	Computer** computers;
	int count;
public:
	CompStore(const char* name, const char* add) {
		SetName(name);
		SetAddress(add);
		computers = nullptr;
		count = 0;
	}
	void SetName(const char* value) {
		delete[] name;
		int len = strlen(value) + 1;
		name = new char[len];
		strcpy_s(name, len, value);
	}
	void SetAddress(const char* value) {
		delete[] address;
		int len = strlen(value) + 1;
		address = new char[len];
		strcpy_s(address, len, value);
	}
	const char* GetName() { return name; }
	const char* GetAddress() { return address; }
	void AddComputer(const Computer* value) {
		Computer** temp = new Computer * [count + 1];
		for (int i = 0; i < count; i++)
			temp[i] = computers[i];
		temp[count] = new Computer(*value);
		delete[] computers;
		computers = temp;
		count++;
		temp = nullptr;
	}
	void DeleteComputer(int id) {
		int index = -1;
		for (int i = 0; i < count; i++) {
			if (computers[i]->GetId() == id) {
				index = i;
				break;
			}
		}
		if (index != -1) {
			Computer** temp = new Computer * [count - 1];
			for (int i = 0; i < index; i++) {
				temp[i] = computers[i];
			}

			for (int i = index; i < count; i++) {
				temp[i] = computers[i + 1];
			}
			delete[] computers;
			computers = temp;
			count--;
			temp = nullptr;
		}
	}
	friend ostream& operator<<(ostream& out, const CompStore& obj) {
		out << obj.name << endl;
		out << obj.address << endl;
		for (int i = 0; i < obj.count; i++) {
			cout << *obj.computers[i] << endl;
		}
		return out;
	}
	~CompStore() {
		for (int i = 0; i < count; i++)
			delete computers[i];
		delete[] computers;
	}
};

void main() {
	auto c = new Computer("asus", "tuf", "gforce gtx 3060ti", "QLED", 10, 16, 64, 1000, true);
	CompStore store("Irshad", "Inshaatcilar");
	store.AddComputer(c);
	store.AddComputer(new Computer("asus", "zenbook pro", "gforce gtx 1050ti", "QLED", 2.8, 8, 16, 512, true));
	cout << store << endl;
	store.DeleteComputer(101);
	cout << store << endl;
}