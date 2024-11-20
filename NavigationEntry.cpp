/*Title: NavigationEntry.cpp
  Author: Shariq Moghees
  Date: 12/1/2024
  Description: This class defines information about visiting a website
*/
#include "NavigationEntry.h"

// CONSTRUCTORS

// Name: NavigationEntry (Default constructor)
// Description: Creates a new NavigationEntry
// Preconditions: None
// Postconditions: Creates a new NavigationEntry object
NavigationEntry::NavigationEntry(){
    m_url = ""; //empty string
    m_timeStamp = 0;
}

// Name: NavigationEntry (Overloaded constructor)
// Description: Creates a new NavigationEntry with a string and an int timestamp
// Preconditions: None
// Postconditions: Creates a new NavigationEntry object
NavigationEntry::NavigationEntry(const string& url, const int& timestamp)
    :m_url(url),m_timeStamp(timestamp){}

// GETTERS

string NavigationEntry::GetURL() const{return m_url;} //Returns the m_url
int NavigationEntry::GetTimeStamp() const{return m_timeStamp;} //Returns m_timeStamp

// SETTERS
  
void NavigationEntry::SetURL(const string& url){m_url = url;} //Used to set m_url
void NavigationEntry::SetTimeStamp(const int& time){m_timeStamp = time;} //Used to set m_timeStamp

// Name: IsEmpty
// Description: Returns true if m_url is empty
// Preconditions: None
// Postconditions: Returns true if m_url is empty else false
bool NavigationEntry::IsEmpty() const{return m_url == "";}

// Name: Overloaded <<
// Description: Prints the details of a navigation entry
// Preconditions: None
// Postconditions: Returns an ostream with output of a navigation entry
// Sample output: URL:http://daler.org/ Visited On: 2018-03-02 16:48:00
ostream& operator<<(ostream& out, NavigationEntry& entry){
    out << "URL:" << entry.GetURL() << " Visited On: " << entry.DisplayTimeStamp(entry.GetTimeStamp()) << endl;
    return out; 
} 