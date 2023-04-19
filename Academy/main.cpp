#include<iostream>
#include<string>

#define delimiter "----------------------------------------------------------------"

#define HUMEN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, unsigned int age
#define HUMEN_GIVE_PARAMETERS last_name, first_name, age


using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Human
{
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
	//			constructors;
	Human(HUMEN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "Hconstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	virtual void info()const
	{
		cout << last_name << " " << first_name << " " << age << " y/o " << endl;
	}

};
#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance

class Student : public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
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
	void get_group(const std::string& group)
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
	//		конструктор
	Student
	(
		HUMEN_TAKE_PARAMETERS,STUDENT_TAKE_PARAMETERS
	) : Human(HUMEN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		get_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}
	void info()const
	{
		Human::info();
		cout << speciality << " " << group << " rating " << rating << " attendance " << attendance << endl;
	}

};

#define TEACHER_TAKE_PARAMETERS const std::string& post
#define TEACHER_GIVE_PARAMETERS post

class Teacher :public Human
{
	std::string post;
public:
	const std::string& get_post()const
	{
		return post;
	}
	void set_post(const std::string& post)
	{
		this->post = post;
	}
	//				Constructor
	Teacher
		(
			HUMEN_TAKE_PARAMETERS,TEACHER_TAKE_PARAMETERS
		) : Human(HUMEN_GIVE_PARAMETERS)
	{
		set_post(post);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	void info()const
	{
		Human::info();
		cout << " " << " subject " << post << endl;
	}
};

#define GRADUATE_TAKE_PARAMETERS const std::string& diplom
#define GRADUATE_GIVE_PARAMETERS diplom
class Graduate :public Student
{
	std::string diplom;
public:
	const std::string& get_diplom()const
	{
		return diplom;
	}
	void set_diplom(const std::string& diplom)
	{
		this->diplom = diplom;
	}
	//				Constructor
	Graduate
	(HUMEN_TAKE_PARAMETERS,STUDENT_TAKE_PARAMETERS,GRADUATE_TAKE_PARAMETERS
	) : Student(HUMEN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_diplom(diplom);
		cout << "TConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	void info()const
	{
		Student::info();
		cout << " " << " the topic of the diploma " << diplom << endl;
	}
};

//#define INHERITANCE

void main()
{
	setlocale(LC_ALL, "");


#ifdef INHERITANCE
	/*Human human("Тупенко", "Василий", 18);
human.info();*/

	Graduate Grad("Pinkman", "Jessie", 25, "Chemistry", "WW_220", 95, 99, "WEB-IT");
	Grad.info();
#endif // INHERITANCE
	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 25, "Chemistry", "WW_220", 90, 87),
		new Teacher("Pasha", "White", 50, "Chemistry"),
		new Graduate("Ivan", "Urgant", 37, "Criminalistic", "OBN", 95, 90, "How to catch Heizenberg")
	};
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		group[i]->info();
		cout << delimiter << endl;
	}
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
	}

}