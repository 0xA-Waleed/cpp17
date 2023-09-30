#include <bits/stdc++.h>
using namespace std;

const int MAX_NUM = 10;

struct book{
	int id, quantity, borrowed_cnt=0;
	string name;
	string borrowed_list[MAX_NUM];
	
	bool check_pre(string pre){
		if(pre.size() > name.size()){
			return false;
		}
		for(int i = 0; i < (int)pre.size(); i++){
			if(pre[i] != name[i]){
				return false;
			}
		}
		return true;
	}
	
	void print(){
		cout << "id " << id << ", name " << name << ", total_quantity " << quantity << ", total_borrowd " << borrowed_cnt << '\n';
	}
};

struct user{
	int id, borrowed_cnt=0;
	string name;
	int borrowed_books[MAX_NUM];
	
	void print(){
		cout << "user " << name << ", id " << id << ", borrowed books ids: ";
		for(int i = 0; i < borrowed_cnt; i++){
			cout << borrowed_books[i] << ' ';
		}
		cout << '\n';
	}
};

int books_cnt, users_cnt;

book books[MAX_NUM];
user users[MAX_NUM];

int menu(){
	int choice = -1;
	while(choice == -1){
		cout << "Library Menu: \n";
		cout << "1) add_book\n";
		cout << "2) search_books_by_prefix\n";
		cout << "3) print_who_borrowed_book_by_name\n";
		cout << "4) print_library_by_id\n";
		cout << "5) print_library_by_name\n";
		cout << "6) add_user\n";
		cout << "7) user_borrow_book\n";
		cout << "8) user_return_book\n";
		cout << "9) print_users\n";
		cout << "10) Exit\n";
		cin >> choice;
		if(choice < 1 || choice > 10){
			cout << "Invalid choice..\n\n";
			choice = -1;
		}
	}
	return choice;
}

void add_book(){
	if(books_cnt == MAX_NUM){
		cout << "Sorry, can't add more books\n";
	}else{
		int id,quan;
		string name;
		cout << "Enter book info: id & name & total quantity: ";
		cin >> id >> name >> quan;
		books[books_cnt].id = id;
		books[books_cnt].name = name;
		books[books_cnt].quantity = quan;
		books_cnt++;
	}
	cout << '\n';
}

void search_by_pre(){	
	string pre;
	cout << "Enter the book name prefix: ";
	cin >> pre;
	for(int i = 0; i < books_cnt; i++){
 		if(books[i].check_pre(pre)){
			cout << books[i].name << '\n';
		}
	}
}

void who_borrowed(){
	bool found = false;
	string name;
	cout << "Enter book name: ";
	cin >> name;
	cout << '\n';
	for(int i = 0; i < books_cnt; i++){
		if(books[i].name == name){
			for(int j = 0; j < books[i].borrowed_cnt; j++){
				cout << books[i].borrowed_list[j] << '\n';
			}
			found = true;
			break;
		}
	}
	if(!found){
		cout << "Sorry, can't find any book with this name\n";
	}
}

int search_book(string name){
	int res = -1;
	for(int i = 0; i < books_cnt; i++){
		if(books[i].name == name){
			res = i;
			break;
		}
	}
	return res;
}

int search_user(string name){
	int res = -1;
	for(int i = 0; i < users_cnt; i++){
		if(users[i].name == name){
			res = i;
			break;
		}
	}
	return res;
}

void borrow_book(){
	string user_name, book_name;
	cout << "Enter the user name & book name: ";
	cin >> user_name >> book_name;
	int user_idx = search_user(user_name), book_idx =  search_book(book_name);
	if(user_idx == -1 || book_idx == -1){
		cout << "Invalid input data..\n";
	}else if(books[book_idx].quantity == books[book_idx].borrowed_cnt){
		cout << "sorry, there is no more copies at the moment\n";
	}else{
		books[book_idx].borrowed_list[books[book_idx].borrowed_cnt] = user_name;
		books[book_idx].borrowed_cnt++;
		users[user_idx].borrowed_books[users[user_idx].borrowed_cnt] = book_idx;
		users[user_idx].borrowed_cnt++;
	}
}

void return_book(){
	string user_name, book_name;
	cout << "Enter the user name & book name: ";
	cin >> user_name >> book_name;
	int user_idx = search_user(user_name), book_idx =  search_book(book_name);
	if(user_idx == -1 || book_idx == -1){
		cout << "Invalid input data..\n";
	}else{
		books[book_idx].borrowed_cnt--;
		users[user_idx].borrowed_cnt--;
	}
}

void add_user(){
	if(users_cnt == MAX_NUM){
		cout << "Sorry, can't add more users\n";
	}else{
		int id;
		string name;
		cout << "Enter user info: name & national_id: ";
		cin >> name >> id;
		users[users_cnt].name = name;
		users[users_cnt].id = id;
		users_cnt++;
	}
	cout << '\n';
}

void print_users(){
	for(int i = 0; i < users_cnt; i++){
		users[i].print();
	}
}

bool sort_name(book &a, book &b){
	return a.name < b.name;
}

bool sort_id(book &a, book &b){
	return a.id < b.id;
}

void print_books(){
	for(int i = 0; i < books_cnt; i++){
		books[i].print();
	}
}

int main(){
	freopen("c.in", "rt", stdin);
	
	while(true){
		int choice = menu();
		if(choice == 1){
			if(books_cnt == MAX_NUM){
				cout << "Sorry, can't add more books\n";
			}else{
				add_book();
			}
		}else if(choice == 2){
			search_by_pre();
		}else if(choice == 3){
			who_borrowed();
		}else if(choice == 4){
			sort(books,books+books_cnt,sort_id);
			print_books();
		}else if(choice == 5){
			sort(books,books+books_cnt,sort_id);
			print_books();
		}else if(choice == 6){
			add_user();
		}else if(choice == 7){
			borrow_book();
		}else if(choice == 8){
			return_book();
		}else if(choice == 9){
			print_users();
		}else{
			break;
		}
		cout << '\n';
	}
	return 0;
}
