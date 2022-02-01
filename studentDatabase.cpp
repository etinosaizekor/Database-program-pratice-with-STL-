#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <iterator>

class Student{
    friend class StudentDatabase;
protected:
    Student();
    Student(size_t id, const char * firstName,const char * lastName,  const char * dept):id(id), 
    firstName(firstName),  lastName(lastName),department(dept){};

    void formatPrint() const{ 
        std::ostringstream stringFormat;
        stringFormat <<id << "\t"<< firstName <<"\t"  << lastName <<"\t"<<department;
        
        std::cout<<stringFormat.str() <<std::endl;
    }

    size_t id;
    std::string firstName;
    std::string lastName;
    std::string department;
};


class StudentDatabase{
    public:
    void insert(int, const char*, const char*, const char*);
    size_t countName(std::string) const; //count the number of student that has the same name;
    size_t countNotOfDepartment() const;
    bool allSameDepartment(std::string) const;
    bool notAvailableDepartment(std::string) const;
    void sortById();
    bool peekById(int) const;
    void printAll() const;
    void deleteAllEntry();
    std::string getName(int) const;
    void removeRecord(int);
    void copyAllEntry(StudentDatabase &);
    void printAllname();


    private:
    std::vector<Student> database;
};


//StudentDatabaseClass implementatation
void StudentDatabase::insert(int s_id, const char * firstName, const char * lastName, const char * department){
    Student newStudent(s_id, firstName, lastName, department);
    database.push_back(newStudent);
};

void StudentDatabase::copyAllEntry(StudentDatabase &newDatabase){
    std::copy(begin(database), end(database), std::back_inserter(newDatabase.database));
}

void StudentDatabase::printAll()const{
    for(auto &v : database){
        v.formatPrint();
    }
};
size_t StudentDatabase::countName(std::string name) const{
    auto count = std::count_if(begin(database), end(database), [&name](auto &obj){
        return obj.firstName == name;
    });
    return count;
}

bool StudentDatabase::allSameDepartment(std::string department) const{
    auto status = std::all_of(begin(database), end(database), [&department](auto &student){
        return student.department == department;
    });
    return status;
};

bool StudentDatabase::peekById(int s_id) const{
    auto status = std::any_of(begin(database), end(database), [&s_id](auto & obj){
        return obj.id == s_id;
    });
    return status;
}

std::string StudentDatabase::getName(int s_id) const{
    auto student = std::find_if(begin(database), end(database), [&s_id](auto & obj){
        return obj.id == s_id;
    });
    return student->firstName;
}

void StudentDatabase::sortById() {
    std::sort(begin(database), end(database), [](auto & l, auto &r){
        return l.id < r.id;
    });
}

void StudentDatabase::removeRecord(int s_id){
    database.erase(std::remove_if(begin(database), end(database), [&s_id](auto &obj){
        return obj.id == s_id;
    }));
}

 bool StudentDatabase::notAvailableDepartment(std::string department) const{
     auto status = std::none_of(begin(database),end(database), [&department](auto &obj){
         return obj.department == department;
     });
     return status;
 }

void StudentDatabase::deleteAllEntry(){
    database.erase(begin(database));
}



int main(){

    StudentDatabase Comp117;
    Comp117.insert(199777, "John", "Paul", "Software Engineering");
    Comp117.insert(182113, "Jennifer", "Stallone", "Software Engineering");
    Comp117.insert(13334, "Chuks", "Stallone", "Software Engineering");
    Comp117.insert(199777, "John", "James", "Computer Engineering");
    Comp117.printAll();
    std::cout<<std::endl;
    std::cout<<"There are " <<Comp117.countName("John") <<" John in the class" <<std::endl;
    std::cout<<std::boolalpha
                <<"Are all student registered from the same department?: "
                <<Comp117.allSameDepartment("Software Engineering") <<std::endl;

    std::cout<<"Name of Student with the ID 199777: "
            <<Comp117.getName(199777) <<std::endl;
    std::cout<<"Is there a student with the Id of 182113?: " 
            <<std::boolalpha<< Comp117.peekById(182113) <<std::endl
            <<"Removing Jennifer Stallone from database: " <<std::endl;
    Comp117.removeRecord(182113);
    std::cout<<"Updated Database: ";
    Comp117.printAll();
    std::cout<<std::endl;
    StudentDatabase allStudentDatabase;
    std::cout<<"Copying all Comp117 student to allStudent Database: " <<std::endl;
    Comp117.copyAllEntry(allStudentDatabase);
    std::cout<<"All entries in allStudent Database" <<std::endl;
    allStudentDatabase.printAll();

       
    

    return 0;
}