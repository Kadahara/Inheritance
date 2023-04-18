#include<iostream>
#include<string>
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
	Human(const std::string& last_name, const std::string& first_name, unsigned int age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "Hconstructor:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	void info()const
	{
		cout << last_name << " " << first_name << " " << age << " y/o " << endl;
	}

};
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
		const std::string& last_name, const std::string& first_name, unsigned int age,
		const std::string& speciality, const std::string& group, double rating, double attendance
	) : Human(last_name, first_name,age)
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
			const std::string& last_name, const std::string& first_name, unsigned int age,
			const std::string& post
		) : Human(last_name, first_name, age)
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
	(	const std::string& last_name, const std::string& first_name, unsigned int age,
		const std::string& speciality, const std::string& group, double rating, double attendance,
		const std::string& diplom
	) : Student(last_name, first_name, age ,speciality, group, rating, attendance)
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


void main()
{
	setlocale(LC_ALL, "");
	/*Human human("Тупенко", "Василий", 18);
	human.info();*/

	Student stud("Pinkman", "Jessie", 25, "Chemistry", "WW_220", 95, 99);
	stud.info();
}