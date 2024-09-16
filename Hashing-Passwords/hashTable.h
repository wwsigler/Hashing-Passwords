#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
using std::string;

class hashTable
{
	private:

		class entry
		{
		private:
		string uname;
		string salt;
		string passHash;
		public:
		entry* next;

		//constructors
		entry(string u, string s, string pH)
		{
			uname = u;
			salt = s;
			passHash = pH;
			next = NULL;
		}

		// getters
		string getUsername()
		{
			return uname;
		}

		string getSalt()
		{
			return salt;
		}

		string getPassHash()
		{
			return passHash;
		}
		};

		//attributes
		entry** hashArray; // array of entry pointers
		int tableSize; // size of hash table array

		//hash function
		int hash(string);

		//getEntry Function
		entry* getEntry(string key)
		{
			int index = hash(key);
			entry* curr = hashArray[index];

			while(curr != NULL && curr->getUsername() != key)
			{
			curr = curr->next;
			}

			if(curr->getUsername() == key)
			{
				return curr;
			}

		return NULL;
		}



	public:
		
		//constructor
		hashTable(int size);
		


		//destructor
		~hashTable()
		{
			for (int i = 0; i < tableSize; i++)
			{
				entry* curr = hashArray[i];
				while (curr != nullptr)
				{
					entry* temp = curr;
					curr = curr->next;
					delete temp;
				}
				hashArray[i] = nullptr;
			}
			delete[] hashArray;
		}



		//getSalt function - appends salt to a password before it is hashed
		string getSalt(string key)
		{
			entry* user = getEntry(key);
			if (user == nullptr)
			{
				return "";
			}
			else
			{
				return user->getSalt();
			}
		}



		//addEntry function - adds new users to the table
		void addEntry(string username, string salt, string passHash)
		{
			//checks for username
			if (getEntry(username) != nullptr)
			{
				return;
			}

			//dynamic allocation
			entry* newEntry = new entry(username, salt, passHash);

			int bucket = hash(username);
			if (hashArray[bucket] == nullptr)
			{
				hashArray[bucket] = newEntry;
			}
			else
			{
				entry* curr = hashArray[bucket];
				while (curr->next != nullptr)
				{
					curr = curr->next;
				}
				curr->next = newEntry;
			}
		}



		//validateLogin function - checks if user has entered correct login credentials
		bool validateLogin(string username, string passwordHash)
		{
			hashTable::entry* user = getEntry(username);

			//login
			if (!user)
			{
				return false;
			}

			//compares passwords
			if (user->getPassHash() == passwordHash)
			{
				return true;
			}
			else
			{
				return false;
			}
		}



		//removeUser function - removes users from hash table
		bool removeUser(string username, string passwordHash)
		{
			entry* user = getEntry(username);
			if (user == nullptr)
			{
				return false; //user not found
			}

			//checks if password is correct
			if (user->getPassHash() != passwordHash)
			{
				return false; //incorrect password
			}

			//removes user from the hash table
			int bucket = hash(username);
			hashTable::entry* prev = nullptr;
			entry* curr = hashArray[bucket];

			while (curr != nullptr && curr != user)
			{
				prev = curr;
				curr = curr->next;
			}

			if (curr == user)
			{
				if (prev == nullptr)
				{
					hashArray[bucket] = user->next;
				}
				else
				{
					prev->next = user->next;
				}

				delete user;
				return true;
			}
			else
			{
				return false; 
			}
		}


		//generateSalt function
		string generateSalt();

};

#endif


