// Nicholas Kong
// Due Date: 5/7/2020

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;



///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Round Robin below /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


// Function to find the waiting time for all using round robin
void findWaitingTime(vector <int> processes, int n, int burst_time[], int wait_time[], int quantum, int num_context[], int arrival[])
{
    // Make a copy of burst times to store remaining burst times.
    int rem_burst_time[n];
    int new_burst_time = 0, temp_burst = 0;
    for (int i = 0 ; i < n ; i++)
    {
        rem_burst_time[i] =  burst_time[i];
    }
    
    int t = 0; // Current time
    
    // Keep traversing processes in round robin manner until all of them are done.
    while (1)
    {
        bool done = true;
        
        // Traverse all processes one by one repeatedly
        for (int i = 0 ; i < n; i++)
        {
            // If burst time of a process is greater than 0 then we need to process it further
            if (rem_burst_time[i] > 0)
            {
                done = false;
                if (rem_burst_time[i] > quantum)
                {
                    // Increase the value of t i.e. shows how much time a process has been processed
                    t += quantum;
                    
                    // Decrease the burst_time of current process by quantum
                    rem_burst_time[i] -= quantum;
                    
                    // This will keep count of the number of context
                    num_context[i] = num_context[i] + 1;
                    
                }
                
                // If burst time is smaller than or equal to quantum. Last cycle for this process
                else
                {
                    // Increase the value of t i.e. shows how much time a process has been processed
                    t = t + rem_burst_time[i];
                    
                    // Waiting time is current time minus time minus arrival used by this process
                    wait_time[i] = t - burst_time[i] - arrival[i];
                    if(wait_time[i] < 0)
                    {
                        wait_time[i] = 0;
                    }

                    // As the process gets fully executed make its remaining burst time = 0
                    rem_burst_time[i] = 0;
                }
            }
        }
        // If we transversed through all processes, break out, we are done
        if (done == true)
        {
            break;
        }
    }
}

// Function to calculate turn around time
void findTurnAroundTime(vector< int > processes, int n,
                        int burst_time[], int wait_time[], int tat[], int num_context[], int arrival[])
{
    // Calculating turnaround time by adding wait_time + burst_time
    for (int i = 0; i < n ; i++)
    {
        tat[i] = burst_time[i] + wait_time[i];
    }
}

// Function to calculate average time
void findavgTime(vector< int > processes, int n, int burst_time[],
                 int quantum, int num_context[], int arrival[])
{
    int wait_time[n], tat[n], finish = 0, temp = 0, i = 0, total_num_context = 0;
    float Avg_Wait_Time = 0.0, Avg_TAT = 0.0, Avg_Burst_Time = 0.0; // For displaying averages
    
    // Function to find waiting time of all processes
    findWaitingTime(processes, n, burst_time, wait_time, quantum, num_context, arrival);
    
    // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, burst_time, wait_time, tat, num_context, arrival);
    
    cout << "Processes labeled by number. Ex: P1 = 1, P2 = 2, P3 = 3, P4 = 4, etc..." << endl;
    int get_num;
    for (int i = 0; i < n; i++)
    {
        // First process starts at 0 ms
        if(i == 0)
        {
            get_num = 0;
            cout << setw(get_num) << i + 1; // Use set precision for accurate letter placement
        }
        
        // Processes after first process starts when the previous process finish
        else if (i > 0)
        {
            cout << setw(temp * 2) << i + 1; // Use set precision for accurate letter placement
        }
        temp = burst_time[i];
    }
    
    cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " << endl;
    cout << "Process ID\tArrival Time\tBurst time\tFinish\t\tWaiting time\tTurnaround time\tNo. Of Context\n";
    cout << "---------------------------------------------------------------------------------------------------------------\n";
    
    // Calculate average waiting time and average turn around time and average CPU burst time
    for (int i=0; i<n; i++)
    {
        finish += burst_time[i];
        Avg_Wait_Time = Avg_Wait_Time + wait_time[i];
        Avg_TAT = Avg_TAT + tat[i];
        Avg_Burst_Time = Avg_Burst_Time + burst_time[i];
        total_num_context += num_context[i];
        cout << "P[" << i+1 << "]\t\t" << arrival[i] << "\t\t" << burst_time[i] <<"\t\t" << finish << "\t\t"
        << wait_time[i] <<"\t\t" << tat[i] << "\t\t" << num_context[i] <<endl;
    }
    Avg_Wait_Time /= n;
    Avg_TAT /= n;
    Avg_Burst_Time /= n;
    
    // Displays all the averages and number of context switches rounding up to 2 decimal places
    cout << "\nAverage CPU Burst Time: "; printf("%.2f", Avg_Burst_Time); cout << " ms";
    cout << "\nAverage waiting time: "; printf("%.2f", Avg_Wait_Time); cout << " ms";
    cout << "\nAverage turn around time: "; printf("%.2f", Avg_TAT); cout << " ms";
    cout << "\nThe total number of context switches is: " << total_num_context << endl;
} 

