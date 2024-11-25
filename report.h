#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "movie.h"

using namespace std;


class Report {
private:
    map<string, int> ticketSales; 
    map<string, float> foodSales; 
    float totalRevenue = 0.0;

public:
    
    void recordTicketSale(const string& movieTitle, int numTickets, float ticketPrice) {
        ticketSales[movieTitle] += numTickets;
        totalRevenue += numTickets * ticketPrice;
    }

    
    void recordFoodSale(const string& foodItem, float price) {
        foodSales[foodItem] += price;
        totalRevenue += price;
    }

    
    void generateReport(const vector<Movie*>& movieList) const {
        cout << "\n--- Sales Report ---" << endl;

        
        cout << "\nTicket Sales:" << endl;
        for (const auto& sale : ticketSales) {
            cout << "Movie: " << sale.first << ", Tickets Sold: " << sale.second << endl;
        }

        
        cout << "\nFood Sales:" << endl;
        for (const auto& sale : foodSales) {
            cout << "Food Item: " << sale.first << ", Total Revenue: $" << fixed << setprecision(2) << sale.second << endl;
        }

        
        cout << "\nTotal Revenue: $" << fixed << setprecision(2) << totalRevenue << endl;

        
        saveReportToFile();
    }

    
    void saveReportToFile() const {
        ofstream outFile("report.txt");
        if (!outFile.is_open()) {
            cerr << "Failed to open report file!" << endl;
            return;
        }

        outFile << "--- Sales Report ---\n";

        outFile << "\nTicket Sales:\n";
        for (const auto& sale : ticketSales) {
            outFile << "Movie: " << sale.first << ", Tickets Sold: " << sale.second << "\n";
        }

        outFile << "\nFood Sales:\n";
        for (const auto& sale : foodSales) {
            outFile << "Food Item: " << sale.first << ", Total Revenue: $" << fixed << setprecision(2) << sale.second << "\n";
        }

        outFile << "\nTotal Revenue: $" << fixed << setprecision(2) << totalRevenue << "\n";

        outFile.close();
        cout << "Report saved to 'report.txt'!" << endl;
    }
};

#endif
