#include<iostream>
#include<crow_all.h>
#include<fstream>
crow::mustache::rendered_template render_page();
int main()
{
    crow::SimpleApp app; //define your crow application
    //define your endpoint at the root directory
    CROW_ROUTE(app, "/")(render_page);
    
    //set the port, set the app to run on multiple threads, and run the app
      app.route_dynamic("/static/<string>")
        .methods("GET"_method)
        ([](const crow::request&, crow::response& res, std::string filename){
            std::string file_path = "./static/css/styles.css"; // Adjust the path as needed
            std::ifstream in(file_path, std::ifstream::in);

            if (!in) {
                res.code = 404;
                res.end("File not found");
                return;
            }

            std::ostringstream contents;
            contents << in.rdbuf();
            res.write(contents.str());
        
                res.add_header("Content-Type", "text/css");

            // Add more content types if necessary

            res.end();
        });

    app.port(18080).multithreaded().run();
}
  
crow::mustache::rendered_template render_page(){
        crow::mustache::set_base("./src/templates");
        // Load the template from a file (or define it directly as a string)
        auto page = crow::mustache::load("./index.html").render();
        return page;  // Send the rendered HTML page.
}
