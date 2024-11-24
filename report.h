#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "movie.h"


class Report {
private:
    std::map<std::string, int> ticketSales; 
    std::map<std::string, float> foodSales; 
    float totalRevenue = 0.0;

public:
    
    void recordTicketSale(const std::string& movieTitle, int numTickets, float ticketPrice) {
        ticketSales[movieTitle] += numTickets;
        totalRevenue += numTickets * ticketPrice;
    }

    
    void recordFoodSale(const std::string& foodItem, float price) {
        foodSales[foodItem] += price;
        totalRevenue += price;
    }

    
    void generateReport(const std::vector<Movie*>& movieList) const {
        std::cout << "\n--- Sales Report ---" << std::endl;

        
        std::cout << "\nTicket Sales:" << std::endl;
        for (const auto& sale : ticketSales) {
            std::cout << "Movie: " << sale.first << ", Tickets Sold: " << sale.second << std::endl;
        }

        
        std::cout << "\nFood Sales:" << std::endl;
        for (const auto& sale : foodSales) {
            std::cout << "Food Item: " << sale.first << ", Total Revenue: $" << std::fixed << std::setprecision(2) << sale.second << std::endl;
        }

        
        std::cout << "\nTotal Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << std::endl;

        
        saveReportToFile();
    }

    
    void saveReportToFile() const {
        std::ofstream outFile("report.txt");
        if (!outFile.is_open()) {
            std::cerr << "Failed to open report file!" << std::endl;
            return;
        }

        outFile << "--- Sales Report ---\n";

        outFile << "\nTicket Sales:\n";
        for (const auto& sale : ticketSales) {
            outFile << "Movie: " << sale.first << ", Tickets Sold: " << sale.second << "\n";
        }

        outFile << "\nFood Sales:\n";
        for (const auto& sale : foodSales) {
            outFile << "Food Item: " << sale.first << ", Total Revenue: $" << std::fixed << std::setprecision(2) << sale.second << "\n";
        }

        outFile << "\nTotal Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << "\n";

        outFile.close();
        std::cout << "Report saved to 'report.txt'!" << std::endl;
    }
};

#endif
