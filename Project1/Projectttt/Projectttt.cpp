#include <iostream>
#include <vector>

// Класс для хранения временной метки
class TimeStamp {
public:
    int year;
    int month;
    int day;
    int hours;
    int minutes;

    TimeStamp(int year, int month, int day, int hours, int minutes) {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hours = hours;
        this->minutes = minutes;
    }
};

// Класс "Посетитель"
class Visitor {
public:
    std::string firstName;
    std::string lastName;
    std::string passportNumber;
    TimeStamp entryTime;
    TimeStamp exitTime;

    Visitor(std::string firstName, std::string lastName, std::string passportNumber, TimeStamp entryTime)
    {
        this->firstName = firstName;
        this->lastName = lastName;
        this->passportNumber = passportNumber;
        this->entryTime = entryTime;
    }
};

// Класс "Контрольно-пропускной пункт"
class Checkpoint {
private:
    int visitorCount;
    std::vector<Visitor> visitors;

public:
    Checkpoint() {
        visitorCount = 0;
    }

    // Метод регистрации входа посетителя на объект
    void registerEntry(const Visitor& visitor) {
        visitors.push_back(visitor);
        visitorCount++;
    }

    // Метод регистрации выхода посетителя из объекта
    void registerExit(const std::string& passportNumber, const TimeStamp& exitTime) {
        for (int i = 0; i < visitors.size(); i++) {
            if (visitors[i].passportNumber == passportNumber) {
                visitors[i].exitTime = exitTime;
                break;
            }
        }
        visitorCount--;
    }

    // Метод вывода списка посетителей, находящихся на объекте
    void printVisitors() {
        std::cout << "Visitors currently inside the object:" << std::endl;
        for (const Visitor& visitor : visitors) {
            std::cout << "Name: " << visitor.firstName << " " << visitor.lastName << std::endl;
            std::cout << "Passport Number: " << visitor.passportNumber << std::endl;
            std::cout << "Entry Time: " << visitor.entryTime.year << "-" << visitor.entryTime.month << "-"
                << visitor.entryTime.day << " " << visitor.entryTime.hours << ":" << visitor.entryTime.minutes << std::endl;
            if (visitor.exitTime.year != 0) {
                std::cout << "Exit Time: " << visitor.exitTime.year << "-" << visitor.exitTime.month << "-"
                    << visitor.exitTime.day << " " << visitor.exitTime.hours << ":" << visitor.exitTime.minutes << std::endl;
            }
            std::cout << std::endl;
        }
    }

    // Перегрузка оператора += для регистрации входа посетителя
    void operator+=(const Visitor& visitor) {
        registerEntry(visitor);
    }

    // Перегрузка оператора -= для регистрации выхода посетителя
    void operator-=(const std::string& passportNumber) {
        TimeStamp exitTime(0, 0, 0, 0, 0);
        registerExit(passportNumber, exitTime);
    }
};

int main() {
    // Создание объекта класса "Контрольно-пропускной пункт"
    Checkpoint checkpoint;

    // Создание временных меток
    TimeStamp entryTime(2022, 4, 15, 10, 30);
    TimeStamp exitTime(2022, 4, 15, 12, 0);

    // Создание посетителей
    Visitor visitor1("John", "Doe", "ABC123", entryTime);
    Visitor visitor2("Jane", "Smith", "XYZ789", entryTime);

    // Регистрация входа посетителей на объект
    checkpoint.registerEntry(visitor1);
    checkpoint.registerEntry(visitor2);

    // Регистрация выхода посетителя из объекта
    checkpoint.registerExit("ABC123", exitTime);

    // Вывод списка посетителей, находящихся на объекте
    checkpoint.printVisitors();

    // Использование перегруженных операторов
    checkpoint += Visitor("Mike", "Johnson", "DEF456", entryTime);
    checkpoint -= "XYZ789";

    // Вывод списка посетителей после использования операторов
    checkpoint.printVisitors();

    return 0;
}