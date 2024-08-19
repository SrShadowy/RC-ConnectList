#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

void connect(std::string server, std::string user, std::string pass)
{
	std::string cmdkey = "cmdkey.exe /generic:";
	cmdkey.append(server);
	cmdkey.append(" /user:" + user);
	cmdkey.append(" /pass:" + pass);


	std::string mstsc = "mstsc.exe /v ";
	mstsc.append(server);


	std::cout << cmdkey
		<< std::endl
		<< mstsc << std::endl;
	system(cmdkey.c_str());
	system(mstsc.c_str());
}

void help() {
	std::cout << "\n\t\t\tRC Connect V0.0.1\n\n"
		<< "\tHelp menu\n"
		<< "\tUse commands -h -help -? to open this menu\n"
		<< "\tThis program calling mstsc to open one server, need all credencials to open, using cmdkey\n"
		<< "\tcommands to use:\n"
		<< "\t-h, -help or -? : to open menu help\n"
		<< "\t-file file.txt or file.txt : the file contrain one list of connections file need contrain format\n"
		<< "Server User Password\n"
		<< "\t-s:server -u:user -p:password : open this connection\n"
		<< "\t-US: NAME PASS : Create Default user and pass that command create US_DEFAULT on folder\n"
		<< "\t\t By SrShadowy \n\n"
		<< std::endl;
}

int create_user_default(std::string user, std::string pass)
{
	std::ofstream input_file("US_DEFAULT");
	if( input_file.is_open() )
	{
		input_file << user << std::endl << pass;
	}
	input_file.close();
	
}


int read_file_to_connect(std::string src)
{
	std::vector<std::string> xconnect;
	std::string line;

	std::ifstream input_file(src.c_str());

	if (!input_file.is_open()) 
	{
		std::cerr << "Could not open the file - '"
			<< src << "'" << std::endl;
		return EXIT_FAILURE;
	}

	while (std::getline(input_file, line)) 
		xconnect.push_back(line);
	
	std::ifstream default_user("US_DEFAULT");
		

	bool have_default_user = default_user.is_open();
	std::string us, pass;
	
	std::getline(default_user, us);	std::getline(default_user, pass);
	


	for(int i = 0; i< xconnect.size(); ++i)//for (const auto& i : xconnect) 
	{
		std::string connect_str = xconnect[i];

		std::size_t position = connect_str.find(" ");
		
		if(position == std::string::npos && have_default_user)
		{
		//	MessageBox(NULL,us.c_str(),"Caption",MB_OK);
		//	MessageBox(NULL,pass.c_str(),"Caption",MB_OK);
			connect(connect_str, us, pass);
			
			continue;
			//MessageBox(NULL,us.c_str(),"Caption",MB_OK);
		}
		
		
		if (position == std::string::npos)
			return EXIT_FAILURE;

		std::string server = connect_str.substr(0, position);
		connect_str = connect_str.erase(0,position + 1);
		
		position = connect_str.find(" ");
		

		
		
		
		if (position == std::string::npos)
			return EXIT_FAILURE;
		
		

		std::string user = connect_str.substr(0, position);
		connect_str = connect_str.erase(0, position + 1);

		std::string password = connect_str;

		connect(server, user, password);
	}


	input_file.close();
	return EXIT_SUCCESS;
}


int main(int argc, char** argv)
{

	// controller
	if (argc <= 1) 
	{
		help();
		system("pause");
		return 1;
	}
	else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-?") == 0 )
	{
		help();
		system("pause");
		return 1;
	}

	if (strcmp(argv[1], "-file") == 0) 
	{
		if (argc == 2) 
		{
			std::cout << " need file ";
			system("pause");
			return 1;
		}

		read_file_to_connect(argv[2]);
	}

	if (strcmp(argv[1], "-US:") == 0) 
	{
		if (argc == 2) 
		{
			std::cout << " user and pass ";
			system("pause");
			return 1;
		}

		create_user_default(argv[2], argv[3]);
		//read_file_to_connect(argv[2]);
		
	
	}

	
	if (std::string(argv[1]).find(".txt") != std::string::npos) 
		read_file_to_connect(argv[1]);
	

	if (std::string(argv[1]).find("-s:") != std::string::npos) 
	{
		if (argc >= 4)
		{
			std::string server = std::string(argv[1]).substr(3);
			std::string user = std::string(argv[2]).substr(3); 
			std::string password = std::string(argv[3]).substr(3);

			connect(server, user, password);
		}
	}

	return 0;
}
