#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

/* Note:::: If there is some Error that System Should Not Allow User Input then Simply Write getchar() before getline() Function*/
struct Vehicle_Registration {// Vehicle registration structure
	string VIN_Number;
	string Car_Make;
	string Car_model;
	int Year_of_build;
	string Registration_number;
	string Owner_Name;
	int Owner_CID;
	//printer function
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

void Print_Registration_detail(Vehicle_Registration V[100], int V_size) {// to print vehicle registration details
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

//read data from registration-info.txt
void Registration_Input_from_file(Vehicle_Registration V[100], int& V_size) {
	ifstream myfile;
	myfile.open("registration-info.txt");
	myfile.ignore(51);
	int s;
	while (!myfile.eof()) {
		getline(myfile, V[V_size].VIN_Number, ',');
		getline(myfile, V[V_size].Car_Make, ',');
		getline(myfile, V[V_size].Car_model, ',');
		myfile >> V[V_size].Year_of_build; myfile.ignore();
		getline(myfile, V[V_size].Registration_number, ',');
		getline(myfile, V[V_size].Owner_Name, ',');
		myfile >> V[V_size].Owner_CID; myfile.ignore(); myfile.ignore();
		V_size++;
	}
	myfile.close();
}
// get registration input from the terminal/ from user
Vehicle_Registration getting_input() {
	Vehicle_Registration V;
	cout << "VIN : "; getline(cin, V.VIN_Number);
	cout << "Make : "; getline(cin, V.Car_Make);
	cout << "Model : "; getline(cin, V.Car_model);
	cout << "Year : "; cin >> V.Year_of_build;
	cout << "Registration Number : "; getline(cin, V.Registration_number);
	cout << "Owner_Name : "; getline(cin, V.Owner_Name);
	cout << "Owner_CID : "; cin >> V.Owner_CID;
	return V;
}
// updating the information in vheicle registartion
void Updating_Information(Vehicle_Registration& V) {
	cout << "What Would You Like to Change ??" << endl;
	cout << "1-VIN\n2-Make\n3-Model\n4-Year\n5-Registration Number\n6-Owner Name\n7-Owner ID\n";
	int k; cin >> k;
	if (k == 1) {
		cout << "VIN : "; getline(cin, V.VIN_Number);
	}if (k == 2) {
		cout << "Make : "; getline(cin, V.Car_Make);
	}if (k == 3) {
		cout << "Model : "; getline(cin, V.Car_model);
	}if (k == 4) {
		cout << "Year : "; cin >> V.Year_of_build;
	}if (k == 5) {
		cout << "Registration Number : "; getline(cin, V.Registration_number);
	}if (k == 6) {
		cout << "Owner_Name : "; getline(cin, V.Owner_Name);
	}if (k == 7) {
		cout << "Owner_CID : "; cin >> V.Owner_CID;
	}
}

// adding new car registration in our data
void Adding_new_car(Vehicle_Registration V[100], int& V_size) {
	V[V_size] = getting_input();
	V_size++;
}
// for searching of a particular vehicle
int Search_from_Registration(Vehicle_Registration V[100], string VIN, int size) {
	for (int i = 0; i < size; i++) {
		if (V[i].VIN_Number == VIN) {
			return i;
		}
	}
	return -1;
}

// for the modification of a car
void modify_car(Vehicle_Registration V[100], string VIN, int& V_size) {
	int k = Search_from_Registration(V, VIN, V_size);
	if (k == -1) {
		cout << "Car Not Found" << endl;
	}
	else {
		Updating_Information(V[k]);
	}
}


struct Job_request {// data struct designed for a jib request
	string VIN_Number;
	string Department;
	string Job_description;
	string Job_status;
	string Date_of_admission;
	string Date_of_release;
	int Total_cost;
	// for printing of a designated job
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

//search fucntion for jobs
int Search_from_Job_list(vector <Job_request> Job[500], int size, string VIN) {
	for (int i = 0; i < size; i++) {
		Job_request J = Job[i].front();
		if (VIN == J.VIN_Number) {
			return i;
		}
	}
	return -1;
}
// prinitng job request for a car
void PrintDetailsofCar(vector <Job_request> Job[500], int size, string VIN, Vehicle_Registration V[100], int V_size) {
	int k = Search_from_Registration(V, VIN, V_size);
	if (k == -1) {//Null case
		cout << "No Car Found" << endl;
	}
	else {//not null case
		cout << "Car Registration Details:" << endl;
		V[k].Printcar();
		int m = Search_from_Job_list(Job, size, VIN);
		for (int i = 0; i < Job[m].size(); i++) {
			cout << "Job Request - " << i + 1 << endl;
			Job[m][i].printJob();
		}
	}
}
// print car details
void PrintDetailsofCarinfile(vector <Job_request> Job[500], int size, string VIN, Vehicle_Registration V[100], int V_size) {
	ofstream myfile;
	myfile.open("car-info.txt");//car txt file
	int k = Search_from_Registration(V, VIN, V_size);
	if (k == -1) {//Null case
		cout << "No Car Found" << endl;
		myfile << "No Car Found" << endl;
		myfile.close();
	}
	else {//not null case
		myfile << "Car Registration Details:" << endl;
		myfile << "VIN number,make,model,year,registration,owner,CID,\n";
		myfile << V[k].VIN_Number << "," << V[k].Car_Make << "," << V[k].Car_model << "," << V[k].Year_of_build << "," << V[k].Registration_number << "," << V[k].Owner_Name << "," << V[k].Owner_CID << ",\n\n\n";
		int m = Search_from_Job_list(Job, size, VIN);
		myfile << "VIN number,Department,Job Description,Status,Addmission date,Release date,Cost,\n";
		for (int i = 0; i < Job[m].size(); i++) {
			myfile << "Job Request - " << i + 1 << endl;
			myfile << Job[m][i].VIN_Number << "," << Job[m][i].Department << "," << Job[m][i].Job_description << "," << Job[m][i].Job_status << "," << Job[m][i].Date_of_admission << "," << Job[m][i].Date_of_release << "," << Job[m][i].Total_cost << ",\n";
		}
		myfile.close();//close file
	}

}
//get input for a job form the job-info.txt
void Job_Input_from_file(vector <Job_request> Job[500], int& size) {
	ifstream myfile;
	myfile.open("job-info.txt");
	myfile.ignore(80);
	string s;
	while (!myfile.eof()) {
		Job_request J;
		getline(myfile, J.VIN_Number, ',');
		getline(myfile, J.Department, ',');
		getline(myfile, J.Job_description, ',');
		getline(myfile, J.Job_status, ',');
		getline(myfile, J.Date_of_admission, ',');
		getline(myfile, J.Date_of_release, ',');
		myfile >> J.Total_cost; myfile.ignore(2);
		int k = Search_from_Job_list(Job, size, J.VIN_Number);
		if (k == -1) {
			Job[size].push_back(J);
			size++;
		}
		else {
			Job[k].push_back(J);
		}
	}
	size--;
	myfile.close();
}
// return revenue from all the jobs done
int revenue(vector <Job_request> Job[500], int size) {
	int revenue = 0;
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < Job[i].size(); k++) {
			revenue = revenue + Job[i][k].Total_cost;
		}
	}
	return revenue;
}
// this function changes the job job status
// either the job is open or close and count of both types
void Open_Close_Center(vector <Job_request> Job[500], int size, int& open, int& closed) {
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < Job[i].size(); k++) {
			if (Job[i][k].Job_status == "open") {//check prior status
				open++;
			}
			else {
				closed++;
			}
		}
	}
}
// change the status for each department either opoen or close
//maintains the count for each category
void Open_Close_Each_Department(vector <Job_request> Job[500], int size, string Department, int& open, int& closed) {
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < Job[i].size(); k++) {
			if (Job[i][k].Department == Department) {//check existance
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

//input new job from user / terminal
Job_request Input_new_job() {
	Job_request J;
	cout << "VIN Number : "; getline(cin, J.VIN_Number);
	cout << "Department : "; getline(cin, J.Department);
	cout << "Job_description : "; getline(cin, J.Job_description);
	cout << "Job Status : "; getline(cin, J.Job_status);
	cout << "Date_of_admission : "; getline(cin, J.Date_of_admission);
	cout << "Date_of_release : "; getline(cin, J.Date_of_release);
	cout << "Cost : "; cin >> J.Total_cost;
	return J;
}
// add new jib into our record
void Adding_new_job(vector <Job_request> Job[500], int& size) {
	Job_request J = Input_new_job();//use the termianl fucn
	int k = Search_from_Job_list(Job, size, J.VIN_Number);// search for prior existance
	if (k == -1) {
		Job[size].push_back(J);
		size++;
	}
	else {
		Job[k].push_back(J);
	}
}

//change job status
void Change_status(vector <Job_request> Job[500], int size, string Status) {
	string s;
	cout << "VIN Number : "; getline(cin, s);//take input from user
	int k = Search_from_Job_list(Job, size, s);//search in data
	if (k == -1) {//Null case
		cout << "Job Not found" << endl;
	}
	else {//not null 
		int n = Job[k].size();
		Job[k][n].Job_status = Status;
	}
}
//write back into the files i.e. all the updated data
void Output_to_the_files(vector <Job_request> Job[500], int size, string VIN, Vehicle_Registration V[100], int V_size) {
	ofstream myfile, myfile1;
	myfile.open("registration-info.txt");
	myfile1.open("job-info.txt");
	myfile << "VIN number,make,model,year,registration,owner,CID,\n";
	//registrations txt
	for (int i = 0; i < V_size; i++) {
		myfile << V[i].VIN_Number << "," << V[i].Car_Make << "," << V[i].Car_model << "," << V[i].Year_of_build << "," << V[i].Registration_number << "," << V[i].Owner_Name << "," << V[i].Owner_CID << ",\n";
	}
	myfile.close();//first file closed
	myfile1 << "VIN number,Department,Job Description,Status,Addmission date,Release date,Cost,\n";
	//job info txt
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < Job[i].size(); k++) {
			myfile1 << Job[i][k].VIN_Number << "," << Job[i][k].Department << "," << Job[i][k].Job_description << "," << Job[i][k].Job_status << "," << Job[i][k].Date_of_admission << "," << Job[i][k].Date_of_release << "," << Job[i][k].Total_cost << ",\n";
		}
	}
	myfile1.close();//2nd file closed
}


