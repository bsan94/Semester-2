#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <vector>
#include <direct.h>
using namespace std;

void login_page();
void existingUser();
void user_create();
void mainmenu();
void create_newnote();
void view();
void edit_or_delete();
void sharing();

class User
{
	private : 
		string username , password , un, pw,targetUser;
		string dirName, accountdirectory;
		int at , accounttype;
		//string outputfilename,inputfilename,filename,filedirectory;
		
	public :
	
		string getUsername()
		{
			return username;
		}
		
		string getPassword()
		{
			return password;
		}
		
		void setUsername(string u)
		{
			username = u;
		}
		
		void setPassword(string p)
		{
			password = p;
		}
		
		void setAccounttype(int at)
		{
			accounttype = at;
		}
		void saveUsername()
		{
			
			dirName = "User\\" + username;
			_mkdir(dirName.c_str());
			accountdirectory = dirName + "\\" + username + ".txt";
			ofstream file;
			file.open(accountdirectory.c_str());
			file << username << endl << password << endl << accounttype << endl;
			file.close();
			
		}
		bool loadUsername()
		{
			dirName = "User\\" + username;
			_mkdir(dirName.c_str());
			accountdirectory =  dirName + "\\" + username + ".txt";

			ifstream read(accountdirectory.c_str());
			getline(read, un);
			getline(read, pw);
			read >> at;
			read.close();
			
				if (un == username && pw == password)
				{
				cout << "\n\t\t\t You have been sucessfully Logged in !" << endl;
				return true;
				}
				else
				{
				cout << "\n\t\t\t Username and password combination is wrong !" << endl;
				return false;
				
				}
		}
		
		bool isTargetExist(string target)
		{
			string targetdirectory;
			
			dirName = "User\\" + target;
			targetdirectory =  dirName + "\\" + target + ".txt";

			ifstream read(targetdirectory.c_str());
			if(read.is_open())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		void usererrorpage()
		{
		cout << "\n\n\n\t\t****************************************************" << endl;
		cout << "\t\t\tERROR ! - USER DOESNT EXIST !" << endl;
		cout << "\t\t****************************************************" << endl;
		system("pause");
		}
		
		void settargetUser(string tu)
		{
			targetUser = tu;
		}
		
		string gettargetUser()
		{
			return targetUser;
		}

		
};
User user;

class Notes
{
	private:
		string username , password , title , note, notas;
		string dirTitle,dirNotes, accountdirectory,dirTitleShared;
		int titlenumbering;
	public :
		
		void setTitle(string t)
		{
			title = t;
		}
		
		void setNote(string n)
		{
			note = n;
		}
		
		string getTitle()
		{
			return title;
		}
		
		string getNote()
		{
			return note;
		}
		
		void saveTitle()
		{
	
			dirTitle = "User\\" + user.getUsername() + "\\Notes\\title.txt";
			ofstream writetitle(dirTitle.c_str(), ios::app );
			writetitle << title << "|";
			writetitle.close();
		}
		
		void saveNote()
		{
			
			dirNotes = "User\\" + user.getUsername() + "\\Notes\\" + title + ".txt";
			ofstream writenote(dirNotes.c_str() );
			writenote << note;;
			writenote.close();
		}
		
		bool isExist()
		{
			dirTitle = "User\\" + user.getUsername() + "\\Notes\\title.txt";
			ifstream readtitle(dirTitle.c_str());
			if(readtitle.is_open())
			{
				return true;
			}
			else
			{
				return false;
			}
			readtitle.close();
		}
			
