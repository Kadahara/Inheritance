#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>	

using namespace std;

//#define WRITE_TO_FILE
//#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");

#ifdef WRITE_TO_FILE
	//1) ������� ����� ������(������ � ����);
	ofstream fout;
	//2)��������� �����. ������� ����� ����� ��� ���� ��� �� �������� � ����� ��������� ���� �� �����.
	fout.open("File.txt", std::ios_base::app); //���� std::ios_base::app ��������� ��������� ���������� � ����
	//���� - ��� �������. ��� �������, ��� ���, ������� ����� ���� ���������� ��� �������.

	//3)����� (����������) ���������� � ����;
	fout << "Hello files!" << endl;
	//4)������ ����������� ����� ���������! 
	//������ ��������� ������ ���������, ��� ����� �������� � ������������� ������������!!!
	fout.close();

	system("notepad File.txt");
#endif // WRITE_TO_FILE
#ifdef READ_FROM_FILE
	//0) ��������� ����� ������:
	const int  SIZE = 256;
	char buffer[SIZE] = {};

	//1) ������� � ��������� �����:
	ifstream fin("file.txt");
	//2)��������� �������� �� �����:
	if (fin.is_open())
	{
		//3) ���� ����� �������� ����� ������ ����...
		while (!fin.eof())// ���� HE ����� ����� 
		{
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		//4)��������� ����� ������ � ��� ������ ���� �� ��������.
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
#endif // READ_FROM_FILE

	const int NUMBER_SIZE = 20;
	char room_number[NUMBER_SIZE];
	char sz_source_filename[FILENAME_MAX] = {};
	char sz_wal_filename[FILENAME_MAX] = {};
	char sz_dhcpd_filename[FILENAME_MAX] = {};

	cout << "������� ����� ���������: "; cin >> room_number;
	strcat(sz_source_filename, room_number);
	strcat(sz_wal_filename, room_number);
	strcat(sz_dhcpd_filename, room_number);

	strcat(sz_source_filename, " RAW.txt");
	strcat(sz_wal_filename, " ready.txt");
	strcat(sz_dhcpd_filename, ".dhcpd");

	const int IP_BUFFER_SIZE = 16;
	const int MAC_BUFFER_SIZE = 18;
	char sz_ip_buffer[IP_BUFFER_SIZE] = {};
	char sz_mac_buffer[MAC_BUFFER_SIZE] = {};

	std::ofstream fout_wal(sz_wal_filename);
	std::ofstream fout_dhcpd(sz_dhcpd_filename);
	std::ifstream fin(sz_source_filename);
	if (fin.is_open())
	{
		for (int i = 1; !fin.eof(); i++)
		{
			//TODO: exchange
			fin >> sz_ip_buffer >> sz_mac_buffer;
			if (strlen(sz_ip_buffer) == 0 && strlen(sz_mac_buffer) == 0)continue;
			fout_wal << sz_mac_buffer << "\t" << sz_ip_buffer << endl;
			//cout << sz_mac_buffer << "\t" << sz_ip_buffer << endl;
			////////////////////////////////////////////////////////////
			for (int i = 0; sz_mac_buffer[i]; i++)if (sz_mac_buffer[i] == '-')sz_mac_buffer[i] = ':';
			cout << "host " << room_number << "-" << i << ":\n";
			cout << "{\n";
			cout << "\thardware ethernet\t" << sz_mac_buffer << ";\n";
			cout << "\tfixed-address\t\t" << sz_ip_buffer << ";\n";
			cout << "}\n";
			cout << endl;

			fout_dhcpd << "host " << room_number << "-" << i << ":\n";
			fout_dhcpd << "{\n";
			fout_dhcpd << "\thardware ethernet\t" << sz_mac_buffer << ";\n";
			fout_dhcpd << "\tfixed-address\t\t" << sz_ip_buffer << ";\n";
			fout_dhcpd << "}\n";
			fout_dhcpd << endl;


		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	fout_dhcpd.close();
	fout_wal.close();

	char sz_command_wal[FILENAME_MAX] = "start notepad ";
	char sz_command_dhcpd[FILENAME_MAX] = "start notepad ";

	strcat(sz_command_wal, sz_wal_filename);
	strcat(sz_command_dhcpd, sz_dhcpd_filename);

	system(sz_command_wal);
	system(sz_command_dhcpd);
}