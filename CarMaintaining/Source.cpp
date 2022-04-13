#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

/* Note:::: If there is some Error that System Should Not Allow User Input then Simply Write getchar() before getline() Function*/

/*Registration Information*/
struct Vehicle_Registration {
	string VIN_Number;
	string Car_Make;
	string Car_model;
	int Year_of_build;
	string Registration_number;
	string Owner_Name;
	int Owner_CID;

	void Printcar() {
		cout << "VIN : " << VIN_Number << endl;
		cout << "Make : " << Car_Make << endl;
		cout << "Model : " << Car_model << endl;
		cout << "Year : " << Year_of_build << endl;
		cout << "Registration : " << Registration_number << endl;
		cout << "Owner Name : " << Owner_Name << endl;
		cout << "Owner CID : " << Owner_CID << endl;
	}
};

/*Job Request Struct*/
struct Job_request {
	string VIN_Number;
	string Department;
	string Job_description;
	string Job_status;
	string Date_of_admission;
	string Date_of_release;
	int Total_cost;

	void printJob() {
		cout << "VIN_Number : " << VIN_Number << endl;
		cout << "Department : " << Department << endl;
		cout << "Job_description : " << Job_description << endl;
		cout << "Job_status : " << Job_status << endl;
		cout << "Date_of_admission : " << Date_of_admission << endl;
		cout << "Date_of_release : " << Date_of_release << endl;
		cout << "Total_cost : " << Total_cost << endl << endl << endl;
	}
};


/*Input from Input Stream Command Line*/
Vehicle_Registration getting_input() {
	Vehicle_Registration V;
	getchar();
	cout << "VIN : "; getline(cin, V.VIN_Number);
	cout << "Make : "; getline(cin, V.Car_Make);
	cout << "Model : "; getline(cin, V.Car_model);
	cout << "Year : "; cin >> V.Year_of_build; getchar();
	cout << "Registration Number : "; getline(cin, V.Registration_number);
	cout << "Owner_Name : "; getline(cin, V.Owner_Name);
	cout << "Owner_CID : "; cin >> V.Owner_CID;
	return V;
}

/*Input Job from Main stream Command Line*/
Job_request Input_new_job() {
	Job_request J; getchar();
	cout << "VIN Number : "; getline(cin, J.VIN_Number);
	cout << "Department : "; getline(cin, J.Department);
	cout << "Job_description : "; getline(cin, J.Job_description);
	cout << "Job Status Press (1)-For Open, (2)-for Closed : "; int k = 0; cin >> k; if (k == 1) { J.Job_status = "open"; }
	else { J.Job_status = "closed"; }
	cout << "Date_of_admission : "; getchar(); getline(cin, J.Date_of_admission);
	cout << "Date_of_release : "; getchar(); getline(cin, J.Date_of_release);
	cout << "Cost : "; cin >> J.Total_cost;
	return J;
}
/*Print All information of Cars on Output and its store in DB as well*/
void Print_Registration_detail(Vehicle_Registration V[100], int V_size) {
	for (int i = 0; i < V_size; i++) {
		cout << "VIN : " << V[i].VIN_Number << endl;
		cout << "Make : " << V[i].Car_Make << endl;
		cout << "Model : " << V[i].Car_model << endl;
		cout << "Year : " << V[i].Year_of_build << endl;
		cout << "Registration : " << V[i].Registration_number << endl;
		cout << "Owner Name : " << V[i].Owner_Name << endl;
		cout << "Owner CID : " << V[i].Owner_CID << endl;
	}
}
/*Updating Information*/
void Updating_Information(Vehicle_Registration& V) {
	cout << "What Would You Like to Change ??" << endl;
	cout << "1-VIN\n2-Make\n3-Model\n4-Year\n5-Registration Number\n6-Owner Name\n7-Owner ID\n";
	int k; cin >> k;
	if (k == 1) {
		cout << "VIN : "; getchar(); getline(cin, V.VIN_Number);
	}if (k == 2) {
		cout << "Make : "; getchar(); getline(cin, V.Car_Make);
	}if (k == 3) {
		cout << "Model : "; getchar(); getline(cin, V.Car_model);
	}if (k == 4) {
		cout << "Year : "; cin >> V.Year_of_build;
	}if (k == 5) {
		cout << "Registration Number : "; getchar(); getline(cin, V.Registration_number);
	}if (k == 6) {
		cout << "Owner_Name : "; getchar(); getline(cin, V.Owner_Name);
	}if (k == 7) {
		cout << "Owner_CID : "; cin >> V.Owner_CID;
	}
}
/*Adding New Car*/
void Adding_new_car(Vehicle_Registration V[100], int& V_size) {
	V[V_size] = getting_input();
	V_size++;
}
/*Searching From the Registration Car Array*/
int Search_from_Registration(Vehicle_Registration V[100], string VIN, int size) {
	for (int i = 0; i < size; i++) {
		if (V[i].VIN_Number == VIN) {
			return i;
		}
	}
	return -1;
}

/*Modification of Car*/
void modify_car(Vehicle_Registration V[100], string VIN, int& V_size) {
	int k = Search_from_Registration(V, VIN, V_size);
	if (k == -1) {
		cout << "Car Not Found" << endl;
	}
	else {
		Updating_Information(V[k]);
	}
}