		bool isExistShared()
		{
			dirTitle = "User\\" + user.getUsername() + "\\Notes\\titleShared.txt";
			ifstream readtitle(dirTitle.c_str());
			if(readtitle.is_open())
			{
				return true;
			}
			else
			{
				return false;
			}
			readtitle.close();
			
		}
		bool isNoteExist()
		{
			dirNotes = "User\\" + user.getUsername() + "\\Notes\\" + title + ".txt";
			ifstream readnote(dirNotes.c_str());
			if (readnote.is_open())
			{
				return true;
			}
			else
			{
				return false;
			}
			readnote.close();
		}
		void loadTitle()
		{
			string tajuk;
			dirTitle = "User\\" + user.getUsername() + "\\Notes\\title.txt";
			titlenumbering = 1;
			ifstream readtitle(dirTitle.c_str());
			while (!readtitle.eof())
			{
				getline(readtitle, tajuk,'|');
				cout << titlenumbering << ". " << tajuk << endl;
				titlenumbering++;
			}
			readtitle.close();	
		}
		void loadTitleShared()
		{
			string tajuk;
			dirTitle = "User\\" + user.getUsername() + "\\Notes\\titleShared.txt";
			titlenumbering = 1;
			ifstream readtitle(dirTitle.c_str());
			while (!readtitle.eof())
			{
				getline(readtitle, tajuk,'|');
				cout << titlenumbering << ". " << tajuk << endl;
				titlenumbering++;
			}
			readtitle.close();	
		}
		void loadNote()
		{
			dirNotes = "User\\" + user.getUsername() + "\\Notes\\" + title + ".txt";
			ifstream readnote(dirNotes.c_str());
			while (!readnote.eof())
			{	
				getline(readnote, notas);
				cout << notas;
			}
			cout << endl;
		}
		
		void errorpage()
		{
		cout << "\n\n\n\t\t****************************************************" << endl;
		cout << "\t\t\tERROR ! - NOTE DOESNT EXIST !" << endl;
		cout << "\t\t****************************************************" << endl;
		system("pause");
		}
		
		void editNote()
		{
			string notepad;
			dirNotes = "User\\" + user.getUsername() + "\\Notes\\" + title + ".txt";
			notepad = "notepad.exe " + dirNotes;
			system(notepad.c_str());
		}
		
		void shareNote()
		{
			string dirName,dirNotesTarget;
		    dirName = "User\\" + user.gettargetUser() + "\\Notes";
		    _mkdir(dirName.c_str());
		
			dirTitleShared = "User\\" + user.gettargetUser() + "\\Notes\\titleShared.txt";
			ofstream writetitle(dirTitleShared.c_str(), ios::app );
			writetitle << title << "|";
			writetitle.close();
			dirNotesTarget = "User\\" + user.gettargetUser() + "\\Notes\\" + title + ".txt";
			dirNotes = "User\\" + user.getUsername() + "\\Notes\\" + title + ".txt";
			ofstream writenote(dirNotesTarget.c_str());
			ifstream readnote(dirNotes.c_str());
			while (!readnote.eof())
			{	
				getline(readnote, notas);
				writenote << notas <<endl;
				
			}
			cout << endl;
			//ofstream writenote(dirNotes.c_str() );
			//writenote << notas << endl;
			writenote.close();
			readnote.close();
		}
		
		void deleteNote()
		{
			string tempdirTitle,line;
			dirTitle = "User\\" + user.getUsername() + "\\Notes\\title.txt";
			tempdirTitle = "User\\" + user.getUsername() + "\\Notes\\TEMPtitle.txt";
			dirNotes = "User\\" + user.getUsername() + "\\Notes\\" + title + ".txt";
			ifstream readtitle(dirTitle.c_str());
			ofstream writetemp(tempdirTitle.c_str());
			while(getline(readtitle,line,'|'))
			{
				if(line!=title)
				{
					writetemp << line <<'|';
				}
			}
			readtitle.close();
			writetemp.close();
			
			remove(dirTitle.c_str());
            rename(tempdirTitle.c_str(),dirTitle.c_str());
            remove(dirNotes.c_str());
            
			
		}
};
Notes note;

int main()
{
	_mkdir("User");
	login_page();

}

	void login_page()
	{


		cout << "\n\n\n\t\t\tWelcome to nEVERNOTE ! : " << endl;
		cout << "\n\t\t\t 1 - Log in " << endl;
		cout << "\n\t\t\t 2 - Register New Account " << endl;
		int userselect;
		cin >> userselect;

		if (userselect == 1)
		{
			system("CLS");
			existingUser();
		}
		else if (userselect == 2)
		{
			system("CLS");
			user_create();
		}
		else
		{
			system("CLS");
			login_page();
		}
	}

