#include<iostream>
#include "crow.h"
#include<fstream>
#include<string>
#include<rab.h>
#include "./run.h"
#include "dbms.h"
// #define CROW_STATIC_DIRECTORY "./src/static" 
//crow::json::wvalue getWeatherPrediction(crow::json::rvalue);
static float genRandom(int maxval);
crow::mustache::rendered_template render_page();
crow::response handleSensorData(const crow::request&);
crow::json::wvalue returnPrediction(const crow::request&);
int main(int argv, char** args)
{
    srand(static_cast<unsigned>(time(0)));

    // std::string css_cache;
    // std::stringstream css_buffer;
    ram_cache::initialize();
    Ai::initialize();
    std::vector<double> test = {30.2,30.2,30.2,36};
    Ai::getPrediction(test);
    crow::SimpleApp app; //define your crow application
    //define your endpoint at the root directory
//    CROW_ROUTE(app, "/")(render_page);
    CROW_ROUTE(app, "/getPrediction")(returnPrediction);
    CROW_ROUTE(app, "/static/css/styles.css")([](){
        std::ifstream file("./src/static/css/styles.css",std::ios::binary);
        if (!file.is_open()) {
            std::cout<<"FIle not opened\n";
            return crow::response(404);
            
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        crow::response res(buffer.str());

        // Set the appropriate content type based on the file extension

        //  if (filename.find(".css") != std::string::npos) {
            res.set_header("Content-Type", "text/css");
        //  }

        return res;
    });
        CROW_ROUTE(app, "/static/images/image3.jpg")([](){
        std::ifstream file("./src/static/images/image3.jpg",std::ios::binary);
        if (!file.is_open()) {
            std::cout<<"FIle not opened\n";
            return crow::response(404);
            
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        crow::response res(buffer.str());

        res.set_header("Cache-Control", "public, max-age=86400"); // Cache for 1 day

        // Set the appropriate content type based on the file extension

        res.set_header("Content-Type", "image/jpeg");
        return res;
    });
        CROW_ROUTE(app,"/sensorData").methods(crow::HTTPMethod::POST)(handleSensorData);
    if(argv == 2)
        app.bindaddr("127.0.0.1").port(std::stoi(args[1])).multithreaded().run();
    else
        app.bindaddr("172.18.163.52").port(8080).multithreaded().run();
}
  
crow::mustache::rendered_template render_page(){
        crow::mustache::set_base("./src/");
        // Load the template from a file (or define it directly as a string)
        auto page = crow::mustache::load("./dashboard.html").render();
        return page;  // Send the rendered HTML page.
}

/*
crow::response handleSensorData(const crow::request& req){
    crow::json::rvalue data = crow::json::load(req.body);
    int temp = data["temperature"].d();
    
    std::cout <<temp<<"\n";
    crow::response res(200);
    return res;
    
}
*/

crow::response handleSensorData(const crow::request& req){
    crow::json::rvalue w_data = crow::json::load(req.body);
    ram_cache::wdata->temp = w_data["temperature"].d();
    ram_cache::wdata->humidity = w_data["humidity"].d();
    ram_cache::wdata->pressure = w_data["pressure"].d();
    crow::response res(200);
    return res;

}
/*
 Fixed values for testing 
crow::json::wvalue returnPrediction(const crow::request& req){
    crow::json::rvalue reqData; //= crow::json::load(req.body);
    crow::json::wvalue prediction;
    prediction["temperature"] = genRandom(50);
    prediction["rain"] = 0.69f;
    prediction["pressure"] = 14.69f;
    prediction["humidity"] = 78.6f;
    return prediction;

}
*/

crow::json::wvalue returnPrediction(const crow::request& req){
    crow::json::rvalue reqData; //= crow::json::load(req.body);
    crow::json::wvalue prediction;
    prediction["temperature"] = ram_cache::wdata->temp;
//    prediction["rain"] = "Feature Under Development"; 
    prediction["pressure"] = ram_cache::wdata->pressure;
    prediction["humidity"] = ram_cache::wdata->humidity;
    return prediction;

}
/*
crow::json::wvalue returnPrediction(const crow::request& req){
    crow::json::rvalue reqData; //= crow::json::load(req.body);
    crow::json::wvalue prediction;
    prediction["temperature"] = 38;
//    prediction["rain"] = "Feature Under Development"; 
    prediction["pressure"] = 14.69;
    prediction["humidity"] = 70;
    return prediction;

}
*/
static float genRandom(int maxval){
    return (rand() % maxval);
}