int main() {
	Vehicle_Registration V[100]; int V_size = 0;//intial multidimensional registarion record
	vector <Job_request> Job[500]; int J_size = 0;//2D jobs 
	Registration_Input_from_file(V, V_size);//input
	Job_Input_from_file(Job, J_size);//input from files i.e. local data in txt files
	int n;
	while (true) {// dispaly files
		cout << "1-Add New Car" << endl;
		cout << "2-Modify Car Info" << endl;
		cout << "3- Add Job Request" << endl;
		cout << "4- Change Job Status" << endl;
		cout << "5- Show Information of Car and Its Services" << endl;
		cout << "6-Total Revenue" << endl;
		cout << "7- Number of Job Closed and Opened for Whole Center" << endl;
		cout << "8- Number of Job Closed and Opened for Each Department" << endl;
		cout << "9- write Information of Car and Its Services in File" << endl;
		cin >> n;
		if (n == 1) {//add car for 1
			Adding_new_car(V, V_size);
			cout << "Addition Car Done" << endl;
		}
		if (n == 2) {//modify for 2
			string Vin;
			cout << "VIN : "; getline(cin, Vin);
			modify_car(V, Vin, V_size);
			cout << "Modification Done" << endl;
		}
		if (n == 3) {// add job for 3
			Adding_new_job(Job, J_size);
			cout << "Addition Job Done" << endl;
		}
		if (n == 4) {//modify car 
			string status;
			cout << "status : "; getline(cin, status);
			modify_car(V, status, V_size);
			Change_status(Job, J_size, status);
			cout << "Status Updated" << endl;
		}
		if (n == 5) {//print car details
			string Vin;
			cout << "VIN : "; getchar();
			getline(cin, Vin);
			PrintDetailsofCar(Job, J_size, Vin, V, V_size);

		}
		if (n == 6) {//get revenue
			cout << "Total Revenue : " << revenue(Job, J_size) << endl;
		}
		if (n == 7) {//change status
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
			Open_Close_Each_Department(Job, J_size, "major", open, close);
			cout << "Major-Open : " << open << endl;
			cout << "Major-Close : " << close << endl;
			Open_Close_Each_Department(Job, J_size, "crash", open, close);
			cout << "Crash-Open : " << open << endl;
			cout << "Crash-Close : " << close << endl;
		}
		if (n == 9) {//print car details
			string Vin;
			cout << "VIN : "; getchar(); getline(cin, Vin);
			PrintDetailsofCarinfile(Job, J_size, Vin, V, V_size);
			cout << "Printed Successfully" << endl;
		}
	}
	system("pause");
}