// Round robin that is called from main
void RR()
{
    vector <int> processes;
    int num, burst_time[20], arrival[20], num_context[20]; // Max process is 20
    
    cout << "\n***********************************************************************************";
    cout << "\n*********************** Scheduling Algorithm: RR **********************************";
    cout << "\n***********************************************************************************";
    
    // Gets the number of processes
    cout << "\nEnter total number of processes: ";
    cin >> num;
    int n = num;
    
    // Gets all process burst times from the user
    cout << "\nEnter Process Burst time" << endl;
    for(int i = 0; i < num; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> burst_time[i]; // Gets burst times from user
        num_context[i] = 0;
        processes.push_back(i + 1); // Pushes name of process into a vector
    }
    
    // Gets all process arrival times from the users
    cout << "Enter the arrival time." << endl;
    for(int i = 0; i < num; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> arrival[i];
    }
    
    
    // Gets the quantum from the user.
    int quantum;
    cout << "Select the quantum you would like to use." << endl;
    cout << "Quantum: ";
    cin >> quantum;
    
    // Function call which will calculate the Round Robin with user inputs
    findavgTime(processes, n, burst_time, quantum, num_context, arrival);
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Round Robin above ///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// First Come First Serve below ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


void FCFS()
{
    // tat = turn around time
    cout << "\n***********************************************************************************";
    cout << "\n*********************** Scheduling Algorithm: FCFS ********************************";
    cout << "\n***********************************************************************************";
    int n, burst_time[20], wait_time[20], tat[20], arrival[20], finish = 0, temp = 0; // Max of 20 processes
    int i, j, Num_Context = 0;
    float avg_wait_time = 0.0, avg_tat = 0.0, avg_burst_time = 0.0; // Needed to calculate average
    
    // Gets the total number of processes
    cout << "\nEnter total number of processes: ";
    cin >> n;
    
    // Gets the process burst time from the users
    cout << "\nEnter CPU Burst Time" << endl;
    for (i = 0; i < n; i++)
    {
        cout<<"P[" << i + 1 << "]: ";
        cin >> burst_time[i];
    }
    
    // Gets the process arrival time from the user
    cout << "Enter Arrival Time" << endl;
    for (i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> arrival[i];
    }
    wait_time[0] = 0; // Waiting time for first process is 0
    
    int new_burst_time = 0;
    int temp_burst = 0;
    
    // Calculating waiting time
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            // Adds previous burst time with current burst time then subtracts by arrival to get wait time
            new_burst_time = burst_time[i-1] + temp_burst;
            wait_time[i] = new_burst_time - arrival[i];
            // If wait time goes negative, set it to 0
            if(wait_time[i] < 0)
            {
                wait_time[i] = 0;
            }
            temp_burst = new_burst_time;
            break;
        }
    }
    
    // Displays the process arrivals in miliseconds
    cout << "Processes labeled by number. Ex: P1 = 1, P2 = 2, etc..." << endl;
    int get_num;
    for (int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            get_num = 0;
            cout << setw(get_num) << i + 1; // Use set precision for accurate letter placement
        }
        else if (i > 0)
        {
            cout << setw(temp * 2) << i + 1; // Use set precision for accurate letter placement
        }
        temp = burst_time[i]; // Gets the time a new process starts
    }
    cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " << endl;
    
    cout << "\nProcess ID\tArrival Time\tBurst Time\tFinish\t\tWaiting Time\tTurnaround Time   No. Of Context" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------";
    
    
    // Calculating turnaround time, and all the averages as well.
    for (i=0; i < n; i++)
    {
        finish += burst_time[i]; // Gets the finish time by adding up the burst times
        tat[i] = burst_time[i] + wait_time[i]; // Gets turn around time by adding burst time + wait time
        avg_wait_time += wait_time[i]; // Totals up wait time by adding all wait times of all processes
        avg_tat += tat[i]; // Totals up turn around time by adding up all turn around times of all processes
        avg_burst_time += burst_time[i]; // Totals up burst time by adding up all burst times of all processes
        cout << "\nP[" << i + 1 << "]" << "\t\t" << arrival[i] << "\t\t" << burst_time[i] << "\t\t" << finish << "\t\t" << wait_time[i] << "\t\t" << tat[i] << "\t\t  " << Num_Context;
    }
    
    
    avg_wait_time /= i; // Gets average by dividing total wait time by number of processes
    avg_tat /= i; // Gets average by dividing total turn around time by number of processes
    avg_burst_time /= i; // Gets average by dividing total burst time by number of processes
    
    // Prints the averages of turnaround time, waiting time, CPU burst, and the number of context switches.
    cout << "\nAverage CPU Burst Time: "; printf("%.2f", avg_burst_time); cout << " ms";
    cout << "\nAverage Waiting Time: "; printf("%.2f",avg_wait_time); cout << " ms";
    cout << "\nAverage Turnaround Time: "; printf("%.2f", avg_tat); cout << " ms";
    cout << "\nTotal number of context switches: " << Num_Context << endl;
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// First Come First Serve Above ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Shortest Remaining Task First Below /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

