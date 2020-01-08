/**
 * CSC30500 
 * Project1
 * @author Shraddha Belbase
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;
void AddCarinfo();
void AddManu();
void AddDealerinfo();
void ListCars();
void ListDealers();
void FindManu();
void FindZIP();


int main()
{
    bool quit = false;  
    char input;                  
    // Run program until user quits
    while (!quit) {
        // Prompt user input
        cout << ">>> ";
        // Receive input
        cin >> input;
        // Choose action
        switch (input) {
            		//Add
            case 'a':
                // Receive secondary input
                cin >> input;
                // Choose a category to add
                switch (input) {
                 
                    case 'c':
					// Add VIN, miles, dealership and price of cars
                        AddCarinfo();
                        break;
                    case 'm':
					// Add manufacturer and VIN
                        AddManu();
                        break;
                    case 'd':
					// Add Dealer's name, ZIP code and phone number
                        AddDealerinfo();
                        break;
                    
                }
                break;
            		//List
            case 'l':
                // Receive secondary input
                cin >> input;
                // Choose category to list
                switch (input) {
                    case 'c':
                        // Scan list and print results
                          ListCars(); 
                        break;
                    case 'd':
                        // Scan list and print results
                           ListDealers();
                        break;
                }
                break;
            		//Find
            case 'f':
				// Receive secondary input
                cin >> input;
				// Choose Category to Find
                switch(input) {
				    case 'm':
                   	// Scan and print all cars from the manufacturer
					   	    FindManu();
					    break;

                    case 'z':
                    	// Scan and print all available in that ZipCode
							FindZIP();
                        break;
                }
                break;
                
                   //Quit
            case 'q':

                // Signal the program to quit
                quit = true;
                break;
        }
      
    } // End program
      return 0;

}
//------------------------------------  Add CarInformation ------------------------------------------

void AddCarinfo() {
	//Function AddCarinfo
	//Add Car information to the data file

	//Variables for Adding Car Information
	string vin;  
	int miles;	 
	string name;
	int price;
	string VIN;
	
	//Variables for manuinfo.txt file
	string code;  //stores  vin
	string manu;
	
	ofstream car("carinfo.txt", ios::app); //Open datafile
	//Prompt user to input
	cin >> vin;
	cin >> miles;
	cin >> name;
	cin >> price;
	
    VIN = vin;  //Store original VIN
	
	vin.resize(3); //Get the first 3 letters of vin to check
	
	//Boolean to Check manufacturer
	bool Manufact = true;

	ifstream man("manuinfo.txt"); //Read manuinfo.txt datafile

	//Cycle through the data until the end of file
	while (man >> manu >> code) {
		if (code == vin) {
			//If Vin matches
			//Add user input to datafile
				car << VIN << " ";
			 	car<< miles << " ";
			  	car<< name << " ";
			  	car<< price << endl;
			
			car.close(); //Close file
			
			Manufact = false; //Change Manufact to false 
		}

	}
	//Print if manufacture does not exist
	if (Manufact) {
		cout << "Please add the manufacturer first!" << endl;
	}
	
}
//------------------------------------  Add Manufacturer Information ------------------------------------------
void AddManu() {
	//Function AddManu
	//Adds Manufacturer's information in manuinfo.txt datafile

	string vin;   //Variable for VIN
	string manu;	//Variable for manufacturer

	// variables for mandata.txt file
	string Mvin;
	string Mmanu;
	
	ofstream manuf("manuinfo.txt", ios::app);
	//Prompt user input and add it to manuinfo.txt file
	cin >> vin;
	cin >> manu;
	
	//Boolean to Check manufacturer
	bool Manufact = true;
	
	ifstream man("manuinfo.txt");		//Read manuinfo.txt datafile
	
	man >> Mmanu;		//Store the first variable in Mmanu
	//Cycles through the data file
	while (!man.eof())
	{
		//Store the second variable in man
		man >> Mvin;
		
		//Check if manufacturer exists already
		if (manu == Mmanu) {
			cout << "Manufacturer already exists" << endl;
			Manufact = false; //Change Manufact to false 	
			break;
		}
		//Read first variable of next line
		man >> Mmanu;
	}
	//Add new manufacturer
	if (Manufact) {
		manuf << manu << " ";
		manuf << vin << " ";
		manuf << endl;
	}	
	manuf.close(); //close file
}
//------------------------------------  Add Dealer's Information ------------------------------------------
void AddDealerinfo() {
	//Function AddDealer info
	//Adds Dealer's information to dealerinfo.txt datafile

	string name;	//Variable for the name
	int zip;		//Variable for the ZIP
	string phone;		//Variable for the phone number

	// file variabales for dealerdata.txt
	string Dname;
	int Dzip;
	string Dphone;
	
	ofstream dealer("dealerinfo.txt", ios::app);  //Open datafile
	//Prompt user to input
	cin >> name;
	cin >> zip;
	cin >> phone;
	
	//Boolean to check if there is a dealer at the ZIPcode
	bool ZIPCODE = true;
	
	ifstream deal("dealerinfo.txt"); 	//Read dealerinfo.txt datafile
	//Store first variable in deal
	deal >> Dname;

	//Cycles through the datafile
	while (!deal.eof())
	{
		//Store second variable in Dzip
		deal >> Dzip;
		//Store sthird variable in Dphone
		deal >> Dphone;
		
		if (Dname == name) { 
			//If user input dealer is equal to existing dealer 
			if (Dzip == zip) {
				//If both have the same ZIPCode
				cout << "Dealer with the same ZIP code already exists" << endl;
				
				ZIPCODE = false;    //Change ZIPCODE to false
				
				break;
			}
		}
		//Store first value from next line in Dname
		deal >> Dname;
	}
	//Add dealer if it doesn't already exist
	if (ZIPCODE) {
		dealer << name << " ";
		dealer << zip << " ";
		dealer << phone << endl;
	}
	dealer.close();
}
//------------------------------------  List Cars ------------------------------------------
void ListCars() {
	//Function ListCars
	//Lists all the available cars

	ifstream infile("carinfo.txt");   //Read carinfo.txt datafile

	string vin;    
	int miles;
	string name;
	int price;
	
	//Cycles through each line and prints dealers
	while (infile >> vin >> miles >> name >> price) {
		cout << vin << " ";
		cout << miles << " ";
		cout << name << " ";
		cout << price << endl;
	}	
}
//------------------------------------  List Delears ------------------------------------------
void ListDealers() {
	//Function ListDealers
	//Lists all the available Dealers

	ifstream infile("dealerinfo.txt");  //Reads dealerinfo.txt datafile
	
	string name;
	int zip;
	string phone;
	
	//Cycles through each line and prints dealers
	while (infile >> name >> zip >> phone) {
		cout << setw(25) << left << name;
		cout << setw(20) << right << zip << "  ";
		cout << phone << endl;
	}

}

//------------------------------------ Find via manufacturer ------------------------------------------
void FindManu() {
	//Function FindManu
	//Prints car and dealer's information user input Manufacturer
	
	string Fmanu;
	string Fvin;
	cin >> Fmanu;

	// variables for dealerdata.txt file
	string Dname;
	int Dzip;
	string Dphone;

	// variables for cardata1.txt file
	string Cnum;
	string Cvin;
	string Cmiles;
	string Cname;
	string Cprice;

	// variables for manuinfo.txt file
	string manu;
	string vin;
	
	// variables for splting up dealership number
	string phone1;
	string phone2;
	string phone3;

	ifstream man("manuinfo.txt");	//Read manuinfo.txt datafile
	
	//Cycle through the datafile
	while (man >> manu >> vin) {
		//Check if the current manufacturer and user input manufacturer match
		if (manu == Fmanu) {
			Fvin = vin;
		}
	}
	
	ifstream cars("carinfo.txt");		//Read carinfo.txt datafile
	
	//Scans entire  data file
	while (!cars.eof()) {
		while (cars >> Cvin >> Cmiles >> Cname >> Cprice) {
			Cvin.resize(3);  //Get first three letter of Cvin
			if (Cvin == Fvin) {
				//Check if both are equal

				ifstream deal;						//Read dealerinfo.txt datafile
				deal.open("dealerinfo.txt");
				//Cycles through the datafile
				while (deal >> Dname >> Dzip >> Dphone) {
					//Check if the car name matches
					if (Dname == Cname) {
						phone1 = Dphone.substr(0,3);   //Stores the first three digits 
						phone2 = Dphone.substr(3,3);	 //Stores the next three digits
						phone3 = Dphone.substr(6,10);	 //Stores the last four digits
					}
				}
				//Print Output
				cout << Fmanu << ":";
				cout << Cmiles << " miles, ";
				cout<< " $" << Cprice << ": ";
				cout << Cname << "[(" ;
				cout << phone1 << ")";
				cout << phone2 << "-" ;
				cout << phone3<< "]" << endl;
				
			}

		}

	}
}




//------------------------------------  Find via ZIP Code ------------------------------------------
void FindZIP() {
//Function FindZIP
//Prints all the cars in the ZIP code provided
	
	int zip;	
	cin >> zip;	//Prompts User Input

	// variables for reading dealerdata.txt file
	string Dname;
	int Dzip;
	string Dphone;
	
	// variables for reading cardata1.txt file
	string Cvin;
	string Cmiles;
	string Cname;
	string Cprice;

	// variables for reading mandata.txt file
	string manu;
	string vin;
	string Mmanu;  //to store manu
	string Mvin;//to store VIN

	// variables used to split dealer's number
	string phone1;
	string phone2;
	string phone3;
					
	ifstream deal("dealerinfo.txt");		//Read Datafile dealerinfo.txt
		//Scans entire datafile
		while (deal >> Dname >> Dzip >> Dphone) {
			if (Dzip == zip) {
				//Check if the ZIP Code matches with the user input ZIP code
				ifstream cars("carinfo.txt");		//Read carinfo datafile

				while (!cars.eof()) {
					while (cars >> Cvin >> Cmiles >> Cname >> Cprice) {
						//Check if the name matches 
						if (Dname == Cname) {
						phone1 = Dphone.substr(0,3);        //Stores the first three digits
						phone2 = Dphone.substr(3,3);        //Stores the second three digits
						phone3 = Dphone.substr(6,10);       //Stores the lasr four digits
						
						ifstream man("manuinfo.txt");

							 Mvin = Cvin;		//Set Cvin to Mvin to use its value later
							Mvin.resize(3);		//Resize Mvin to get the first three letters			
	
							//Cycle through datafile
							while (man >> manu >> vin) {
								//Check if the vin matches
								if (vin == Mvin) {
									//Set name to manufacturer name
									Mmanu = manu;
								}

							}
				//Print Output
				cout << Mmanu << ":";
				cout << Cmiles << " miles, ";
				cout<< " $" << Cprice << ": ";
				cout << Cname << "[(" ;
				cout << phone1 << ")";
				cout << phone2 << "-" ;
				cout << phone3<< "]" << endl;
						}
						
					}
				
				}
			}
		}
}
//---------------------------------------------------------------------------------------------------