#include<iostream>
#include<fstream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-----------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS	const std::string& last_name, const std::string& first_name, unsigned int age
#define HUMAN_GIVE_PARAMETERS	last_name, first_name, age
class Human
{
	static const int LAST_NAME_WIDTH = 15;
	static const int FIRST_NAME_WIDTH = 10;
	static const int AGE_WIDTH = 4;
	std::string last_name;
	std::string first_name;
	unsigned int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}
	//				Constructors:
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	virtual std::ostream& print(std::ostream& os)const
	{
		return os << last_name << " " << first_name << " " << age << " y/o";
	}
	virtual std::ofstream& print(std::ofstream& ofs)const
	{
		//ofs << last_name << " " << first_name << " " << age;
		ofs.width(LAST_NAME_WIDTH);
		ofs << std::left;
		ofs << last_name;
		ofs.width(FIRST_NAME_WIDTH);
		ofs << first_name;
		ofs.width(AGE_WIDTH);
		ofs << age;
		return ofs;
	}
};
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.print(os);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	obj.print(ofs);
	return ofs;
}

#define STUDENT_TAKE_PARAMETERS	const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS	speciality, group, rating, attendance
class Student : public Human
{
	static const int SPECIALITY_WIDTH = 22;
	static const int GROUP_WIDTH = 8;
	static const int RATING_WIDTH = 8;
	static const int ATTENDANCE_WIDTH = 8;
	std::string speciality;
	std::string group;
	double rating;		//успеваемость
	double attendance;	//посещаемость
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}
	//				Constructors:
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os) << speciality << " " << group << " rating:" << rating << ", attendance:" << attendance;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);
		ofs.width(SPECIALITY_WIDTH);
		ofs << speciality;
		ofs.width(GROUP_WIDTH);
		ofs << group;
		ofs.width(RATING_WIDTH);
		ofs << rating;
		ofs.width(ATTENDANCE_WIDTH);
		ofs << attendance;
		return ofs;
	}
};

#define TEACHER_TAKE_PARAMETERS	const std::string& speciality, unsigned int experience
#define TEACHER_GIVE_PARAMETERS	speciality, experience
class Teacher :public Human
{
	static const int SPECIALITY_WIDTH = 22;
	static const int EXPERIENCE_WIDTH = 5;
	std::string speciality;
	unsigned int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	unsigned int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}
	//				Constructors:
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//				Methods:
	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os) << " " << speciality << ", experience: " << experience << " years";
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);
		ofs.width(SPECIALITY_WIDTH);
		ofs << speciality;
		ofs.width(EXPERIENCE_WIDTH);
		ofs << experience;
		return ofs;
	}
};

class Graduate :public Student
{
	std::string subject;
public:
	const std::string& get_subject()const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const std::string& subject)
		:Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	std::ostream& print(std::ostream& os)const override
	{
		return Student::print(os) << " Subject: " << subject;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Student::print(ofs);
		ofs << subject;
		return ofs;
	}
};

void print(Human* group[], const int size)
{
	cout << delimiter << endl;
	for (int i = 0; i < size; i++)
	{
		//group[i]->info();
		cout << *group[i] << endl;
		cout << delimiter << endl;
	}
}
void save(Human* group[], const int size, const char filename[])
{
	std::ofstream fout(filename);
	for (int i = 0; i < size; i++)
	{
		fout << typeid(*group[i]).name() << ":\t";
		fout << *group[i] << endl;
	}
	fout.close();
	char command[FILENAME_MAX] = "notepad ";
	strcat_s(command, FILENAME_MAX, filename);
	system(command);
}
void clear_memory(Human* group[], const int size)
{
	for (int i = 0; i < size; i++)
	{
		delete group[i];
	}
}

//#define INHERITANCE
#define POLYMORPHISM	//Многоформенность

void main()
{
	setlocale(LC_ALL, "");
#ifdef INHERITANCE
	/*Human human("Тупенко", "Василий", 18);
human.info();*/

	Student stud("Pinkman", "Jessie", 25, "Chemistry", "WW_220", 95, 99);
	stud.info();

	Teacher teacher("White", "Walter", 50, "Chemistry", 20);
	teacher.info();

	Graduate grad("Schreder", "Hank", 40, "Criminalistic", "OBN", 90, 70, "How to catch Heisenberg");
	grad.info();
#endif // INHERITANCE

	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 25, "Chemistry", "WW_220", 95, 98),
		new Teacher("White", "Walter", 50, "Chemistry", 20),
		new Graduate("Schreder", "Hank", 40, "Ctriminalistic", "OBN", 90, 70, "How to catch Heisenberg"),
		new Student("Vercetti", "Tomas", 30, "Theft", "Vice", 98, 100),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 25)
	};

	print(group, sizeof(group) / sizeof(group[0]));
	save(group, sizeof(group) / sizeof(group[0]), "group.txt");

	clear_memory(group, sizeof(group) / sizeof(group[0]));
}