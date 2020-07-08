#include "pch.h"
#include<iostream>
#include<string>
#include<list>
#include<iterator>
#include<fstream>
#include<stdlib.h>
#include<sstream>
#include<stdio.h>
#include<vector>
#include<map>

using namespace std;

class PostImplementation
{
	private:

		int num; 
		string id; 
		string post_provider; 
		string message;

	public:

		PostImplementation() {};

		PostImplementation(int num, string id, string post_provider, string message)
		{
			this->num=num;
			this->id=id;
			this->post_provider=post_provider;
			this->message=message;
		}

		PostImplementation(string email)
		{ 
			stringstream string_stream(email);
			string delimiter=":=";
			vector<string>tokens;
			string intermediate;
			size_t size=0;
			string token;

			if(getline(string_stream, intermediate, '-')) tokens.push_back(intermediate);
			if(getline(string_stream, intermediate, '@')) tokens.push_back(intermediate);
			if(getline(string_stream, intermediate, ':')) tokens.push_back(intermediate);

			while((size=email.find(delimiter))!=string::npos)
			{
				token=email.substr(0, size);
				email.erase(0, size+delimiter.length());
			}

			tokens.push_back(email);
			num=atoi(tokens[0].c_str());
			id=tokens[1];
			post_provider=tokens[2];
			message=tokens[3];
		}

		void print_post_implementation() { cout<<num<<"-"<<id<<"@"<<post_provider<<":="<<message<<endl; }

		int get_num() { return num; }
		string get_id() { return id; }
		string get_post_provider() { return post_provider; }
		string get_message() { return message; }

		int set_num(int num) { this->num=num; }
		string set_str_id(string id) { this->id=id; }
		string set_str_post_provider(string post_provider) { this->post_provider=post_provider; }
		string set_str_message(string message) { this->message=message; }

		void set_print_post_implementation(string num, string str_id, string str_post_provider, string str_message)
		{
			this->num=atoi(num.c_str());
			this->id=str_id;
			this->post_provider=str_post_provider;
			this->message=str_message;
		}

		friend istream &operator >>(istream &input, PostImplementation& post_implementation)
		{
			input>>post_implementation.num
				 >>post_implementation.id
				 >>post_implementation.post_provider
				 >>post_implementation.message;
			return input;
		}

		friend ostream &operator <<(ostream &output, const PostImplementation& post_implementation)
		{
			output<<"Name: "<<post_implementation.num<<endl
				  <<"Id: "<<post_implementation.id<<endl
				  <<"PostProvider: "<<post_implementation.post_provider<<endl
				  <<"Message: "<<post_implementation.message<<endl<<endl;
			return output;
		}

		bool operator ==(const PostImplementation& post_implementation) { if(num==post_implementation.num) return true; }

		bool operator >(const PostImplementation& post_implementation)
		{ 
			if(num>post_implementation.num) return true;
			else return false; 
		}

		bool operator <(const PostImplementation& post_implementation)
		{ 
			if(num<post_implementation.num) return true;
			else return false; 
		}
};

class PostBox: public PostImplementation
{
	private:

		list<PostImplementation*>list_post_implementation;

	public:

		PostBox(const string& file)
		{
			ifstream myfile(file.c_str()); 
			string line;

			if(myfile.is_open())
			{
				while(getline(myfile, line)) 
				{
					PostImplementation *post_implementation=new PostImplementation(line);
					list_post_implementation.push_back(post_implementation);
				}
				myfile.close();
			}

			else 
			{ 
				cout<<"Problem, check name or file destination!"<<endl;
				system("pause");
			}
		}

		PostBox(const PostBox& post_box) { list_post_implementation=post_box.list_post_implementation; }

		void print_post_box()
		{
			for(list<PostImplementation*>::iterator iterator=list_post_implementation.begin(); iterator!=list_post_implementation.end(); iterator++)
			cout<<(*iterator)->get_num()
				<<"-"<<(*iterator)->get_id()
				<<"@"<<(*iterator)->get_post_provider()
				<<":="<<(*iterator)->get_message()<<endl;
		}