/*It will Search from the list of Job Requests*/
int Search_from_Job_list(vector <Job_request> Job[500], int size, string VIN) {
	for (int i = 0; i < size; i++) {
		Job_request J = Job[i].front();
		if (VIN == J.VIN_Number) {
			return i;
		}
	}
	return -1;
}
/*Print Details of Specific Car with its VIN Number*/
void PrintDetailsofCar(vector <Job_request> Job[500], int size, string VIN, Vehicle_Registration V[100], int V_size) {
	int k = Search_from_Registration(V, VIN, V_size);
	if (k == -1) {
		cout << "No Car Found" << endl;
	}
	else {
		cout << "Car Registration Details:" << endl;
		V[k].Printcar();
		int m = Search_from_Job_list(Job, size, VIN);
		for (int i = 0; i < Job[m].size(); i++) {
			cout << "Job Request - " << i + 1 << endl;
			Job[m][i].printJob();
		}
	}
}
/*Revenue Geneted Function*/
int revenue(vector <Job_request> Job[500], int size) {
	int revenue = 0;
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < Job[i].size(); k++) {
			revenue = revenue + Job[i][k].Total_cost;
		}
	}
	return revenue;
}
/*Open Closed SLots for All Centers*/
void Open_Close_Center(vector <Job_request> Job[500], int size, int& open, int& closed) {
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < Job[i].size(); k++) {
			if (Job[i][k].Job_status == "open") {
				open++;
			}
			else {
				closed++;
			}
		}
	}
}
/*Open Closed SLots for Each Department*/
void Open_Close_Each_Department(vector <Job_request> Job[500], int size, string Department, int& open, int& closed) {
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < Job[i].size(); k++) {
			if (Job[i][k].Department == Department) {
				if (Job[i][k].Job_status == "open") {
					open++;
				}
				else {
					closed++;
				}
			}
		}
	}
}

/*Adding of New Job*/
void Adding_new_job(vector <Job_request> Job[500], int& size) {
	Job_request J = Input_new_job();
	int k = Search_from_Job_list(Job, size, J.VIN_Number);
	if (k == -1) {
		Job[size].push_back(J);
		size++;
	}
	else {
		Job[k].push_back(J);
	}
}
/*Changing Status of Specific Job*/
void Change_status(vector <Job_request> Job[500], int size, string Status) {
	string s;
	cout << "VIN Number : "; getline(cin, s);
	int k = Search_from_Job_list(Job, size, s);
	if (k == -1) {
		cout << "Job Not found" << endl;
	}
	else {
		int n = Job[k].size();
		Job[k][n].Job_status = Status;
	}
}

int main() {
	Vehicle_Registration V[100]; int V_size = 0;
	vector <Job_request> Job[500]; int J_size = 0;
	cout << "Enter No of Cars You want to Add : ";
	int n1; cin >> n1;
	for (int i = 0; i < n1; i++) {
		cout << "Car " << i << " Details" << endl;
		Adding_new_car(V, V_size);
	}
	cout << "Enter No of jobs You want to Add : ";
	int n2; cin >> n2;
	for (int i = 0; i < n2; i++) {
		cout << "Job " << i << " Details" << endl;
		Adding_new_job(Job, J_size);
	}
	int n; int exit = 0;
	while (exit == 0) {
		cout << "1-Add New Car" << endl;
		cout << "2-Modify Car Info" << endl;
		cout << "3- Add Job Request" << endl;
		cout << "5- Show Information of Car and Its Services" << endl;
		cout << "6-Total Revenue" << endl;
		cout << "7- Number of Job Closed and Opened for Whole Center" << endl;
		cout << "8- Number of Job Closed and Opened for Each Department" << endl;
		cout << "9-Exit" << endl;
		cin >> n;
		if (n == 1) {
			Adding_new_car(V, V_size);
			cout << "Addition Car Done" << endl;
		}
		if (n == 2) {
			string Vin; getchar();
			cout << "VIN : "; getline(cin, Vin);
			modify_car(V, Vin, V_size);
			cout << "Modification Done" << endl;
		}
		if (n == 3) {
			Adding_new_job(Job, J_size);
			cout << "Addition Job Done" << endl;
		}
		if (n == 5) {
			string Vin;
			cout << "VIN : "; getchar();
			getline(cin, Vin);
			PrintDetailsofCar(Job, J_size, Vin, V, V_size);

		}
		if (n == 6) {
			cout << "Total Revenue : " << revenue(Job, J_size) << endl;
		}
		if (n == 7) {
			int open = 0, close = 0;
			Open_Close_Center(Job, J_size, open, close);
			cout << "Open : " << open << endl;
			cout << "Close : " << close << endl;
		}
		if (n == 8) {
			int open = 0, close = 0;
			Open_Close_Each_Department(Job, J_size, "express", open, close);
			cout << "Express-Open : " << open << endl;
			cout << "Express-Close : " << close << endl;
			open = 0; close = 0;
			Open_Close_Each_Department(Job, J_size, "major", open, close);
			cout << "Major-Open : " << open << endl;
			cout << "Major-Close : " << close << endl;
			open = 0; close = 0;
			Open_Close_Each_Department(Job, J_size, "crash", open, close);
			cout << "Crash-Open : " << open << endl;
			cout << "Crash-Close : " << close << endl;
		}
		if (n == 9) {
			cout << "Exit From the System" << endl;
			exit = 1;
		}
	}
	system("pause");
}