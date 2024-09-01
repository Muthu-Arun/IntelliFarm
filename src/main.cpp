#include<iostream>
#include<crow_all.h>
crow::mustache::rendered_template render_page();
int main()
{
    crow::SimpleApp app; //define your crow application
    //define your endpoint at the root directory
    CROW_ROUTE(app, "/")(render_page);
    
    //set the port, set the app to run on multiple threads, and run the app
    app.port(18080).multithreaded().run();
}
  
crow::mustache::rendered_template render_page(){
        crow::mustache::set_base("./src/templates");
        // Load the template from a file (or define it directly as a string)
        auto page = crow::mustache::load("./index.html").render();
        return page;  // Send the rendered HTML page.
}