// Shortest Remaining Task First or Shortest Job First called by main
void SJF()
{
    // Max number of processes is 20
    int arrival[20], temp_burst[20], burst_time[20], wait_time[20], tat[20], finish[20], num_context[20];
    int i, j, smallest, count = 0, time, n, temp = 0, total_num_context = 0;
    float Avg_Wait_Time = 0.0, Avg_TAT = 0.0, Avg_Burst = 0.0, end = 0.0; // Needed for average calculations
    
    cout << "\n***********************************************************************************";
    cout << "\n*********************** Scheduling Algorithm: SRTF ********************************";
    cout << "\n***********************************************************************************";
    
    // Gets the number of process from the user
    cout << "\nEnter the number of Processes: " << endl;
    cin >> n;
    
    // Gets the process arrival time from the user
    cout << "\nEnter arrival time of process: " << endl;
    for(i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> arrival[i];
    }
    
    // Gets the process burst time from the user
    cout << "\nEnter burst time of process: " << endl;
    for(i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> temp_burst[i];
    }
    
    // Makes a copy of the process burst times
    for(i = 0; i < n; i++)
    {
        burst_time[i] = temp_burst[i];
    }
    
    temp_burst[9] = 9999; // Needed so it doesn't break on CSEgrid. Not sure why, runs fine without it on my machine.
    
    // Checks to see which job is the shortest and will do that first.
    for(time = 0; count != n; time++)
    {
        num_context[time] = 0;
        smallest = 9;
        for(i = 0; i < n; i++)
        {
            // Finds the shortest burst and stores it
            if(arrival[i] <= time && temp_burst[i] < temp_burst[smallest] && temp_burst[i] > 0)
            {
                smallest = i;
            }
            // Finds how many time each process has a context switch.
            if(temp_burst[i] < temp_burst[smallest])
            {
                num_context[time] = num_context[time] + 1;
            }
        }
        temp_burst[smallest]--; // Decrements
        
        
        // Calculates the finsih, wait_time, turnaround time.
        if(temp_burst[smallest] == 0)
        {
            count++;
            end = time + 1;
            finish[smallest] = end;
            wait_time[smallest] = end - arrival[smallest] - burst_time[smallest];
            tat[smallest] = end - arrival[smallest];
        }
    }
    
    // Shows where the process is starts in milliseconds.
    cout << "Processes labeled by number. Ex: P1 = 1, P2 = 2, etc..." << endl;
    int get_num;
    for (int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            get_num = 0;
            cout << setw(get_num) << i + 1; // Use set precision for accurate letter placement
        }
        else if (i > 0)
        {
            cout << setw(temp * 2) << i + 1; // Use set precision for accurate letter placement
        }
        temp = burst_time[i];
    }
    cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " << endl;
    
    // Displays the appropriate table format for the shortest job first.
    cout << "Process ID\tArrival Time\tBurst Time\tFinish\t\tWaiting Time\tTurnaround Time No. of Context" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------\n";
    for(i=0; i<n; i++)
    {
        cout<<"P[" << i+1 << "]\t\t" << arrival[i] << "\t\t" << burst_time[i] << "\t\t" << finish[i] << "\t\t" << wait_time[i] << "\t\t" << tat[i] << "     \t\t" << num_context[i] << endl;
        Avg_Wait_Time = Avg_Wait_Time + wait_time[i]; // Totals up wait time by adding up all the wait times
        Avg_TAT = Avg_TAT + tat[i]; // Totals up turn around time by adding up all the turn around times
        Avg_Burst += burst_time[i]; // Totals up burst time by adding up all burst times
        total_num_context += num_context[i]; // Adds up all the context switching numbers
    }
    
    
    Avg_Wait_Time /= i; // Gets average by dividing total wait time by number of processes
    Avg_TAT /= i; // Gets average by dividing total turn around time by number of processes
    Avg_Burst /= i; // Gets average by dividing total burst times by number of processes
    
    // Prints the averages along with the total context switches to the screen.
    cout << "\nAverage CPU Burst Time: "; printf("%.2f", Avg_Burst); cout << " ms";
    cout << "\nAverage Waiting Time: "; printf("%.2f", Avg_Wait_Time); cout << " ms";
    cout << "\nAverage Turnaround Time: "; printf("%.2f", Avg_TAT); cout << " ms";
    cout << "\nThe total number of context switches is: " << total_num_context << endl;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Shortest Remaining Task First Above /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Main Program Below //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, const char * argv[])
{
    int choice = 0;
    while(choice != -1) // While loops that continues to display menu until -1 is entered.
    {
        // Displayes the menu choices for the user
        cout << "\nThis is a process scheduling algorithm." << endl;
        cout << "Which scheduling algorithm would you like to perform? Enter -1 to exit" << endl;
        cout << "1. \t First Come First Serve (FCFS) scheduling algorithm" << endl;
        cout << "2. \t Round Robin (RR) scheduling algorithm" << endl;
        cout << "3. \t Shortest Remaining Task First - preemtive (SRTF) scheduling algorithm" << endl;
        cout << "-1. \t Exit the program." << endl;
        cin >> choice; // Gets the choice from user
        
        // Series of if and else if clause to go to correct scheduling algorithm desired by user
        if(choice == 1)
        {
            FCFS(); // Fully Functional.
        }
        else if(choice == 2)
        {
            RR(); // Full Functional
        }
        else if(choice == 3)
        {
            SJF(); // Fully Functional
        }
        else if(choice == -1)
        {
            cout << "Exiting the program. Goodbye." << endl;
        }
        else
        {
            cout << "That is not one of the options listed above. Try again." << endl;
        }
    }
    return 0;
}