	void existingUser()
	{
		string username,password;
		
		string dirName, accountdirectory;
		cout << "\n\n\n\t\t\tExisitng user log-in page" << endl;
		cout << "\n\t\t\t Enter Username : ";
		cin >> username;
		cout << "\n\t\t\t Enter Password : ";
		cin >> password;
		
		user.setUsername(username);
		user.setPassword(password);
		if (user.loadUsername() == true )
		{
			mainmenu();
		}
		else
		{
			login_page();
		}
		
		
	}

	void user_create()
	{
		system("cls");
		string dirName, accountdirectory;
		string username, password;
		
		int userselectact;

		cout << "\n\n\n\t\t\tRegistering a new user" << endl;
		cout << "\n\t\t\t Select a username : ";
		cin >> username;
		cout << "\n\t\t\t Select a password : ";
		cin >> password;
		system("cls");
		cout << "\n\t\t\t Please select your account type : " << endl;
		cout << "\n\t\t\t   1 - Free user" << endl;
		cout << "\n\t\t\t   2 - Paid user (RM5 per month)" << endl;
		cin >> userselectact;
		
		user.setUsername(username);
		user.setPassword(password);
		user.setAccounttype(userselectact);
		user.saveUsername();
		
		system("cls");
		login_page();

	}

	void mainmenu()
	{
		system("cls");
		int menuselect;
		cout << "\n\n\n\t\t\t" << user.getUsername() << "'s DASHBOARD" << endl;
		cout << "\n\n\t\t*****************************************" << endl;
		cout << "\t\t\t\tMain Menu" << endl;
		cout << "\t\t*****************************************" << endl;
		cout << "\t\t\t1 - View Notes" << endl;
		cout << "\t\t\t2 - Create new note" << endl;
		cout << "\t\t\t3 - Edit or delete note" << endl;
		cout << "\t\t\t4 - Share Notes" << endl;
		cout << "\t\t\t5 - Log out" << endl;
		cin >> menuselect;
		cin.ignore();
		
		if(menuselect == 1)
		{
			view();
			mainmenu();
		}
		else if (menuselect == 2)
		{
			create_newnote();
			mainmenu();
		}
		else if (menuselect == 3)
		{
			edit_or_delete();
			mainmenu();
		}
		else if (menuselect == 4)
		{
			sharing();
			mainmenu();
		}
		else
		{
			mainmenu();
		}

	}
	
	void create_newnote()
	{
		system("cls");
		string  title,usernote, dirName;
		dirName = "User\\" + user.getUsername() + "\\Notes";
		_mkdir(dirName.c_str());

		cout << "\n\n\n\t\t****************************************************" << endl;
		cout << "\t\t\t\tCreating a new note" << endl;
		cout << "\t\t****************************************************" << endl;
		cout << "\n\t\t Give your note a title : ";
		getline(cin, title);
		note.setTitle(title);

		cout << "\n\t\tNotes : ";
		getline(cin, usernote);
		note.setNote(usernote);
		
		note.saveTitle();
		note.saveNote();
		
		cout<<"\n\n\t\t Note has been sucessfully created !"<<endl<<endl;
		system("pause");
		system("cls");
	}
	
	void view()
	{
		system("cls");
		string title,dirTitle,tajuk;
		string selectedtitle;
		int userselection;
		
			cout << "\n\n\n\t\t****************************************************" << endl;
			cout << "\t\t\t\tViewing saved notes" << endl;
			cout << "\t\t****************************************************" << endl;
			cout << "\n\t\t 1 - View Personal Notes" << endl;
			cout << "\n\t\t 2 - View Shared Notes" <<endl;
			cout << "\n\t\t 3 - View Imported Notes" <<endl;
			cout << "\n\t\t 4 - Back to Main Menu" <<endl;
			cin>>userselection;
			cin.ignore();
			
			if(userselection == 1)
			{
				
			if(note.isExist() == false)
			{
					note.errorpage();
			}
			else
			{
			
			system("cls");
			cout << "\n\n\n\t\t****************************************************" << endl;
			cout << "\t\t\t\tViewing Personal Notes" << endl;
			cout << "\t\t****************************************************" << endl;
			cout << endl;
				
			note.loadTitle();

			cout << "\n\t\t\t Selected Note  : " ;
			getline(cin, title);
			note.setTitle(title);
			if(note.isNoteExist()==false)
			{
				note.errorpage();
			}
			else
			{
				system("cls");
				cout << "\n\n\n\t\t****************************************************" << endl;
				cout << "\t\t\tViewing saved notes :" << title << endl;;
				cout << "\t\t****************************************************" << endl <<endl;;
				note.loadNote();
				
				cout<<endl<<endl<<endl<<endl;
				system("pause");
			}
		    }
			}
		    
		    if(userselection == 2)
		    {
			if(note.isExistShared() == false)
			{
			note.errorpage();
			}
			else
			{   	
		    system("cls");
			cout << "\n\n\n\t\t****************************************************" << endl;
			cout << "\t\t\t\tSelecting Shared Notes" << endl;
			cout << "\t\t****************************************************" << endl;
			cout << endl;
				
			note.loadTitleShared();

			cout << "\n\t\t\t Selected Note  : " ;
			getline(cin, title);
			note.setTitle(title);
			if(note.isNoteExist()==false)
			{
				note.errorpage();
			}
			else
			{
				system("cls");
				cout << "\n\n\n\t\t****************************************************" << endl;
				cout << "\t\t\tViewing Shared notes :" << title << endl;;
				cout << "\t\t****************************************************" << endl <<endl;;
				note.loadNote();
				
				cout<<endl<<endl<<endl<<endl;
				system("pause");
			}
			}
			}
	}
		
