#include "../headers/Application.h"

int main()
{
    Application* application = Application::GetInstance();

    application->run();

    return 0;
}