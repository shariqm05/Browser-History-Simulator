/*Title: Browser.cpp
  Author: Prof. Dixon
  Date: 11/14/2024
  Description: This class defines information about the browser class
*/
#include "Browser.h"

// Name: Browser (Overloaded constructor)
// Description: Creates a new Browser with the filename passed
// Preconditions: None
// Postconditions: Sets m_fileName and m_currentPage to nullptr
Browser::Browser(string filename)
    :m_fileName(filename),m_currentPage(nullptr){}

// Name: ~Browser (Destructor)
// Description: Deallocates the items in m_backStack, m_forwardStack and
//              m_currentPage
// Preconditions: None
// Postconditions: Deallocates all dynamically allocated memory
Browser::~Browser(){
    //iterate through BackStack and delete each navEntry
    while (!m_backStack.IsEmpty()){ //while its not empty
        NavigationEntry* temp = m_backStack.Pop(); //get the top node navenry
        delete temp; // delete the navEntry in the node
    }
    //iterate through ForwardStack and delete each navEntry
    while (!m_forwardStack.IsEmpty()){ //while its not empty
        NavigationEntry* temp = m_forwardStack.Pop();
        delete temp;
    }
    //destroy current page
    delete m_currentPage;
    m_currentPage = nullptr;
}

// Name: StartBrowser
// Description: Loads the file and calls the menu
// Preconditions: None
// Postconditions: Menu keeps running until exited
void Browser::StartBrowser(){
    LoadFile();
    Menu();
}

// Name: Menu
// Description: Menu that allows browser history to be displayed, go back,
//              go forward, visit a site or quit.
// Preconditions: None
// Postconditions: When exiting, thanks user.
void Browser::Menu(){
    bool running = true; //program flag
    while (running){
        cout << "Welcome to the Browser History Simulator\n" << endl;
        cout << "Current Website:\n" << m_currentPage << endl; //uses overloaded << operator
        //main menu display
        cout << "What would you like to do?" << endl;
        cout << "1. Display Browser History" << endl;
        cout << "2. Go Back" << endl;
        cout << "3. Go Forward" << endl;
        cout << "4. Visit Site" << endl;
        cout << "5. Quit" << endl; 
        //user input
        int input;
        cin >> input;
        //process input logic
        switch(input){
            case 1:
                Display();
                break;
            case 2:
                Back(1);
                break;
            case 3:
                Forward(1);
                break;
            case 4:
                NewVisit();
                break;
            case 5: //ends program
                cout << "Ending Browser History Simulator" << endl;
                running = false;
                break;
            default: //input validation. No message, just reprompt
                cout << endl; //line break
        }
    }
}

// Name: Visit
// Description: Dynamically allocates a new NavigationEntry (NE).
//              If m_currentPage is nullptr, assigns new NE to the current Page
//              Otherwise, pushes the currentPage into the history and updates
//              m_currentPage to new NE
// Preconditions: None
// Postconditions: Adds things to m_backStack or m_currentPage
void Browser::Visit(const string& url, int timestamp){
    if (m_currentPage == nullptr){ //if current page is empty
        m_currentPage = new NavigationEntry(url, timestamp);
    } else{ 
        m_backStack.Push(m_currentPage); //put the current page in backstack
        m_currentPage = new NavigationEntry(url,timestamp);
    }
}

// Name: NewVisit
// Description: User enters the URL of the site visited and populates the
//              timestamp based on the current system time (below)
//              auto now = chrono::system_clock::now();
//              time_t nowAsTimeT = std::chrono::system_clock::to_time_t(now);
//              int64_t timestamp = static_cast<int64_t>(nowAsTimeT);
// Preconditions: None
// Postconditions: Adds new URL to m_backStack or m_currentPage
void Browser::NewVisit(){
    cout << "Enter the URL of the new site:" << endl;
    //user input url
    string input;
    cin >> input;
    //make a new timestamp of current system time by using provided code
    auto now = chrono::system_clock::now();
    time_t nowAsTimeT = std::chrono::system_clock::to_time_t(now);
    int64_t timestamp = static_cast<int64_t>(nowAsTimeT);
    //set the new current page (reference Visit)
    if (m_currentPage == nullptr){ //if no current page exists
        m_currentPage = new NavigationEntry(input, timestamp);
    }
    else{ 
        m_backStack.Push(m_currentPage); 
        m_currentPage = new NavigationEntry(input, timestamp);
    }
}

// Name: Display
// Description: Display all of then entires in the back stack and front stack
// Preconditions: None
// Postconditions: None
void Browser::Display(){
    //Back Stack Display
    cout << "**Back Stack**" << endl;
    m_backStack.Display();
    cout << endl;
    //Forward Stack Display
    cout << "**Forward Stack**" << endl;
    m_forwardStack.Display();
    cout << endl;
    //Current Website (use NavEntry overloaded <<)
    if(m_currentPage == nullptr){
        cout << "No current page" << endl;
    }
    else{
        cout << *m_currentPage << endl;
    }
    cout << endl;
}

// Name: Back (steps)
// Description: Moves item from m_currentPage to m_forwardStack
//              Moves item from m_backStack to m_currentPage
//              If m_backStack is empty, does not fail but does nothing.
//              While can do more than one step, normally only moves one.
// Preconditions: m_backStack must not be empty.
// Postconditions: Rotates items as above
NavigationEntry Browser::Back(int steps){
    if (m_backStack.IsEmpty()){ // do nothing if backstack is empty
        return *m_currentPage;
    }
    for (int i = 0; i < steps; i++){
        //set current page into forward stack
        m_forwardStack.Push(m_currentPage);
        //set previous page as current
        m_currentPage = m_backStack.Pop();
    }
    return *m_currentPage;
}

// Name: Forward (steps)
// Description: Moves item from m_backStack to m_currentPage
//              Moves item from m_currentPage to m_forwardStack
//              If m_forwardStack is empty, does not fail but does nothing.
//              While can do more than one step, normally only moves one.
// Preconditions: m_forwardStack must not be empty
// Postconditions: Rotates items as above
NavigationEntry Browser::Forward(int steps){
    if (m_forwardStack.IsEmpty()){ // do nothing if forwardstack is empty
        return *m_currentPage;
    }
    for (int i = 0; i < steps; i++){
        //set current page into back stack
        m_backStack.Push(m_currentPage);
        //set forward page as current
        m_currentPage = m_forwardStack.Pop();
    }
    return *m_currentPage;
}

// Name: GetCurrentPage
// Description: Returns the current page
// Preconditions: None
// Postconditions: None
NavigationEntry Browser::GetCurrentPage() const{
    if (m_currentPage == nullptr){ //if its nullptr
        throw runtime_error("No current page exists");
    }
    return *m_currentPage;
}

// Name: LoadFile
// Description: Loads the file using Visit
// Preconditions: None
// Postconditions: Adds things to m_backStack or m_currentPage
void Browser::LoadFile(){
    ifstream file(m_fileName); 
    //opening and processing areas
    if (file.is_open()){
        //variables for one NavEntry
        string url, timestampStr;
        while(getline(file, url, DELIMITER) &&
            getline(file, timestampStr, DELIMITER)){
            //convert all timestamp variable using stoi
            int timestamp = stoi(timestampStr);
            if (m_currentPage == nullptr){ // for first NavEntry
                m_currentPage = new NavigationEntry(url, timestamp);
            }
            else{ //push current page into back stack and set current page
                m_backStack.Push(m_currentPage);
                m_currentPage = new NavigationEntry(url, timestamp);
            }
        }
    }
    file.close(); 
}