	void edit_or_delete()
	{
		system("cls");
		string tajuk,title,notepad;
		int userselection;

		if (note.isExist() == false)
		{
			note.errorpage();
		}

		else
		{
			cout << "\n\n\n\t\t****************************************************" << endl;
			cout << "\t\t\t\tEdit or Delete note" << endl;
			cout << "\t\t****************************************************" << endl;
			cout << "\n\t\t Please make your choice  : " << endl;
			cout << "\t\t\t 1 - I want to Edit my note " << endl;
			cout << "\t\t\t 2 - I want to Delete my note " << endl;
			cout << "\t\t\t 3 - Take me to the main menu !" << endl;

			cin >> userselection;
			cin.ignore();

			if (userselection == 1)
			{
				system("cls");
				cout << "\n\n\n\t\t****************************************************" << endl;
				cout << "\t\t\t\tViewing saved notes" << endl;
				cout << "\t\t****************************************************" << endl;
				cout << "\n\t\t Please TYPE in Note Title to Edit  : " << endl;

				note.loadTitle();

				cout << "\n\t\t\t Selected Note  : ";
				getline(cin, title);
				note.setTitle(title);
				if(note.isNoteExist()==false)
				{
					note.errorpage();
				}
				else
				{
					note.editNote();
				}
			}
			
			if (userselection == 2)
			{
				system("cls");
				cout << "\n\n\n\t****************************************************" << endl;
				cout << "\t\t\t\tViewing saved notes" << endl;
				cout << "\t****************************************************" << endl;
				cout << "\n\t\t Please TYPE in Note Title to DELETE  : " << endl;

				note.loadTitle();

				cout << "\n\t\t\t Selected Note  : ";
				getline(cin, title);
				note.setTitle(title);
				if(note.isNoteExist()==false)
				{
					note.errorpage();
				}
				else
				{
					note.setTitle(title);
					note.deleteNote();
				}
			}
			
		}
	}
	
	void sharing()
	{
		system("cls");
		string title,target,tempnote;
		cout << "\n\n\n\t\t****************************************************" << endl;
		cout << "\t\t\t\tSharing Notes to other user" << endl;
		cout << "\t\t****************************************************" << endl;
		cout << "\n\t\t\tNotes will be shared to target user" << endl;
		
		if(note.isExist()==false)
		{
			note.errorpage();
		}
		else
		{
			note.loadTitle();
			cout << "\n\t\t\tSelect Which notes to share ";
			getline(cin, title);
			note.setTitle(title);
			if(note.isNoteExist()==false)
			{
				note.errorpage();
			}
			else
			{
				cout << "\n\t\t\tUsername of target user : ";
				getline(cin,target);
				if(user.isTargetExist(target)==false)
				{
					user.usererrorpage();
				}
				else
				{
					user.settargetUser(target);
					note.shareNote();
					
					cout<<"\n\n\t\t The note has been sucessfully shared !" <<endl;
				}
			
			}
		}
	}

	void userInfo()
	{
		
	}
