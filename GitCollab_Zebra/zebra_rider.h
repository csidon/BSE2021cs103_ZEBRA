#ifndef ZEBRA_RIDER_H
#define ZEBRA_RIDER_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

//Coder: Chris C
//File: zebra_rider.cpp
//Edited on: 3 Nov 2021
//Last Edited Date:  3 Nov 2021
//Purpose: This file contains all functions specific to the rider

struct Rider_pid
{
	string r_fname, r_pname, r_lname, r_address, r_emailusrname, r_pswd, r_idalpha, r_defaultloc, r_cardholder_name, r_card_num, r_card_type, r_header_contact, r_headeridnum, r_headerexpiry, r_headercvv;
	int r_contact, r_idnum, r_expiry, r_cvv;

	//constructor
	Rider_pid(string rdl = "", string rfn = "", string rpn = "", string rln = "", string rad = "", string reu = "", string rpw = "", string ida = "", string rccn = "", string rccnum = "", string ct = "", string rhc = "", string rhi = "", string rhe = "", string rhcvv = "", int cex = 0, int cvv = 0, int idn = 0, int rcall = 0)
	{
		r_defaultloc = rdl;
		r_fname = rfn;
		r_lname = rln;
		r_pname = rpn;
		r_address = rad;
		r_emailusrname = reu;
		r_pswd = rpw;
		r_idalpha = ida;
		r_contact = rcall;
		r_idnum = idn;
		//payment specific vars
		r_card_type = ct;
		r_cardholder_name = rccn;
		r_card_num = rccnum;
		r_expiry = cex;
		r_cvv = cvv;
		//header specific vars
		r_header_contact = rhc;
		r_headeridnum = rhi;
		r_headerexpiry = rhe;
		r_headercvv = rhcvv;

	}
};

struct Rider_AllRidesInfo
{
	string rr_UIDalpha, rr_pname, rr_defaultloc, rr_startloc, rr_endloc, rr_pay_avail, rr_tripIDa;
	int rr_UIDnum, rr_tripCost, rr_gst, rr_netTripRevenue, rr_tripIDn;

	//Constructor
	Rider_AllRidesInfo(string uida = "", string rpn = "", string rdl = "", string rsl = "", string rel = "", string pay = "", int uidn = 0, int tc = 0, int gst = 0, int ntr = 0, string tida = "", int tidn = 0)
	{
		rr_tripIDa = tida;
		rr_tripIDn = tidn;
		rr_UIDalpha = uida;
		rr_pname = rpn;
		rr_defaultloc = rdl;
		rr_endloc = rel;
		rr_UIDnum = uidn;
		rr_tripCost = tc;
		rr_gst = gst;
		rr_netTripRevenue = ntr;
		rr_pay_avail = pay;
	}
};

//struct Location_ListNode
//{
//	string location_nodeData;
//	struct Location_ListNode* next;
//}*head;
//
//void location_nodesAvailable()
//{
//	Location_ListNode* head = nullptr;
//	//First location node, Brooklyn
//	head = new Location_ListNode;
//	head->location_nodeData = "BROOKLYN";
//	head->next = nullptr;
//
//	Location_ListNode* secondPtr = new Location_ListNode;
//	secondPtr->location_nodeData = "HAITAITAI";
//	head->next = secondPtr;
//
//	Location_ListNode* thirdPtr = new Location_ListNode;
//	thirdPtr->location_nodeData = "ARO VALLEY";
//	head->next = thirdPtr;
//
//	Location_ListNode* fourthPtr = new Location_ListNode;
//	fourthPtr->location_nodeData = "KELBURN";
//	head->next = fourthPtr;
//
//	Location_ListNode* fifthPtr = new Location_ListNode;
//	fifthPtr->location_nodeData = "MOUNT COOK";
//	head->next = fifthPtr;
//
//	Location_ListNode* sixthPtr = new Location_ListNode;
//	sixthPtr->location_nodeData = "TE ARO";
//	head->next = sixthPtr;
//}

//void insertLocationNodeAtEnd(string location_nodeData)
//{
//	struct Location_ListNode* newLocationNode, * temp;
//	newLocationNode = (struct Location_ListNode*)malloc(sizeof(struct Location_ListNode));
//	if (newLocationNode == NULL)
//	{
//		cout << "\nDEBUG: Unable to allocate memory.";
//	}
//	else
//	{
//		newLocationNode->location_nodeData = location_nodeData;
//		newLocationNode->next = NULL;
//		temp = head;
//		while (temp != NULL && temp->next != NULL)
//			temp = temp->next;
//		temp->next = newLocationNode;
//		cout << "\nDEBUG: Location inserted successfully!";
//	}
//}
//void displayList()
//{
//	struct node* temp;
//	if (head == NULL)
//	{
//		cout << "\nDEBUG: No locations registered, list empty";
//	}
//	else
//	{
//		temp = head;
//		while (temp != NULL)
//		{
//			cout << ""
//		}
//	}
//}

//##################################
//  Rider Main function prototypes
//**********************************
int count_entries();
int rider_main();

// Option 1: Rider login
Rider_pid r_login(vector <Rider_pid> read_from_file);
Rider_pid pay_details(Rider_pid& passed_pid_details);

// Option 2: Rider registration
Rider_pid rider_register();
void writeRiderToFile(Rider_pid write_r);

// Option 3: Forgot Password
vector<Rider_pid> pswd_reset(vector <Rider_pid> read_from_file);

//**************************************
//  Rider logged in function prototypes
//**************************************
void r_loggedIn_home(Rider_pid& userInfo);

//Location translates user's int input to location string so that distance can be calculated
string location_translate(int user_input);		

//------------------------------------------------------------------------------------------------------------
//   Rider Booking-specific functions
// 
//Initiates a ride booking process when given riderpid structure, allrides information structure, and cost
void book_ride(Rider_pid userPIDInfo, Rider_AllRidesInfo userRidesInfo, double cost);

//Shows available destination options after removing the pickup options from selection
string show_destination_options(Rider_AllRidesInfo rideInfo, int userInput);

//Displays all locations available for user to select
string show_pickup_options(Rider_AllRidesInfo rideInfo, int userInput);

//---End Rider Booking-specific functions ----------------------------------------------------------------------



//Search and Update functions
vector <Rider_pid> rider_retrieve_info();
vector <Rider_pid> searchAndUpdate_userDefaultLoc(Rider_pid& updateInfo);




vector <Rider_pid> rider_register(vector <Rider_pid>& rinput);




//Rider_ridestore r_login(vector <Rider_pid> temp_pull_file);



//vector<Rider_pid> searchAndUpdate_defaultloc(Rider_ridestore& passed_pid_details, vector <Rider_pid> read_from_file);
//vector <Rider_pid> pay_details(Rider_ridestore& passed_nopid_details, vector <Rider_pid> read_from_file);
//Rider_pid pay_details(Rider_ridestore& passed_nopid_details, vector <Rider_pid> read_from_file);
void add_header_riderpid(fstream& addheader);

//CHECKING FUNCTIONS: These functions check if a variable has data stored or is an empty string or int = 0
Rider_pid has_defaultloc(Rider_pid checkloc);




#endif
