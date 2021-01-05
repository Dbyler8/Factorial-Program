#include <iostream>
#include <fstream>
#include <chrono> //To measure the tim
#include <algorithm>
using namespace std;



using namespace std::chrono;

struct node
{

	double data;
	node* next;
};

class factorial // I chose to use the class format to organize my functions. This made passing infromation easier
{
public:
	
	~factorial() {}; //I chose to use the default constructor. Node deletion happens in print()
	void compute(int fact); //This function computes the factorial and stores the results in groups of 8 per node
	void reverse(); //This function reverses the nodes so that the previous end of the nodes is now the head. THis allows the data to printed in a cohesive way
	void print(int N); //This prints and deletes the computed factorial

private:
	node* head;//ptr to head node. THis tells the program where to find the rest of the list as well
	int count;
};


int main()
{

	int N;
	cout << "Enter the value of N ";
	cin >> N;
	
	while (N > 0) //Continues to compute factorials until the user enters as negative number
	{
		auto start = high_resolution_clock::now();//Begins the time clock
		factorial test;
		test.compute(N); //Computes according to user value

		test.reverse();// Reverses the head
		test.print(N);// Prints and deletes the factorial
		cout << endl << N << "! calculated";
		auto stop = high_resolution_clock::now(); //Ends the clock
		auto duration = duration_cast<minutes>(stop - start); //Difference between the clocks 
		cout << " Computation in Minutes: " << endl << duration.count(); //Displaying the clocks
		cout << endl << "*******************************************************************" << endl << "Enter the value of N "; //*** signifies the end of this factorial and the beginning of the next.
		cin >> N; //User enters next factorial.
	}; //If non-negative will cycle again. 
	system("pause");
	return 0;
}



void factorial::compute(int N)// Uses head* in the class to effect change. 
{
	long carry = 0; double carry2; //Had problems with data loss. These two both simply act as carrier for the for the bigger values
	double result;

	node *temp, *ptr; //These node ptrs allow one to traverse the nodes without upseting the head. 
	head = new node(); //Head is given a new ndoe. 
	if (head) //If there is memery to create node
	{
		head->data = 1; //Basic values for 1 or 0
		head->next = NULL;
	}
	else
	{
		cout << "ERROR - FAILED NODE CREATION";
		return;
	}
	if (N == 1) //If one or zero, nothing more needs to be done
		return;
	else
	{
		for (long i = 2; i <= N; i++) // This loop calculates for each variable fo the factorial 
		{
			ptr = head;
			carry = 0; // Carry alway resets to zero after each factorial number has been finished

			while (ptr ->next) // Loop continues while ptr-> next is not NULL
			{
				
				result = (i * ptr->data) + carry; //Result is equal to the number times the data previously there plus the carry from teh last node if there is anything
			//	outfile << result << "result" << endl; outfiles were used to troubleshoot
				carry = result /100000000;
				carry2 = carry; //For some reason the long double would give me strange results when I would use it in the ptr->data line belo
				ptr->data = (result - (carry2 * 100000000)); //Ptr-> data is equal to the result minus the carry times 10to the 8. This esnures only 8 digits pernode
			//	outfile << ptr->data << "data" << endl;
				ptr = ptr->next; //Next pointer
			}//After the loop has conducted through, the last node is then calculated
			result = (i * ptr->data) + carry;
			carry = (result / (100000000));//These lines are the same as before with the exception that the pinter does not move
			carry2 = carry;
			ptr->data = result - (carry2 * (100000000));
	
			if (carry > 0)//If carry is still there, then this block creates a new node to house the carried values
			{
				temp = new node(); //If 
				if (temp) {
					temp->data = carry;
					temp->next = NULL;
					ptr->next = temp;
				}
				else
				{
					cout << "ERROR: FAILED NODE CREATION ON NUMBER " << i << endl;
					return;
				}
			}
	
	
		}
		
	}

}

void factorial::reverse()
{
	node* current = head, *prev = NULL, *next = NULL;

	while (current != NULL)
	{
		next = current->next; //Next moves the next node
		current->next = prev; //First instance this will be NULL and the next instance this will be the previous instance of current
		prev = current; //The prev for next cycle will now be equal to the current of this cycle thus, creating a loop
		current = next;// = current next. Simply progressing down the line
		count++; //Counts how many nodes have been reversed
	}
	head = prev; //Head is now equal to the prev. The function has completely reversed this stack. It is now ready to be printed

}
void factorial::print(int N)
{
	int final_digits = 0; int nodes = 1; //Final digits are the digits given by the head node. Not always 8., nodes tells us how many nodes have processed
	node* temp = NULL; //This pointer will be used to help move the chain along
	ofstream outfile;

	outfile.setf(ios::fixed); //Will not display in scientific format
	outfile.open("Factorial.out", std::ios_base::app);//create output file
	outfile << N << "!: " << endl;
	if (outfile.fail())
	{
		outfile << "File opening failed. \n";
		exit(0); // if we couldn't open the file to read from we exit
	}

	if (head->data < 1)
		final_digits = 0;
	else if (head->data < 10)
		final_digits = 1;
	else if (head->data < 100)
		final_digits = 2;
	else if (head->data < 1000)
		final_digits = 3;
	else if (head->data < 10000)
		final_digits = 4;
	else if (head->data < 100000)
		final_digits = 5;
	else if (head->data < 1000000)
		final_digits = 6;
	else if (head->data < 10000000)
		final_digits = 7;
	else final_digits = 8; //These if-elses determine how many digits that are in the program.

	outfile.precision(0); //Tells outfile to print 0 numbers beyond the zero
	outfile << head->data; //Dsiplays the info in the head node
	temp = head;
	head = head->next;
	delete temp; //Cycles to the next node + Deletes the used node

	while (head != NULL) //Maybe change based on how zero node is implemented (teamp!=)
	{
		{
			if (head->data < 1)
				outfile << "0000000";
			else if (head->data < 10)
				outfile << "0000000";
			else if (head->data < 100)
				outfile << "000000";
			else if (head->data < 1000)
				outfile << "00000";
			else if (head->data < 10000)
				outfile << "0000";
			else if (head->data < 100000)
				outfile << "000";
			else if (head->data < 1000000)
				outfile << "00";
			else if (head->data < 10000000)
				outfile << "0";
			outfile << head->data; //These if-elses inform the program on how many zeros to display. This is because sometimes a node begins with zeroes. All of these nodes MUST have 8 digits in them, so we add zeros in to make sure that the program reads it that way

		}
		temp = head;
		head = head->next;
		delete temp; //Display , cycle to next, and delete
		nodes++;
		if (nodes % 10 == 0) //If there are ten nodes that get cycled through, then the program instigates a new line for proper spacing	
			outfile << endl;
		
	}
	//NOTE: OUTPUT IS DISPLAYED IN Factorial.out!
	outfile << endl << "There are " << ((count-1)* 8) + final_digits << " digits in this factorial"; //count-1 because the last node is given in final_digits. Multiples the number of nodes by 8 becuase there are 8 digits in each node
	outfile << endl << "*************************************************************************" << endl;
	outfile.close();
}
