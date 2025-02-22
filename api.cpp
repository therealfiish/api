#include "crow.h"
#include <iostream>

std::vector<std::tuple<std::string, std::string, int>> hw;


int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
        .methods("GET"_method)([]
        ()
            {
                std::string msg
                { R"(

                                                    Welcome to HWMNGR!

                        This API lets you keep track of your assignments (and I guess everyone elses). 

                    -------------------------------------------------------------------------------------
                    |                                                                                   |
                    |           There are two ways that you can input assignments:                      |
                    |                                                                                   |
                    |                   1. Send a POST request to the API in this format:               |
                    |           "{ \"assignment\": \"x\", \"course\": \"y\", \"days_due\": z }"         |
                    |           where x: assignment name, y = course, and z = days remaining.           |
                    |                                                                                   |
                    |               2 (much easier). Send a GET request to this route:                  |
                    |                   /assignment/course/days_remaining                               |
                    |                       and replace each as needed.                                 |    
                    |                   IMPORTANT: USE "%20" INSTEAD OF SPACES!                         |
                    |                                                                                   |
                    |-----------------------------------------------------------------------------------|
                    |                                                                                   |
                    |       There are many ways to check your assignments. For example:                 |
                    |       1. Check by due date by sending a GET request to route /duenext.            |
                    |       2. Check by class name by sending a GET request to route /byclass.          |
                    |                                                                                   |
                    |-----------------------------------------------------------------------------------|
                    |                                                                                   |
                    |       To delete an assignment, send a GET request to \delete\n, where n is the    |
                    |       assignment number you wish to delete.                                       |
                    |                                                                                   |  
                    |-----------------------------------------------------------------------------------|
                    |                                                                                   |
                    |                          Thanks for using my API!                                 |
                    |                                                                                   |
                    -------------------------------------------------------------------------------------
                                                                                                            )" };

                return crow::response(200, msg);
            });

    CROW_ROUTE(app, "/add")
        .methods("POST"_method)([]
        (const crow::request& req)
            {
                auto body = crow::json::load(req.body);
                std::string assignmentName = body["assignment"].s();
                std::string courseName = body["course"].s();
                int days = body["days_due"].i();

                hw.emplace_back(assignmentName, courseName, days);

                return crow::response(200, "Assignment Added! This is assignment #" + std::to_string(hw.size()));
        });
   
    CROW_ROUTE(app, "/<string>/<string>/<int>")
        .methods("GET"_method)([]
        (std::string a, std::string c, int d)
        {
            hw.emplace_back(a, c, d);
            return crow::response(200, "Assignment Added! This is assignment #" + std::to_string(hw.size()));
        });

    CROW_ROUTE(app, "/duenext")
        .methods("GET"_method)([]
        ()
            {
                std::sort(hw.begin(), hw.end(), [](const std::tuple<std::string, std::string, int>& a, const std::tuple<std::string, std::string, int>& b) {
                    return std::get<2>(a) < std::get<2>(b);
                    });


                std::string results = "Assignments Due In Descending Order \n";
                for (const auto& assignment : hw) {
                    results += std::get<0>(assignment) + " - " + std::get<1>(assignment) + " - Due in " + std::to_string(std::get<2>(assignment)) + "days\n";
                }
                
                return crow::response(200, results);
            });

  
    CROW_ROUTE(app, "/byclass")
        .methods("GET"_method)([]
        ()
            {

                std::sort(hw.begin(), hw.end(), [](const std::tuple<std::string, std::string, int>& a, const std::tuple<std::string, std::string, int>& b) {
                    return std::get<1>(a) < std::get<1>(b); 
                });

                std::string results = "Assignments Sorted by Course: \n";
                for (const auto& assignment : hw) {
                    results += std::get<0>(assignment) + " - " + std::get<1>(assignment) + " - Due in " + std::to_string(std::get<2>(assignment)) + " days\n";
                }
                return crow::response(200, results);
            });

    
    app.run();
}