		struct num{ bool operator ()( PostImplementation *post_implementation, PostImplementation *post_implementation1)
		{ return post_implementation->get_num()<post_implementation1->get_num(); } };

		struct id{ bool operator ()( PostImplementation *post_implementation, PostImplementation *post_implementation1)
		{ return post_implementation->get_id()<post_implementation1->get_id(); } };

		struct post_provider{ bool operator ()( PostImplementation *post_implementation, PostImplementation *post_implementation1)
		{ return post_implementation->get_post_provider()<post_implementation1->get_post_provider(); } };

		struct message{ bool operator ()( PostImplementation *post_implementation, PostImplementation *post_implementation1)
		{ return post_implementation->get_message()<post_implementation1->get_message(); } };

		void sort_num()
		{
			list_post_implementation.sort(num());
			cout<<endl;
		}

		void sort_id()
		{
			list_post_implementation.sort(id());
			cout<<endl;
		}

		void sort_post_provider()
		{
			list_post_implementation.sort(post_provider());
			cout<<endl;
		}

		void sort_message()
		{
			list_post_implementation.sort(message());
			cout<<endl;
		}

		void to_map()
		{
			vector<string>vector_post_implementation;

			for(list<PostImplementation*>::iterator iterator=list_post_implementation.begin(); iterator!=list_post_implementation.end(); iterator++)
			{ vector_post_implementation.push_back((*iterator)->get_post_provider()); }

			cout<<endl;
			std::map<string, int>map_post_implementation;

			for(vector<string>::iterator iterator=vector_post_implementation.begin(); iterator!=vector_post_implementation.end(); iterator++)
			{
				if(map_post_implementation.find(*iterator)!=map_post_implementation.end()) { map_post_implementation[*iterator]++; }
				else { map_post_implementation[*iterator]=1; }
			}

			for(std::map<string, int>::const_iterator iterator=map_post_implementation.begin(); iterator!=map_post_implementation.end(); ++iterator)
			{
				if(iterator->second>1)
					cout<<iterator->first
						<<" with "
						<<iterator->second
						<< " users"<<endl;

				else cout<<iterator->first
						<<" with "
						<<iterator->second
						<< " users"<<endl;
			}
			cout<<endl;
		}

		friend ostream &operator <<(ostream &output, const PostBox& post_box)
		{
			list<PostImplementation*>list_post_implementation1=post_box.list_post_implementation;
			for(list<PostImplementation*>::iterator iterator=list_post_implementation1.begin(); iterator!=list_post_implementation1.end(); iterator++)
				output<<(*iterator)->get_num()
					<<"-"<<(*iterator)->get_id()
					<<"@"<<(*iterator)->get_post_provider()
					<<":="<<(*iterator)->get_message()<<endl;
			return output;
		}

		friend istream &operator >>(istream &input, PostBox& post_box)
		{
			list<PostImplementation*>list_post_implementation1;
			int number_of_elements;
			cout<<"How many elements you want to add?: ";
			cin>>number_of_elements;
			list_post_implementation1.resize(number_of_elements);
			int num;
			string id;
			string post_provider;
			string message;

			for(list<PostImplementation*>::iterator iterator=list_post_implementation1.begin(); iterator!=list_post_implementation1.end(); iterator++)
			{
				cout<<"Enter number: "; 
				input>>num;

				cout<<"Enter Id: "; 
				input>>id;

				cout<<"Enter PostProvider: "; 
				input>>post_provider;

				cout<<"Enter Message: "; 
				input>>message;

				(*iterator)=new PostImplementation(num, id, post_provider, message);
				post_box.list_post_implementation.push_back(*iterator);
				cout<<endl;
			}

			return input;
		}
};

int main(void)
{
	PostBox post_box("text.txt");
	post_box.print_post_box();
	post_box.sort_post_provider();
	post_box.print_post_box();
	post_box.to_map();
	system("pause");
}