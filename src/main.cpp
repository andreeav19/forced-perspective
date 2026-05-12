#include "../headers/Application.h"

int main()
{
    const Application* application = Application::GetInstance();

    application->run();

    return 0;
}
