#include<iostream>
#include<crow_all.h>
#include<fstream>
// #define CROW_STATIC_DIRECTORY "./src/static" 
crow::mustache::rendered_template render_page();
int main()
{
    crow::SimpleApp app; //define your crow application
    //define your endpoint at the root directory
    CROW_ROUTE(app, "/")(render_page);
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

        //  if (filename.find(".css") != std::string::npos) {
        res.set_header("Content-Type", "image/jpeg");

        //  }

        return res;
    });
    app.bindaddr("172.18.162.174").port(8080).multithreaded().run();
}
  
crow::mustache::rendered_template render_page(){
        crow::mustache::set_base("./src/templates");
        // Load the template from a file (or define it directly as a string)
        auto page = crow::mustache::load("./index.html").render();
        return page;  // Send the rendered HTML page.
}
