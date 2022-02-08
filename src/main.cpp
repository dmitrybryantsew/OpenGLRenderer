#include "App.hpp"

int main(int argc, char* argv []){
    simple3DEngine::App* myApp = new simple3DEngine::App();
    myApp->run();
    delete myApp;
}