#include<bits/stdc++.h>
using namespace std;

string names[21][5];
int status[21][5];
int cnt[21];

int menu(){
	int choice = -1;
	while(choice == -1){
		cout << "Enter your choice: \n";
		cout << "1) Add new patient\n";
		cout << "2) Print all patients\n";
		cout << "3) Get next patient\n";
		cout << "4) Exit\n";
		cin >> choice;
		if(choice < 1 || choice > 4){
			choice = -1;
		}
	}
	return choice;
}

void shift_right(int spec){
	int pos = cnt[spec];
	pos--;
	for(int i = pos; i >= 0; i--){
		names[spec][i+1] = names[spec][i];
		status[spec][i+1] = status[spec][i];
	}
}

void shift_left(int spec){
	for(int i = 0; i < cnt[spec]; i++){
		names[spec][i] = names[spec][i+1];
		status[spec][i] = status[spec][i+1];
	}	
}

void add_patient(){
	int specialization,stat,spec_cnt;
	string name;
	cout << "Enter specialization, name, status: ";
	cin >> specialization >> name >> stat;
	if(specialization < 1 || specialization > 20 || (stat != 0 && stat != 1)){
		cout << "Invalid input..\n\n";
		add_patient();
	}
	spec_cnt = cnt[specialization];
	if(spec_cnt == 5){
		cout << "Sorry we can't add more patients to this specialization\n\n";
	}
	if(stat == 0){
		names[specialization][spec_cnt] = name;
		status[specialization][spec_cnt] = stat;
	}else{
		shift_right(specialization);
		names[specialization][0] = name;
		status[specialization][0] = stat;
	}
	cnt[specialization]++;
};

void print_patients(){
	for(int i = 0; i < 20; i++){
		if(cnt[i] > 0){
			cout << "There are " << cnt[i] << " patients in specialization " << i << '\n';
			for(int j = 0; j < cnt[i]; j++){
				cout << names[i][j];
				if(status[i][j] == 0){
					cout << ", regular\n";
				}else{
					cout << ", urgent\n";
				}
			}
		}
	}	
}

void get_next(){
	int specialization, spec_cnt;
	cout << "Enter specialization number: ";
	cin >> specialization;
	if(specialization < 1 || specialization > 20){
		cout << "Invalid specialization number..\n\n";
		get_next();
	}
	spec_cnt = cnt[specialization];
	if(spec_cnt == 0){
		cout << "No patients at the moment.\n\n";
	}else{
		cout << names[specialization][0] << " please go with the Dr\n\n";
		shift_left(specialization);
		cnt[specialization]--;
	}
}

int main(){
	while(true){
		int choice = menu();
		if(choice == 1){
			add_patient();
		}else if(choice == 2){
			print_patients();
		}else if(choice == 3){
			get_next();
		}else if(choice == 4){
			break;
		}
	}
	
	return 0;
}
